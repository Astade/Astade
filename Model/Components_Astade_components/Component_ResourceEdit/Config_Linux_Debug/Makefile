#
# (C) Copyright 2005,2006 Anders Larsen <al@alarsen.net>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

DEBUG	= 1

# installation path
prefix	?= ~

# include path
INCLUDE	:= -I../manual
INCLUDE	+= -I../../../../Source/Icons

# Astade API
APIDIR	:= ../../Component_AstadeAPI
APILIBDIR := $(APIDIR)/Config_Linux_StatLib
APILIB	:= AstadeAPI
INCLUDE	+= -I$(APIDIR)/auto -I$(APIDIR)/manual

# compiler settings
CXXFLAGS:= $(INCLUDE) $(shell wx-config --cxxflags) -Wall
LDFLAGS	:= -L$(APILIBDIR) -l$(APILIB) $(shell wx-config --libs)

ICONSOURCE := $(wildcard ../../../../Source/icons_png/*.png)
ICONDEST = $(patsubst %.png,%_png.h,$(ICONSOURCE))
ICONAUTO = $(patsubst ../../../../Source/icons_png%,../../../Components_Astade_components/Component_ResourceEdit/auto%,$(ICONDEST))

ifdef DEBUG
CXXFLAGS+= -g
else
LDFLAGS	+= -Wl,-s
endif

# find sources and headers
SOURCES	:= $(wildcard ../auto/*.cpp ../manual/*.cpp)
HEADERS	:= $(wildcard ../auto/*.h ../manual/*.h $(APIDIR)/auto/*.h)

# objects go into current directory
OBJS	:= $(notdir $(SOURCES:.cpp=.o))

%.o:	../auto/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

%.o:	../manual/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

../../../Components_Astade_components/Component_ResourceEdit/auto/%_png.h:	../../../../Source/icons_png/%.png
	../../../Components_Helper_components/Component_bin2c/Config_Linux/bin2c -c $< $@

build:	$(TARGET)

install:	build
	install -s $(TARGET) $(prefix)/bin

clean:
	rm -f $(TARGET) *.o .depend

$(TARGET):	$(ICONAUTO) .depend $(OBJS) $(APILIBDIR)/lib$(APILIB).a
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

.depend:	Makefile $(SOURCES) $(HEADERS) $(ICONAUTO)
	$(CXX) -MM $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) >$@

-include .depend
