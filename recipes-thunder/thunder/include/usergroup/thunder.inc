inherit useradd

USERADD_PACKAGES = "${PN}"

GROUPADD_PARAM:${PN} = "-r ${THUNDER_GROUP};"

THUNDER_OCDM_GROUP_PARAM = "${@oe.utils.conditional('THUNDER_OCDM_GROUP', '', '', '-r', d)}"
GROUPADD_PARAM:${PN} += "${@bb.utils.contains('DISTRO_FEATURES', 'opencdm', '${THUNDER_OCDM_GROUP_PARAM} ${THUNDER_OCDM_GROUP}', '', d)}"
