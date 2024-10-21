SUMMARY = "An image based on core-image that includes thunder."
LICENSE = "MIT"

inherit core-image

IMAGE_INSTALL += "\
    packagegroup-core-boot \
    kernel-modules \
    packagegroup-thunder \
"

IMAGE_FEATURES += "\
    ssh-server-dropbear \
"
