##
## @file
## @author  Adrian Antonana
## @brief   TTCN-3 Test Executor
##

cmake_minimum_required(VERSION 3.6)

project(titan VERSION 6.2.0)

include(GNUInstallDirs)

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
# CPack
#---------------------------------------------------------------------------------------
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/packages)
message(STATUS "DEB Generator: debian packages will be generated under ${CPACK_PACKAGE_DIRECTORY}")
set(CPACK_DEBIAN_PACKAGE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
set(CPACK_DEBIAN_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}.deb")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "TTCN-3 is a standardized, modular language specifically designed for testing")
set(CPACK_PACKAGE_VENDOR "Adrian Antonana")
set(CPACK_PACKAGE_CONTACT "a.antonana@gmail.com")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/eclipse/titan.core")
#set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.rst")
#set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_DEBIAN_PACKAGE_VERSION "${PROJECT_VERSION}")
#set(CPACK_DEBIAN_PACKAGE_SECTION "Development")
#set(CPACK_RPM_PACKAGE_LICENSE "LGPL")
set(CPACK_STRIP_FILES TRUE)
set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/${PROJECT_NAME}-${PROJECT_VERSION}")
include(CPack)
