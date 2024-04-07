#!/bin/bash

# Converts all markdown files given as args to html with a given template.
# Is called once and gets all markdown files as command line args.
#
# example arg:
# $ ./convert.sh source/*.md
#
# example usage:
# $ ./convert.sh source/*.md  # markdown files have to be inside source folder
# $ ./convert.sh  # will look for .md files in the source folder
#

website_dir=_website  # output of the translated website
source_dir=source  # folder containing the source files, i.e. markdown files


# jeez, why isn't that enabled by default?
# http://chiefsandendians.blogspot.com/2010/07/linux-scripts-and-alias.html
shopt -s expand_aliases


### Check whether executed on BSD/macOS or GNU:
# Since this will unfortunately affect the behaviour of sed.
# Thanks to https://stackoverflow.com/a/6836122
strings /bin/rm | grep -q 'GNU coreutils' 

if [ "$?" -eq 0 ]; then
    # on GNU Linux
    alias sedi="sed -i''"
else
    # on BSD/macOS
    # rm ~/core_util_check;
    alias sedi="sed -i ''"
fi
###


### Create command for relative path with python as realpath command is not available on every distribution
relpath() {
    python3 -c "import os.path; print(os.path.relpath('$1','$2'))" ;
} 
###


### Search for local binary of pandoc. Uberspace only has an outdated version
if [ -f ~/bin/pandoc ]; then
    alias pandoc="~/bin/pandoc"
    echo "Switched to local pandoc"
fi
echo "Using pandoc version:" `pandoc -v | head -n 1`
###


# create output dir
rm -rf $website_dir
mkdir $website_dir

if [ $# -eq 0 ]; then
    # find markdown files if none are given
    md_files=`find $source_dir -name "*.md"`
else
    md_files=$@
fi


for template in $md_files;
do
    filename="$(basename "$template" .md).html"  # source/projects/file.md -> file.html
    filepath=`dirname "${template#*/}"`  # source/projects/file.md -> projects

    mkdir -p $website_dir/$filepath  # create _website/projects

    out_file=$website_dir/$filepath/$filename

    # used to find stylesheet and such in website's root
    dir_depth=`relpath '.' $filepath`

    stylesheet_path=$dir_depth/styling.css

    # --columns 10000 is ugly but without it html tables are broken: https://github.com/jgm/pandoc/issues/2574

    # Variables are passed through to the template and can be used there.
    # rel_path: used to navigate to the website's root. e.g. "../"
    # root_path: used to list page's url in open graph protocol. https://ogp.me/
    # current_date: is appended as a querying parameter to the css file to refresh the cache after the website updated

    pandoc $template \
        --mathml \
        --from=markdown \
        --to=html \
        --template template.html \
        --columns 10000 \
        --number-sections \
        --css $stylesheet_path \
        --toc --toc-depth=2 \
        --metadata autor="Thomas Spitzer" \
        --variable=rel_path:"$dir_depth/" \
        --variable=document_path:"$filepath/$filename" \
        --variable=current_date:"$(date +%Y-%m-%d_%H-%M-%S)" \
        --citeproc \
        --output=$out_file

    # remove spaces from the beginning of code blocks
    sedi "/  <span id=\"cb/s/^  //g" $out_file

    echo "converted $template -> $out_file"
done


cp styling.css $website_dir/
# cp source/favicon.png $website_dir/
cp -r source/media $website_dir/
# remove all hidden files
find $website_dir/ -type f -name '.*' ! -name ".htaccess" -delete

echo "conversion done."
