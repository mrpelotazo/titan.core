##
## @file
## @author  Adrian Antonana
## @brief   TTCN-3 Test Executor
##

cmake_minimum_required(VERSION 3.6)

project(titan VERSION 6.2.0)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

#---------------------------------------------------------------------------------------
# Find required dependencies
#---------------------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(OpenSSL REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(Threads REQUIRED)
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
find_package(Editline REQUIRED)

#---------------------------------------------------------------------------------------
# Compiler settings
#---------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
add_definitions(-DLINUX -DNDEBUG)

#---------------------------------------------------------------------------------------
# CMake package variables
#---------------------------------------------------------------------------------------
set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(VERSION_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake")
set(PROJECT_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")

#---------------------------------------------------------------------------------------
# Add CMakeLists from subdirectories
#---------------------------------------------------------------------------------------
add_subdirectory(common)
add_subdirectory(compiler2)
add_subdirectory(compiler2/asn1)
add_subdirectory(compiler2/ttcn3)
add_subdirectory(repgen)
add_subdirectory(xsdconvert)
add_subdirectory(mctr2/cli)
add_subdirectory(mctr2/mctr)
add_subdirectory(core)
add_subdirectory(loggerplugins/JUnitLogger)
add_subdirectory(loggerplugins/JUnitLogger2)
add_subdirectory(loggerplugins/TSTLogger)
add_subdirectory(etc)

#---------------------------------------------------------------------------------------
# CMake package
#---------------------------------------------------------------------------------------
# Generate package version config file
write_basic_package_version_file(
    "${VERSION_CONFIG_FILE}"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install version config
install(
    FILES "${VERSION_CONFIG_FILE}"
    DESTINATION "${CONFIG_INSTALL_DIR}"
)

# Exported targets for build directory
export(
    EXPORT ${TARGETS_EXPORT_NAME}
    FILE ${PROJECT_NAME}-config.cmake
)

# Exported targets for installation
install(
    EXPORT ${TARGETS_EXPORT_NAME}
    DESTINATION ${CONFIG_INSTALL_DIR}
    FILE ${PROJECT_NAME}-config.cmake
)

# Add to CMake registry
export(PACKAGE ${PROJECT_NAME})

#---------------------------------------------------------------------------------------
# CPack
#---------------------------------------------------------------------------------------
set(CPACK_GENERATOR DEB)
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)
set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/${PROJECT_NAME}-${PROJECT_VERSION}")
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/packages)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/debian/postinst.in
	${CPACK_PACKAGE_DIRECTORY}/postinst
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/debian/postrm.in
	${CPACK_PACKAGE_DIRECTORY}/postrm
)

message(STATUS "DEB Generator: debian packages will be generated under ${CPACK_PACKAGE_DIRECTORY}")
set(CPACK_DEBIAN_PACKAGE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
set(CPACK_DEBIAN_FILE_NAME "${PROJECT_NAME}_${PROJECT_VERSION}-${CPACK_DEBIAN_PACKAGE_RELEASE}.deb")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "TTCN-3 is a standardized, modular language specifically designed for testing")
set(CPACK_PACKAGE_CONTACT "Adrian Antonana a.antonana@gmail.com")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/eclipse/titan.core")
#set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.rst")
#set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_DEBIAN_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
#set(CPACK_RPM_PACKAGE_LICENSE "LGPL")
set(CPACK_STRIP_FILES TRUE)
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CPACK_PACKAGE_DIRECTORY}/postinst;${CPACK_PACKAGE_DIRECTORY}/postrm")

include(CPack)
