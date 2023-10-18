require ./thunder-tools.inc

# In the past the generators resided in Thunders repo.
SRC_URI = "git://github.com/rdkcentral/Thunder.git;protocol=git;branch=${RECIPE_BRANCH}"

OECMAKE_SOURCEPATH = "${WORKDIR}/git/Tools"

SRCREV = "8fa0abb34e7db00905fcf6ab58e05f9860ca1b50"
