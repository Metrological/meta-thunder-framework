SUMMARY = "An image based on core-image that includes thunder."
LICENSE = "MIT"

IMAGE_INSTALL:append = " \
    packagegroup-core-boot \
    kernel-modules \
    packagegroup-thunder \
"

IMAGE_FEATURES:append = " \
    ssh-server-dropbear \
"
inherit core-image