SUMMARY = "Thunder Libraries"
DESCRIPTION = "Thunder libraries component"
HOMEPAGE = "https://github.com/WebPlatformForEmbedded/ThunderLibraries"
SECTION = "thunder"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=85bcfede74b96d9a58c6ea5d4b607e58"
PROVIDES += "wpeframework-libraries"
RPROVIDES:${PN} += "wpeframework-libraries"
DEPENDS += "thunder-tools-native thunder"

require ../include/thunder.inc
require ../include/version.inc

SRC_URI = "git://git@github.com:/WebPlatformForEmbedded/ThunderLibraries.git;protocol=ssh;branch=${RECIPE_BRANCH}"

PACKAGECONFIG ??= "\
    ${@bb.utils.contains('MACHINE_FEATURES', 'bluetooth', 'bluetooth', '', d)} \
    ${@bb.utils.contains('DISTRO_FEATURES', 'broadcast', 'broadcast', '', d)} \
"

PACKAGECONFIG[bluetooth] = "-DBLUETOOTH=ON,-DBLUETOOTH=OFF,bluez5"
PACKAGECONFIG[broadcast] = "-DBROADCAST=ON,-DBROADCAST=OFF,"
PACKAGECONFIG[broadcastsiparse] = "-DBROADCAST_SI_PARSING=ON,-DBROADCAST_SI_PARSING=OFF,"

EXTRA_OECMAKE += "\
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_REFERENCE=${SRCREV} \
"
