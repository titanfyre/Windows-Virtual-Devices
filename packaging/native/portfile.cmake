vcpkg_download_distfile(ARCHIVE
    URLS "https://github.com/titanfyre/Windows-Virtual-Devices/releases/download/sdk-v0.1.0/windows-virtual-devices-sdk-0.1.0.tar.gz"
    FILENAME "windows-virtual-devices-sdk-0.1.0.tar.gz"
    SHA512 3497fab64b4f951e564febce5eec3a652d4a9b8a378e8559560a2985be910ac76f6c91f18f60c1d5665e9f4e40da6980c42bb6ee7ae452796877b684c78d101f
)
vcpkg_extract_source_archive(SOURCE_PATH ARCHIVE "${ARCHIVE}" NO_REMOVE_ONE_LEVEL)
vcpkg_cmake_configure(SOURCE_PATH "${SOURCE_PATH}")
vcpkg_cmake_install()
vcpkg_cmake_config_fixup(PACKAGE_NAME WindowsVirtualDevicesSDK CONFIG_PATH lib/cmake/WindowsVirtualDevicesSDK)
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include" "${CURRENT_PACKAGES_DIR}/debug/share")
vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")
