SUMMARY = "Thunder Framework Packagegroup"
DESCRIPTION = "Thunder Packagegroup"
LICENSE = "MIT"

inherit packagegroup

PACKAGES = "\
    packagegroup-thunder \
"

RDEPENDS:${PN} = "\
    thunder \
    thunder-clientlibraries \
    thunder-interfaces \
    thunder-libraries \
    thunder-ui \
"

PROVIDES:append = " \
    packagegroup-wpeframework \
    packagegroup-thunder \
"