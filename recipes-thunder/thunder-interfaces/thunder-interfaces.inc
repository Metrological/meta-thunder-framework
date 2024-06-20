SUMMARY = "WPEFramework interfaces"
DESCRIPTION = "Thunder interfaces component"
HOMEPAGE = "https://github.com/rdkcentral/ThunderInterfaces"
SECTION = "thunder"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2f6c18f99faffa0e5d4ff478705c53f8"
PROVIDES += "wpeframework-interfaces"
RPROVIDES:${PN} += "wpeframework-interfaces"
DEPENDS += "thunder"

require ../include/thunder.inc
require ../include/version.inc

SRC_URI = "git://github.com/rdkcentral/ThunderInterfaces.git;protocol=git;branch=${RECIPE_BRANCH};protocol=https"

inherit python3native

EXTRA_OECMAKE += "\
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_REFERENCE=${SRCREV} \
    -DPYTHON_EXECUTABLE=${PYTHON} \
"
do_install:append() {
    if ${@bb.utils.contains("DISTRO_FEATURES", "opencdm", "true", "false", d)}
    then
        install -m 0644 ${D}${includedir}/WPEFramework/interfaces/IDRM.h ${D}${includedir}/cdmi.h
    fi
}

FILES:${PN} += "${libdir}/thunder/proxystubs/*.so*"
FILES:${PN}-dev += "${libdir}/thunder/proxystubs/*.so"
