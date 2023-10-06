HOMEPAGE = "https://github.com/rdkcentral/ThunderTools"
SUMMARY = "Host/Native tooling for the Thunder"
DESCRIPTION = "Host/Native tooling (i.e generators) required to build Thunder Framework"
SECTION = "thunder"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=c3349dc67b2f8c28fc99b300eb39e3cc"
PROVIDES += "wpeframework-tools-native"
RPROVIDES:${PN} += "wpeframework-tools-native"
DEPENDS += "python3-native python3-jsonref-native"

require ../include/version.inc

SRC_URI = "git://github.com/rdkcentral/ThunderTools.git;protocol=git;branch=${RECIPE_BRANCH};protocol=https"

S = "${WORKDIR}/git"

OECMAKE_SOURCEPATH = "${WORKDIR}/git"

PACKAGECONFIG[proxystub_security] = "\
    -DPROXYSTUB_GENERATOR_ENABLE_SECURITY="ON" \
    ,-DPROXYSTUB_GENERATOR_ENABLE_SECURITY="OFF", \
"
PACKAGECONFIG[proxystub_coherency] = "\
    -DPROXYSTUB_GENERATOR_ENABLE_COHERENCY="ON" \
    ,-DPROXYSTUB_GENERATOR_ENABLE_COHERENCY="OFF", \
"

inherit cmake pkgconfig python3native 

# native need to be inherited last
inherit native

FILES:${PN} += "${datadir}/*/Modules/*.cmake"
