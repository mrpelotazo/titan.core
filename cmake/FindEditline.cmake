cmake_minimum_required(VERSION 3.6)

include(ExternalProject)

set(EDIT_INSTALL_DIR ${PROJECT_BINARY_DIR}/libedit-prefix)

ExternalProject_Add(libedit
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/mctr2/editline/libedit
    DOWNLOAD_COMMAND ""
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure --prefix=${EDIT_INSTALL_DIR}
    BUILD_COMMAND make
    INSTALL_COMMAND make install
)

file(MAKE_DIRECTORY ${EDIT_INSTALL_DIR}/include)

add_library(edit IMPORTED STATIC)
add_library(edit-dynamic IMPORTED SHARED)

set_target_properties(edit PROPERTIES
    IMPORTED_LOCATION ${EDIT_INSTALL_DIR}/lib/libedit.a
    INTERFACE_INCLUDE_DIRECTORIES ${EDIT_INSTALL_DIR}/include
)

set_target_properties(edit-dynamic PROPERTIES
    IMPORTED_LOCATION ${EDIT_INSTALL_DIR}/lib/libedit.so
    INTERFACE_INCLUDE_DIRECTORIES ${EDIT_INSTALL_DIR}/include
)

