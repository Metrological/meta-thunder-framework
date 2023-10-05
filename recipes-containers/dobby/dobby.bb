SUMMARY = "Dobby Container Manager"
DESCRIPTION = "Dobby “Docker based Thingy” is a tool for managing and running OCI containers using crun"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=c466d4ab8a68655eb1edf0bf8c1a8fb8"

SRC_URI = "git://github.com/rdkcentral/Dobby"

#2020-12-14
SRCREV = "2db374a248e1e011a13d7ba643901f7da6972710"
DEPENDS:append = " libnl dbus jsoncpp python3 ctemplate boost yajl systemd"
RDEPENDS:${PN} = "crun (>= 0.14.1)"

S = "${WORKDIR}/git"

PACKAGECONFIG ??= "debug"
PACKAGECONFIG:append:arrisxi6 = " arrisxi6"
PACKAGECONFIG:append:llama = " llama"
PACKAGECONFIG:append:skyxione = " skyxione"

PACKAGECONFIG[debug] = "-DCMAKE_BUILD_TYPE=Debug,,"
PACKAGECONFIG[arrisxi6] = "-DLEGACY_COMPONENTS=OFF -DRDK_PLATFORM=XI6,,"
PACKAGECONFIG[llama] = "-DLEGACY_COMPONENTS=ON -DRDK_PLATFORM=LLAMA,,"
PACKAGECONFIG[skyxione] = "-DLEGACY_COMPONENTS=ON -DRDK_PLATFORM=XI1,,"

inherit pkgconfig cmake

# We use the cmake standard install, however it doesn't seem to correctly
# add the symlink for the systemd service, so here we do it as a post
# install step

do_install:append () {

    echo "Enabling service in ${D}${sysconfdir}/systemd/system/multi-user.target.wants/dobby.service"
    install -d ${D}${sysconfdir}/systemd/system/multi-user.target.wants
    ln -sf ${systemd_system_unitdir}/dobby.service ${D}${sysconfdir}/systemd/system/multi-user.target.wants/dobby.service
}

# Skip harmless QA issue caused by installing but not shipping buildtime cmake files
INSANE_SKIP:${PN} = "installed-vs-shipped"

# These are the files that end up in the rootfs
FILES:${PN} += "${systemd_system_unitdir}/dobby.service"
FILES:${PN} += "${sysconfdir}/systemd/system/multi-user.target.wants/dobby.service"
FILES:${PN} += "${sysconfdir}/dobby.json"
FILES:${PN} += "${sbindir}/DobbyDaemon"
FILES:${PN} += "${libexecdir}/DobbyInit"
FILES:${PN} += "${bindir}/DobbyTool"
FILES:${PN} += "${libdir}/plugins/dobby/*.so*"

