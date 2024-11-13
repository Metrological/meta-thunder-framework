HOMEPAGE = "https://github.com/rdkcentral/Thunder"
SUMMARY = "Thunder Framework"
DESCRIPTION = "A C++ platform abstraction layer for generic functionality."
SECTION = "thunder"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=85bcfede74b96d9a58c6ea5d4b607e58"

require ../include/thunder.inc
require ../include/version.inc

require ${@oe.utils.conditional('THUNDER_GROUP', '', '', 'include/usergroup/thunder.inc', d)}

SRC_URI = "git://github.com/rdkcentral/Thunder.git;protocol=https;branch=${RECIPE_BRANCH};protocol=https"

DEPENDS += "zlib"
DEPENDS_libc-musl += "libexecinfo"

inherit python3native systemd update-rc.d

THUNDER_SYSTEM_PREFIX ??= "WPE"
THUNDER_PORT ??= "80"
THUNDER_IDLE_TIME ??= "180"
THUNDER_ETHERNETCARD_NAME ??= "eth0"
THUNDER_SOFT_KILL_CHECK_WAIT_TIME ??= "10"
THUNDER_HARD_KILL_CHECK_WAIT_TIME ??= "4"
THUNDER_TRACING_LEVEL ??= "0"

THUNDER_INITSCRIPT_SYSTEMD_EXTRA_DEPENDS ??= ""
THUNDER_INITSCRIPT_SYSTEM_ROOT_PATH ??= "/home/root"
THUNDER_INITSCRIPT_LEVEL ??= "${@bb.utils.contains('DISTRO_FEATURES', 'thunder', '40', '80', d)}"

PACKAGECONFIG ??= "\
    hidenonexternalsymbols \
    messaging \
    webkitbrowser_autoresume \
    webserver_autoresume \
    human_versioned_binaries \
    udev_rules \
    virtualinput \
"

PACKAGECONFIG:append = " ${@bb.utils.contains('DISTRO_FEATURES', 'thunder_debug', 'debug', '', d)}"
PACKAGECONFIG:append = " ${@bb.utils.contains('DISTRO_FEATURES', 'thunder_debugoptimized', 'debugoptimized', '', d)}"
PACKAGECONFIG:append = " ${@bb.utils.contains('DISTRO_FEATURES', 'thunder_production', 'production', '', d)}"
PACKAGECONFIG:append = " ${@bb.utils.contains('DISTRO_FEATURES', 'thunder_release', 'release', '', d)}"
PACKAGECONFIG:append = " ${@bb.utils.contains('DISTRO_FEATURES', 'thunder_releasesymbols', 'releasesymbols', '', d)}"

PACKAGECONFIG:append = " ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'init_service', 'init_script', d)}"
PACKAGECONFIG:append = " ${@bb.utils.contains('DISTRO_FEATURES', 'provisioning', 'securesocket', '', d)}"
PACKAGECONFIG:append = " ${@bb.utils.contains('MACHINE_FEATURES', 'bluetooth', 'bluetooth_support', '', d)}"

PACKAGECONFIG:append = " ${@bb.utils.contains('DISTRO_FEATURES', 'thunder_debug', 'tracing', '', d)}"

# CMAKE Build Type
# DISTRO_FEATURES should be set to propagate build type across all necessary components
# like, DISTRO_FEATURES:append = "thunder_release"
PACKAGECONFIG[debug] = "-DCMAKE_BUILD_TYPE=Debug,,"
PACKAGECONFIG[debugoptimized] = "-DCMAKE_BUILD_TYPE=DebugOptimized,,"
PACKAGECONFIG[releasesymbols] = "-DCMAKE_BUILD_TYPE=RelWithDebInfo,,"
PACKAGECONFIG[release] = "-DCMAKE_BUILD_TYPE=Release,,"
PACKAGECONFIG[production] = "-DCMAKE_BUILD_TYPE=MinSizeRel,,"

# Options
PACKAGECONFIG[bluetooth_support] = "-DBLUETOOTH_SUPPORT=ON,-DBLUETOOTH_SUPPORT=OFF,bluez5"
PACKAGECONFIG[deadlockdetection] = "-DDEADLOCK_DETECTION=ON,-DDEADLOCK_DETECTION=OFF,"
PACKAGECONFIG[exceptioncatching] = "-DEXCEPTION_CATCHING=ON,-DEXCEPTION_CATCHING=OFF,"
PACKAGECONFIG[exceptionhandling] = "-DEXCEPTIONS_ENABLE=ON,-DEXCEPTIONS_ENABLE=OFF,"
PACKAGECONFIG[hidenonexternalsymbols] = "-DHIDE_NON_EXTERNAL_SYMBOLS=ON,-DHIDE_NON_EXTERNAL_SYMBOLS=OFF,"
PACKAGECONFIG[human_versioned_binaries] = "-DHUMAN_VERSIONED_BINARIES=ON,-DHUMAN_VERSIONED_BINARIES=OFF,"
PACKAGECONFIG[performancemonitor] = "-DPERFORMANCE_MONITOR=ON,-DPERFORMANCE_MONITOR=OFF,"
PACKAGECONFIG[securesocket] = "-DSECURE_SOCKET=ON,-DSECURE_SOCKET=OFF,openssl"
PACKAGECONFIG[strictcompilersettings] = "-DENABLE_STRICT_COMPILER_SETTINGS=ON,-DENABLE_STRICT_COMPILER_SETTINGS=OFF,"
PACKAGECONFIG[tracing] = "-DDISABLE_TRACING=OFF -DENABLED_TRACING_LEVEL=${THUNDER_TRACING_LEVEL},,"
PACKAGECONFIG[virtualinput] = "-DVIRTUALINPUT=ON,-DVIRTUALINPUT=OFF,"
PACKAGECONFIG[wcharsupport] = "-DWCHAR_SUPPORT=ON,-DWCHAR_SUPPORT=OFF,"

# Extensions
PACKAGECONFIG[hibernate_support] = "-DHIBERNATESUPPORT=ON,-DHIBERNATESUPPORT=OFF,"
PACKAGECONFIG[localtracer] = "-DLOCALTRACER=ON,-DLOCALTRACER=OFF,"
PACKAGECONFIG[privilegedrequest] = "-DPRIVILEGEDREQUEST=ON,-DPRIVILEGEDREQUEST=OFF,"
PACKAGECONFIG[processcontainers] = "-DPROCESSCONTAINERS=ON,-DPROCESSCONTAINERS=OFF,libcgroup collectd cgroup-lite, cgroup-lite"
PACKAGECONFIG[processcontainers_awc] = "-DPROCESSCONTAINERS_AWC=ON,-DPROCESSCONTAINERS_AWC=OFF,"
PACKAGECONFIG[processcontainers_clib] = "-DPROCESSCONTAINERS_CLIB=ON,-DPROCESSCONTAINERS_CLIB=OFF,"
PACKAGECONFIG[processcontainers_crun] = "-DPROCESSCONTAINERS_CRUN=ON,-DPROCESSCONTAINERS_CRUN=OFF,crun,crun"
PACKAGECONFIG[processcontainers_dobby] = "-DPROCESSCONTAINERS_DOBBY=ON,-DPROCESSCONTAINERS_DOBBY=OFF,dobby"
PACKAGECONFIG[processcontainers_lxc] = "-DPROCESSCONTAINERS_LXC=ON,-DPROCESSCONTAINERS_LXC=OFF,lxc"
PACKAGECONFIG[processcontainers_runc] = "-DPROCESSCONTAINERS_RUNC=ON,-DPROCESSCONTAINERS_RUNC=OFF,runc-docker"
PACKAGECONFIG[warningreporting] = "-DWARNING_REPORTING=ON,-DWARNING_REPORTING=OFF,"

# System scripts
PACKAGECONFIG[init_script] = "-DINITV_SCRIPT=ON -DSYSTEM_ROOT_PATH="${THUNDER_INITSCRIPT_SYSTEM_ROOT_PATH}" -DSYSV_INIT_LEVEL="${THUNDER_INITSCRIPT_LEVEL}",-DINITV_SCRIPT=OFF,"
PACKAGECONFIG[init_service] = "-DSYSTEMD_SERVICE=ON -DSYSTEMD_EXTRA_DEPENDS="${THUNDER_INITSCRIPT_SYSTEMD_EXTRA_DEPENDS}" -DSYSTEMD_UNIT_BASE_PATH="${systemd_unitdir}",-DSYSTEMD_SERVICE=OFF,"
PACKAGECONFIG[udev_rules] = "-DUDEV_VIDEO_RULE=ON -DPLATFORM_VIDEO_DEVICE_GROUP="${THUNDER_PLATFORM_VIDEO_DEVICE_GROUP}" -DPLATFORM_VIDEO_SUBSYSTEM="${THUNDER_PLATFORM_VIDEO_SUBSYSTEM}",-DUDEV_VIDEO_RULE=OFF,"

# Tests
PACKAGECONFIG[cyclicinspector] = "-DTEST_CYCLICINSPECTOR=ON,-DTEST_CYCLICINSPECTOR=OFF,"
PACKAGECONFIG[testloader] = "-DTEST_LOADER=ON,-DTEST_LOADER=OFF,"

# FIXME
# The WPEFramework also needs limited Plugin info in order to determine what to put in the "resumes" configuration
# it feels a bit the other way around but lets set at least webserver and webkit
PACKAGECONFIG[webkitbrowser_autoresume] = "-DPLUGIN_WEBKITBROWSER=ON,-DPLUGIN_WEBKITBROWSER=OFF,"
PACKAGECONFIG[webserver_autoresume] = "-DPLUGIN_WEBSERVER=ON,-DPLUGIN_WEBSERVER=OFF,"

def getlayerrevision(d):
    topdir = d.getVar('TOPDIR', d, True)

    layers = (d.getVar("BBLAYERS", d, True) or "").split()
    for layer in layers:
        my_layer = layer.split('/')[-1]
        if my_layer == 'meta-thunder-framework':
            try:
                return base_get_metadata_git_revision(layer, None)
            except NameError:
                return oe.buildcfg.get_metadata_git_revision(layer)


    return "unknown"

WPE_LAYER_REV ??= "${@getlayerrevision(d)}"

EXTRA_OECMAKE += "\
    -DEXTERN_EVENTS="${THUNDER_EXTERN_EVENTS}" \
    -DBUILD_SHARED_LIBS=ON \
    -DRPC=ON \
    -DBUILD_REFERENCE="${SRCREV}" \
    -DTREE_REFERENCE="${WPE_LAYER_REV}" \
    -DVERSIONED_LIBRARY_LOADING=ON \
    -DPERSISTENT_PATH="${THUNDER_PERSISTENT_PATH}" \
    ${@oe.utils.conditional('THUNDER_VOLATILE_PATH', '', '', '-DVOLATILE_PATH="${THUNDER_VOLATILE_PATH}"', d)} \
    ${@oe.utils.conditional('THUNDER_DATA_PATH', '', '', '-DDATA_PATH="${THUNDER_DATA_PATH}"', d)} \
    -DSYSTEM_PREFIX="${THUNDER_SYSTEM_PREFIX}" \
    -DPORT="${THUNDER_PORT}" \
    -DETHERNETCARD_NAME="${THUNDER_ETHERNETCARD_NAME}" \
    -DIDLE_TIME="${THUNDER_IDLE_TIME}" \
    -DSOFT_KILL_CHECK_WAIT_TIME="${THUNDER_SOFT_KILL_CHECK_WAIT_TIME}" \
    -DHARD_KILL_CHECK_WAIT_TIME="${THUNDER_HARD_KILL_CHECK_WAIT_TIME}" \
    ${@oe.utils.conditional('THUNDER_GROUP', '', '', '-DGROUP="${THUNDER_GROUP}"', d)} \
    -DPYTHON_EXECUTABLE="${PYTHON}""

SYSTEMD_SERVICE:${PN} = "thunder.service"
# If WPE Framework is enabled as distro feature, start earlier. Assuming packagegroup-wpe-boot is used and we're in control for the network
THUNDER_START = "${@bb.utils.contains('DISTRO_FEATURES', 'thunder', '40', '80', d)}"

PACKAGES =+ "${PN}-initscript"
FILES:${PN}-initscript = "${sysconfdir}/init.d/thunder"
INITSCRIPT_PACKAGES = "${PN}-initscript"
INITSCRIPT_NAME:${PN}-initscript = "thunder"
INITSCRIPT_PARAMS:${PN}-initscript = "defaults ${THUNDER_START} 24"
RRECOMMENDS:${PN} = "${PN}-initscript"

FILES:${PN} += "${libdir}/thunder/*/*.so* ${THUNDER_PERSISTENT_PATH}"
FILES:${PN}-dev += "${libdir}/thunder/*/*.so"
