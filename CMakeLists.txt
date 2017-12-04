##
## @file
## @author  Adrian Antonana
## @brief   TTCN-3 Test Executor
##

cmake_minimum_required(VERSION 3.6)

project(titan VERSION 6.3.0)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

#---------------------------------------------------------------------------------------
# Find required dependencies
#---------------------------------------------------------------------------------------
find_package(OpenSSL REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(Threads REQUIRED)
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
find_library(LIBEDIT edit)

if(LIBEDIT)
    message(STATUS "Found libedit: ${LIBEDIT}")
else()
    message(FATAL_ERROR "libedit could not be found")
endif()

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(Perl REQUIRED)
find_program(SED sed)

if(SED)
    message(STATUS "Found sed: ${SED}")
else()
    message(FATAL_ERROR "sed could not be found")
endif()
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
if(UNIX)
    set(PACKAGE_RELEASE_VERSION 1)
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "TTCN-3 is a standardized, modular language specifically designed for testing")
    set(CPACK_PACKAGE_CONTACT "Adrian Antonana a.antonana@gmail.com")
    set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
    set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/${PROJECT_NAME}-${PROJECT_VERSION}")
    set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/packages)
    set(CPACK_STRIP_FILES TRUE)

    message(STATUS "Packages will be generated under ${CPACK_PACKAGE_DIRECTORY}")

    # try get linux distributuion and arch
    execute_process(COMMAND uname -m OUTPUT_VARIABLE MACHINE_ARCH OUTPUT_STRIP_TRAILING_WHITESPACE)
    find_program(LSB_RELEASE lsb_release)

    if(LSB_RELEASE)
        execute_process(COMMAND lsb_release -sr OUTPUT_VARIABLE LINUX_DISTRO_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
        execute_process(COMMAND lsb_release -si OUTPUT_VARIABLE LINUX_DISTRO OUTPUT_STRIP_TRAILING_WHITESPACE)
        string(TOLOWER ${LINUX_DISTRO} LINUX_DISTRO)

        if(LINUX_DISTRO STREQUAL "opensuse project")
            set(LINUX_DISTRO "opensuse")
        endif()
    endif()

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpack/postinst.in
        ${CPACK_PACKAGE_DIRECTORY}/postinst
    )

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpack/postrm.in
        ${CPACK_PACKAGE_DIRECTORY}/postrm
    )

    if(LINUX_DISTRO STREQUAL "debian" OR LINUX_DISTRO STREQUAL "ubuntu" OR LINUX_DISTRO STREQUAL "linuxmint")
        execute_process(COMMAND dpkg-architecture -qDEB_HOST_ARCH OUTPUT_VARIABLE DEBIAN_ARCH OUTPUT_STRIP_TRAILING_WHITESPACE)
        list(APPEND CPACK_GENERATOR DEB)
        set(CPACK_DEB_COMPONENT_INSTALL ON)
        set(CPACK_DEBIAN_RUNTIME_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
        set(CPACK_DEBIAN_PACKAGE_RELEASE ${PACKAGE_RELEASE_VERSION})
        set(CPACK_DEBIAN_PACKAGE_VERSION "${PROJECT_VERSION}")
        set(CPACK_DEBIAN_PACKAGE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
        set(CPACK_DEBIAN_FILE_NAME "${PROJECT_NAME}_${PROJECT_VERSION}-${CPACK_DEBIAN_PACKAGE_RELEASE}_${LINUX_DISTRO}-${LINUX_DISTRO_VERSION}_${DEBIAN_ARCH}.deb")
        set(CPACK_DEBIAN_PACKAGE_DEPENDS "")
        set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
        set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
        set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/eclipse/titan.core")
        set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CPACK_PACKAGE_DIRECTORY}/postinst;${CPACK_PACKAGE_DIRECTORY}/postrm")
    elseif(LINUX_DISTRO STREQUAL "fedora" OR LINUX_DISTRO STREQUAL "opensuse" OR LINUX_DISTRO STREQUAL "centos")
        list(APPEND CPACK_GENERATOR RPM)
        set(CPACK_RPM_PACKAGE_URL "https://github.com/eclipse/titan.core")
        set(CPACK_RPM_PACKAGE_RELEASE ${PACKAGE_RELEASE_VERSION})
        set(CPACK_RPM_PACKAGE_ARCHITECTURE ${MACHINE_ARCH})
        set(CPACK_RPM_PACKAGE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
        set(CPACK_RPM_FILE_NAME "${PROJECT_NAME}_${PROJECT_VERSION}-${CPACK_RPM_PACKAGE_RELEASE}_${LINUX_DISTRO}-${LINUX_DISTRO_VERSION}_${CPACK_RPM_PACKAGE_ARCHITECTURE}.rpm")
        set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE "${CPACK_PACKAGE_DIRECTORY}/postinst")
        set(CPACK_RPM_POST_UNINSTALL_SCRIPT_FILE "${CPACK_PACKAGE_DIRECTORY}/postrm")
        set(CPACK_RPM_PACKAGE_LICENSE "EPL")
    else()
        list(APPEND CPACK_GENERATOR TGZ STGZ)
        set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME}_${PROJECT_VERSION}-${PACKAGE_RELEASE_VERSION}_Linux-${MACHINE_ARCH})
    endif()

    include(CPack)

endif()
