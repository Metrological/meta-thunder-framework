SUMMARY = "An image based on core-image that includes thunder."
LICENSE = "MIT"

IMAGE_INSTALL += "\
    packagegroup-core-boot \
    kernel-modules \
    packagegroup-thunder \
"

IMAGE_FEATURES += "\
    ssh-server-dropbear \
"

inherit core-image
