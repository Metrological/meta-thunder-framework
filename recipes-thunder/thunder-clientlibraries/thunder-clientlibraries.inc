SUMMARY = "WPEFramework client libraries"
DESCRIPTION = "Thunder client libraries component"
HOMEPAGE = "https://github.com/rdkcentral/ThunderClientLibraries"
SECTION = "thunder"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=847677038847363222ffb66cfa6406c2"
PROVIDES += "wpeframework-clientlibraries"
RPROVIDES:${PN} += "wpeframework-clientlibraries"
DEPENDS += "thunder-interfaces"

require ../include/thunder.inc
require ../include/version.inc

SRC_URI = "git://github.com/rdkcentral/ThunderClientLibraries.git;protocol=git;branch=${RECIPE_BRANCH};protocol=https \
           file://0001-Fix-Weston-Compositor.patch \
           "

inherit python3native
WPE_CDMI_ADAPTER_IMPL ??= "${@bb.utils.contains('DISTRO_FEATURES', 'nexus_svp', 'opencdmi_brcm_svp', 'opencdm_gst', d)}"

PACKAGECONFIG ??= "\
    ${@bb.utils.contains('DISTRO_FEATURES', 'opencdm', 'opencdm ${WPE_CDMI_ADAPTER_IMPL}', '', d)} \
    ${@bb.utils.contains('DISTRO_FEATURES', 'provisioning', 'provisionproxy', '', d)} \
    ${@bb.utils.contains('DISTRO_FEATURES', 'security', 'securityagent', '', d)} \
    ${@bb.utils.contains('DISTRO_FEATURES', 'compositor', 'compositorclient', '', d)} \
    ${@bb.utils.contains('DISTRO_FEATURES', 'cryptography', 'cryptography', '', d)} \
    virtualinput \
"

PACKAGECONFIG:append = " ${@bb.utils.contains('DISTRO_FEATURES', 'secapi', ' cryptography_secapi', 'cryptography_openssl', d)}"

PACKAGECONFIG:append = "${@bb.utils.contains('DISTRO_FEATURES', 'weston', 'compositorclient_wayland compositorclient_wayland_weston', '', d)}"
PACKAGECONFIG:append:rdk = " compositorclient_wayland compositorclient_wayland_westeros"

PACKAGECONFIG[bluetoothaudiosink] = "-DBLUETOOTHAUDIOSINK=ON,-DBLUETOOTHAUDIOSINK=OFF,bluez5"
PACKAGECONFIG[compositorclient] = "-DCOMPOSITORCLIENT=ON,-DCOMPOSITORCLIENT=OFF"
PACKAGECONFIG[compositorclient_mesa] = "-DPLUGIN_COMPOSITOR_IMPLEMENTATION='Mesa',,mesa libdrm"
PACKAGECONFIG[compositorclient_wayland] = "-DPLUGIN_COMPOSITOR_IMPLEMENTATION='Wayland',,"
PACKAGECONFIG[compositorclient_wayland_westeros] = "-DPLUGIN_COMPOSITOR_SUB_IMPLEMENTATION='Westeros',,westeros"
PACKAGECONFIG[compositorclient_wayland_weston] = "-DPLUGIN_COMPOSITOR_SUB_IMPLEMENTATION='Weston',,weston wayland"
PACKAGECONFIG[cryptography] = "-DCRYPTOGRAPHY=ON,-DCRYPTOGRAPHY=OFF,"
PACKAGECONFIG[cryptography_openssl] = "-DCRYPTOGRAPHY_IMPLEMENTATION="OpenSSL",,openssl"
PACKAGECONFIG[cryptography_secapi] = "-DCRYPTOGRAPHY_IMPLEMENTATION="SecApi",,virtual/secapi"
PACKAGECONFIG[cryptography_software] = "-DINCLUDE_SOFTWARE_CRYPTOGRAPHY_LIBRARY='ON',-DINCLUDE_SOFTWARE_CRYPTOGRAPHY_LIBRARY='OFF',"
PACKAGECONFIG[cryptography_test] = "-DBUILD_CRYPTOGRAPHY_TESTS=ON,,"
PACKAGECONFIG[cryptography_thunder] = "-DCRYPTOGRAPHY_IMPLEMENTATION="Thunder",,"
PACKAGECONFIG[deviceinfo] = "-DDEVICEINFO=ON,-DDEVICEINFO=OFF,"
PACKAGECONFIG[displayinfo] = "-DDISPLAYINFO=ON,-DDISPLAYINFO=OFF,"
PACKAGECONFIG[gstreamerclient] = "-DGSTREAMERCLIENT=ON,-DGSTREAMERCLIENT=OFF,gstreamer1 gst1-plugins-base"
PACKAGECONFIG[gstreamerclient_rpi] = "-DPLUGIN_COMPOSITOR_IMPLEMENTATION='RPI',,"
PACKAGECONFIG[opencdm] = "-DCDMI=ON,-DCDMI=OFF,"
PACKAGECONFIG[opencdm_gst] = "-DCDMI_ADAPTER_IMPLEMENTATION=gstreamer,,gstreamer1.0"
PACKAGECONFIG[playerinfo] = "-DPLAYERINFO=ON,-DPLAYERINFO=OFF,"
PACKAGECONFIG[provisionproxy] = "-DPROVISIONPROXY=ON -DUSE_PROVISIONING=ON,-DPROVISIONPROXY=OFF,libprovision"
PACKAGECONFIG[securityagent] = "-DSECURITYAGENT=ON,-DSECURITYAGENT=OFF"
PACKAGECONFIG[virtualinput] = "-DVIRTUALINPUT=ON,-DVIRTUALINPUT=OFF,"

EXTRA_OECMAKE += "\
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_REFERENCE=${SRCREV} \
    -DPYTHON_EXECUTABLE=${PYTHON} \
"

FILES_SOLIBSDEV = ""
FILES:${PN} += "${libdir}/*.so ${datadir}/WPEFramework/* ${PKG_CONFIG_DIR}/*.pc"
FILES:${PN}-dev += "${libdir}/cmake/*"

INSANE_SKIP:${PN} += "dev-so"
INSANE_SKIP:${PN}-dbg += "dev-so"

# Avoid settings ADNEEDED in LDFLAGS as this can cause the libcompositor.so to drop linking to libEGL/libGLES
# which might not be needed at first glance but will cause problems higher up in the change, there for lets drop -Wl,--as-needed
# some distros, like POKY (morty) enable --as-needed by default (e.g. https://git.yoctoproject.org/cgit/cgit.cgi/poky/tree/meta/conf/distro/include/as-needed.inc?h=morty)
ASNEEDED = ""

