cmake_minimum_required(VERSION 3.6)

include(ExternalProject)

set(LIBEDIT_INSTALL_DIR ${PROJECT_BINARY_DIR}/libedit-prefix)
set(LIBEDIT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/mctr2/editline/libedit)

ExternalProject_Add(libedit
    SOURCE_DIR ${LIBEDIT_SOURCE_DIR}
    DOWNLOAD_COMMAND ""
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure --prefix=${LIBEDIT_INSTALL_DIR}
    BUILD_COMMAND make
    INSTALL_COMMAND make install
)

ExternalProject_Add_Step(libedit regen-automake
    COMMAND aclocal
    COMMAND libtoolize
    COMMAND automake --add-missing
    WORKING_DIRECTORY ${LIBEDIT_SOURCE_DIR}
    COMMENT "Regenerating automake files..."
    DEPENDEES download
    DEPENDERS configure
)

file(MAKE_DIRECTORY ${LIBEDIT_INSTALL_DIR}/include)

add_library(edit IMPORTED STATIC)
add_library(edit-dynamic IMPORTED SHARED)

set_target_properties(edit PROPERTIES
    IMPORTED_LOCATION ${LIBEDIT_INSTALL_DIR}/lib/libedit.a
    INTERFACE_INCLUDE_DIRECTORIES ${LIBEDIT_INSTALL_DIR}/include
)

set_target_properties(edit-dynamic PROPERTIES
    IMPORTED_LOCATION ${LIBEDIT_INSTALL_DIR}/lib/libedit.so
    INTERFACE_INCLUDE_DIRECTORIES ${LIBEDIT_INSTALL_DIR}/include
)

