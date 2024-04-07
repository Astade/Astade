#!/bin/bash

# Marius Montebaur, 20.06.2020
# Automatically update the html files when some templates are chagned.

ls convert.sh template.html styling.css $@ | entr ./convert.sh $@

