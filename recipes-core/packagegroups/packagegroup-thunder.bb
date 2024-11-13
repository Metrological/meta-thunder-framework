SUMMARY = "Thunder Framework Packagegroup"
DESCRIPTION = "Thunder Packagegroup"
LICENSE = "MIT"

PACKAGE_ARCH = "${TUNE_PKGARCH}"

inherit packagegroup

PACKAGES = "\
    packagegroup-thunder \
"

RDEPENDS:${PN} = "\
    thunder \
    thunder-clientlibraries \
    thunder-interfaces \
    thunder-ui \
"

PROVIDES:append = " \
    packagegroup-thunder \
"
