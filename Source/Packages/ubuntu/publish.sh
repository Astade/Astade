#!/bin/bash --
#
#

DIRNAME=$(dirname $0)
PPA_DAILY="astade/daily"
PPA_RELEASE="astade/release"
DAILYEXP='^([0-9]+\.){3}[0-9]+~g[0-9a-f]{7}'

# include version info
source version

# include command line options
source ${DIRNAME}/getopts.sh

# if version is in form
# major.minor.patch.change~commit
# (e.g. 1.1.5.1~g3cf0abb)
# upload to daily ppa
if [[ $VERSION =~ $DAILYEXP ]]; then
    PPA=${PPA_DAILY}
else
    PPA=${PPA_RELEASE}
fi

# upload
dput ppa:${PPA} astade_${VERSION}-0ubuntu${PATCHLEVEL}~${DIST}_source.changes

exit 0
