require ./thunder-tools.inc

# In the past the generators resided in Thunders repo.
SRC_URI = "git://github.com/rdkcentral/Thunder.git;protocol=git;branch=${RECIPE_BRANCH}"

OECMAKE_SOURCEPATH = "${WORKDIR}/git/Tools"

SRCREV = "0d6aa9664f780053818d1bbd211cdcf69ec2e9aa"
