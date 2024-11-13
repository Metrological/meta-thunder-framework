SUMMARY = "Thunder interfaces"
DESCRIPTION = "Thunder interfaces component"
HOMEPAGE = "https://github.com/rdkcentral/ThunderInterfaces"
SECTION = "thunder"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2f6c18f99faffa0e5d4ff478705c53f8"
DEPENDS += "thunder"

require ../include/thunder.inc
require ../include/version.inc

SRC_URI = "git://github.com/rdkcentral/ThunderInterfaces.git;protocol=https;branch=${RECIPE_BRANCH};protocol=https"

inherit python3native

EXTRA_OECMAKE += "\
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_REFERENCE=${SRCREV} \
    -DPYTHON_EXECUTABLE=${PYTHON} \
"

FILES:${PN} += "${libdir}/thunder/proxystubs/*.so* ${libdir}/wpeframework/proxystubs/*.so*"
FILES:${PN}-dev += "${libdir}/thunder/proxystubs/*.so ${libdir}/wpeframework/proxystubs/*.so"
