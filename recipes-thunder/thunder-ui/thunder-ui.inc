SUMMARY = "Thunder Framework User Interface"
DESCRIPTION = "Thunder Framework User Interface web app"
HOMEPAGE = "https://github.com/rdkcentral/ThunderUI"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=66fe57b27abb01505f399ce4405cfea0"
PROVIDES += "wpeframework-ui"
RPROVIDES:${PN} += "wpeframework-ui"

require ../include/version.inc

SRC_URI = "git://github.com/rdkcentral/ThunderUI.git;branch=${RECIPE_BRANCH};protocol=https"

S = "${WORKDIR}/git"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
    rm -rf ${D}${datadir}/WPEFramework/Controller/UI/*
    mkdir -p ${D}${datadir}/WPEFramework/Controller/UI
    cp -r ${S}/src/* ${D}${datadir}/WPEFramework/Controller/UI
    cp -r ${S}/dist/* ${D}${datadir}/WPEFramework/Controller/UI
}

FILES:${PN} += "${datadir}/WPEFramework/Controller/UI/*"

