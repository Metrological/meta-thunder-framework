SUMMARY = "Thunder Framework Packagegroup"
DESCRIPTION = "Thunder Packagegroup"
LICENSE = "MIT"

inherit packagegroup

PACKAGES = "\
    packagegroup-thunder \
"

RDEPENDS_packagegroup-thunder = "\
    thunder \
    thunder-clientlibraries \
    thunder-interfaces \
    thunder-libraries \
    thunder-ui \
"

PROVIDES += "packagegroup-wpeframework"