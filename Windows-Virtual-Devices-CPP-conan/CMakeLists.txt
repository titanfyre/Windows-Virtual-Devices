cmake_minimum_required(VERSION 3.24)
project(WindowsVirtualDevicesSDK VERSION 0.1.0.0 LANGUAGES C CXX)
if(NOT WIN32 OR NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(FATAL_ERROR "This SDK requires Windows x64. No driver is installed by this build.")
endif()
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
add_library(TitanWindowsVirtualDevices STATIC
  "sdk/VirtualDevice/VirtualDevice.cpp"
)
add_library(WindowsVirtualDevicesSDK::sdk ALIAS TitanWindowsVirtualDevices)
set_target_properties(TitanWindowsVirtualDevices PROPERTIES EXPORT_NAME sdk)
target_compile_features(TitanWindowsVirtualDevices PUBLIC cxx_std_17)
target_compile_definitions(TitanWindowsVirtualDevices PUBLIC )
target_compile_definitions(TitanWindowsVirtualDevices PRIVATE UNICODE _UNICODE NOMINMAX WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0A00)
if(MSVC)
  target_compile_options(TitanWindowsVirtualDevices PRIVATE /utf-8 /EHsc /W4)
endif()
target_include_directories(TitanWindowsVirtualDevices PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sdk>"
  "$<INSTALL_INTERFACE:include/>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sdk/VirtualDevice>"
  "$<INSTALL_INTERFACE:include/VirtualDevice>"
)
target_link_libraries(TitanWindowsVirtualDevices PUBLIC advapi32 cfgmgr32 comctl32 crypt32 gdi32 hid newdev setupapi shell32 user32 wintrust)
install(TARGETS TitanWindowsVirtualDevices EXPORT WindowsVirtualDevicesSDKTargets ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY sdk/ DESTINATION include FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.inl")
install(FILES LICENSE DESTINATION share/windows-virtual-devices)
install(EXPORT WindowsVirtualDevicesSDKTargets NAMESPACE WindowsVirtualDevicesSDK:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WindowsVirtualDevicesSDK)
configure_file("WindowsVirtualDevicesSDKConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/WindowsVirtualDevicesSDKConfig.cmake" @ONLY)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/WindowsVirtualDevicesSDKConfigVersion.cmake" VERSION 0.1.0.0 COMPATIBILITY SameMajorVersion)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/WindowsVirtualDevicesSDKConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/WindowsVirtualDevicesSDKConfigVersion.cmake" DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WindowsVirtualDevicesSDK)
