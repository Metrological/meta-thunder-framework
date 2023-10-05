ROOTFS_POSTPROCESS_COMMAND:append = " update_thunder_path_permissions;"
update_thunder_path_permissions () {
    if [ "${THUNDER_GROUP}" != "" ] && [ "${THUNDER_SUPER_USER_GROUP}" != "" ]; then
        if [ -d "${IMAGE_ROOTFS}/${THUNDER_INSTALL_PATH}" ]; then
            chmod 0550 "${IMAGE_ROOTFS}/${THUNDER_INSTALL_PATH}"
            chown "${THUNDER_SUPER_USER_GROUP}:${THUNDER_GROUP}" "${IMAGE_ROOTFS}/${THUNDER_INSTALL_PATH}"
        fi
	if [ -d "${IMAGE_ROOTFS}/${THUNDER_PERSISTENT_PATH}" ]; then
            chmod 0755 "${IMAGE_ROOTFS}/${THUNDER_PERSISTENT_PATH}"
            chown "${THUNDER_SUPER_USER_GROUP}:${THUNDER_SUPER_USER_GROUP}" "${IMAGE_ROOTFS}/${THUNDER_PERSISTENT_PATH}"
        fi
	if [ -d "${IMAGE_ROOTFS}/${THUNDER_PERSISTENT_PATH}/WPEFramework" ]; then
            chmod 0770 "${IMAGE_ROOTFS}/${THUNDER_PERSISTENT_PATH}/WPEFramework"
            chown "${THUNDER_SUPER_USER_GROUP}:${THUNDER_GROUP}" "${IMAGE_ROOTFS}/${THUNDER_PERSISTENT_PATH}/WPEFramework"
        fi

    fi
}

