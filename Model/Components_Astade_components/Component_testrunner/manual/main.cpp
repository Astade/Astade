#include <stdio.h>
#include <argp.h>
#include <fstream>
#include <map>
#include <vector>
#include <iomanip>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

#include <boost/shared_ptr.hpp>

#include "OutText.h"
#include "Section.h"
#include "Action.h"
#include "Test.h"
#include "Trigger.h"
#include "TextTrigger.h"

namespace classic = boost::spirit::classic;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

/* This structure is used by main to communicate with parse_opt. */
struct Arguments
{
  Arguments(): quiet(false), verbose(false), beautify(false), reportfile(0), scriptfile(0), target(0) {}
  bool quiet;
  bool verbose;
  bool beautify;
  char *reportfile;
  char *scriptfile;
  char *target;
};

Arguments arguments;

tr::Section ast(0);  // root section
tr::Section& currentSection = ast;

void newSection(const std::string& name)
{
    if (arguments.verbose)
        std::cout << "found section \"" << name << "\"" << std::endl;
    if (currentSection.findSection(name))
        throw std::string("duplicate name \"")+name+"\"";
    boost::shared_ptr<tr::Section> aSection(new tr::Section(&currentSection));
    currentSection.add(name,aSection);
}

void newTest(const std::string& name)
{
    if (arguments.verbose)
        std::cout << "found test \"" << name << "\"" << std::endl;
    if (currentSection.findSection(name))
        throw std::string("duplicate name \"")+name+"\"";
    boost::shared_ptr<tr::Section> aSection(new tr::Test(&currentSection));
    currentSection.add(name,aSection);
}

void endSection()
{
    if (arguments.verbose)
        std::cout << "section ended" << std::endl;
}

void addTrigger(const std::string& triggerText)
{
    if (arguments.verbose)
        std::cout << "add a text Trigger:" << std::endl;
    currentSection.addWatch(boost::shared_ptr<tr::Trigger>(new tr::TextTrigger(triggerText)));
}

template <typename Iterator>
struct testscript
  : qi::grammar<Iterator, std::vector<std::string>()>
{
    testscript()
      : testscript::base_type(rootSections)
    {
        using qi::lit;
        using boost::spirit::qi::omit;

        unesc_char.add("\\a", '\a')("\\b", '\b')("\\f", '\f')("\\n", '\n')
                      ("\\r", '\r')("\\t", '\t')("\\v", '\v')
                      ("\\\\", '\\')("\\\'", '\'')("\\\"", '\"')
        ;
        
        rootSections    = *(section);

        section         = (section_begin | test_begin) >> watchlist >> section_end;
        test_begin      %= space >> (lit("test") >> space >> identifier >> space >> lit("{"))[newTest];
        section_begin   %= space >> (lit("section") >> space >> identifier >> space >> lit("{"))[newSection];
        section_end     = (space >> lit("}") >> space >> lit(";"))[endSection];


        watchlist       = *(watch);
        watch           = watch_begin >> trigger >> watch_end;
        watch_begin     = space >> lit("watch") >> space >> lit(":");
        watch_end       = space >> lit(";");


        trigger         = omit[textTrigger];
        textTrigger     %= space >> unesc_str[addTrigger] ;
/*

        timeoutTrigger  = space >> lit("timeout");

        actionlist      = action >> *(lit(',') >> action);
        action          = textAction;
        textAction      = space >> unesc_str;
        */

        identifier      =  qi::char_("a-zA-Z_") > *qi::char_("a-zA-Z_0-9");
        space           = *(qi::lit(' ') | qi::lit('\n') | qi::lit('\t'));
        
        unesc_str = qi::lit('"')
            >> *(unesc_char | qi::alnum | "\\x" >> qi::hex)
            >>  qi::lit('"')
        ;
    }

    qi::rule<Iterator, std::string()> identifier;
    qi::rule<Iterator> space;
    qi::rule<Iterator,std::string()> section_begin;
    qi::rule<Iterator,std::string()> test_begin;
    qi::rule<Iterator> section;
    qi::rule<Iterator> section_end;
    qi::rule<Iterator> watch_begin;
    qi::rule<Iterator> watch_end;
    qi::rule<Iterator> watch;
    qi::rule<Iterator> trigger;
    qi::rule<Iterator,std::string()> textTrigger;
    qi::rule<Iterator> timeoutTrigger;
    qi::rule<Iterator> actionlist;
    qi::rule<Iterator> watchlist;
    qi::rule<Iterator> action;
    qi::rule<Iterator> textAction;
    qi::rule<Iterator,std::vector<std::string>()> rootSections;

    qi::rule<Iterator, std::string()> unesc_str;
    qi::symbols<char const, char const> unesc_char;

};

const char *argp_program_version =
"testrunner 0.1";

const char *argp_program_bug_address =
"<dev@astade.tigris.org>";

static struct argp_option options[] =
{
  {"target",  't', "TARGET_ADDR", 0, "the tcp address of the target.\n(e.g.: localhost:4711)"},
  {"script",  's', "SCRIPTFILE", 0, "scriptfile to execute"},
  {"verbose", 'v', 0, OPTION_ARG_OPTIONAL, "verbose info aboout parsing."},
  {"beautify",'b', 0, OPTION_ARG_OPTIONAL, "output the parsed text in a beautified form."},
  {"quiet",   'q', 0, OPTION_ARG_OPTIONAL, "there is no output about the script progress."},
  {"report",  'r', "REPORT", OPTION_ARG_OPTIONAL, "filname to write the test report instead of to standard output"},
  {0}
};

static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
    Arguments* arguments = (Arguments*) state->input;

    switch (key)
    {
    case 'b':
        arguments->beautify = true;
        break;
    case 'q':
        arguments->quiet = true;
        break;
    case 'v':
        arguments->verbose = true;
        break;
    case 'r':
        arguments->reportfile = arg;
        break;
    case 's':
        arguments->scriptfile = arg;
        break;
    case 't':
        arguments->target = arg;
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static char doc[] =
"testrunner -- A program to run testscripts.";

static struct argp argp = {options, parse_opt, 0, doc};

int main (int argc, char **argv)
{
    /* Where the magic happens */
    argp_parse (&argp, argc, argv, 0, 0, &arguments);

    if (!arguments.scriptfile)
    {
        printf("you must specify a script file\n");
        exit(-1);
    }

    // open file, disable skipping of whitespace
    std::ifstream in(arguments.scriptfile);
    in.unsetf(std::ios::skipws);

    // wrap istream into iterator
    boost::spirit::istream_iterator begin(in);
    boost::spirit::istream_iterator end;

    // wrap forward iterator with position iterator, to record the position
    typedef classic::position_iterator2<boost::spirit::istream_iterator>
        pos_iterator_type;
    pos_iterator_type position_begin(begin, end, arguments.scriptfile);
    pos_iterator_type position_end;

    testscript<pos_iterator_type> p;       // create instance of parser

    try
    {
        std::vector<std::string> s;
        qi::phrase_parse(position_begin, position_end, p, qi::space, s);
        if (position_begin != position_end)
            throw qi::expectation_failure<pos_iterator_type>(position_begin, position_end,boost::spirit::info("general error"));
    }
    catch(const qi::expectation_failure<pos_iterator_type> e)
    {
        const classic::file_position_base<std::string>& pos = e.first.get_position();
        std::cout   << "parse error at file "
                    << pos.file 
                    << " line " 
                    << pos.line 
                    << " column " 
                    << pos.column 
                    << std::endl
                    << e.what_
                    << std::endl
                    << "'"
                    << e.first.get_currentline() 
                    << "'" << std::endl 
                    << std::setw(pos.column) 
                    << " " 
                    << "^- here" 
                    << std::endl;
        return -1;    
    }
    catch(std::string e)
    {
        std::cout   << "logical error: "
                    << e
                    << std::endl;
        return -1;
    }

    if (arguments.beautify)
        ast.beautify(0);

    return 0;
}