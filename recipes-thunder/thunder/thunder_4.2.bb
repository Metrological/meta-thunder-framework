require ./thunder.inc

SRCREV = "8fa0abb34e7db00905fcf6ab58e05f9860ca1b50"

# FIXME, determine this a little smarter
# Provision event is required for libprovision and provision plugin
# Location event is required for locationsync plugin
# Time event is required for timesync plugin
# Identifier event is required for Compositor plugin
# Internet event is provided by the LocationSync plugin
# WebSource event is provided by the WebServer plugin

WPEFRAMEWORK_EXTERN_EVENTS ?= " \
    Decryption \
    ${@bb.utils.contains('PACKAGECONFIG', 'websource', 'WebSource', '', d)} \
    Location Time Internet Provisioning \
    ${@bb.utils.contains('DISTRO_FEATURES', 'thunder_security_disable', '', 'Security', d)} \
"

EXTRA_OECMAKE += '-DEXTERN_EVENTS="${WPEFRAMEWORK_EXTERN_EVENTS}"'