require ./thunder-tools.inc

LIC_FILES_CHKSUM = "file://LICENSE;md5=85bcfede74b96d9a58c6ea5d4b607e58"

# In the past the generators resided in Thunders repo.
SRC_URI = "git://github.com/rdkcentral/Thunder.git;protocol=https;branch=${RECIPE_BRANCH}"

OECMAKE_SOURCEPATH = "${WORKDIR}/git/Tools"

SRCREV = "0d6aa9664f780053818d1bbd211cdcf69ec2e9aa"
