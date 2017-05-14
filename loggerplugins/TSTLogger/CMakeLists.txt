cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Library version
#---------------------------------------------------------------------------------------
set(TSTLOGGER_VERSION_MAJOR 1)
set(TSTLOGGER_VERSION_MINOR 0)
set(TSTLOGGER_VERSION ${TSTLOGGER_VERSION_MAJOR}.${TSTLOGGER_VERSION_MINOR})

#---------------------------------------------------------------------------------------
# Target tstlogger
#---------------------------------------------------------------------------------------
add_library(tstlogger SHARED TSTLogger.cc)
target_include_directories(tstlogger PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

set_target_properties(tstlogger PROPERTIES VERSION ${TSTLOGGER_VERSION})

#---------------------------------------------------------------------------------------
# Target tstlogger-rt2
#---------------------------------------------------------------------------------------
add_library(tstlogger-rt2 SHARED TSTLogger.cc)
target_include_directories(tstlogger-rt2 PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

target_compile_definitions(tstlogger-rt2 PUBLIC -DTITAN_RUNTIME_2)
set_target_properties(tstlogger-rt2 PROPERTIES VERSION ${TSTLOGGER_VERSION})

#---------------------------------------------------------------------------------------
# Target tstlogger-parallel
#---------------------------------------------------------------------------------------
add_library(tstlogger-parallel SHARED TSTLogger.cc)
target_include_directories(tstlogger-parallel PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

set_target_properties(tstlogger-parallel PROPERTIES VERSION ${TSTLOGGER_VERSION})

#---------------------------------------------------------------------------------------
# Target tstlogger-parallel-rt2
#---------------------------------------------------------------------------------------
add_library(tstlogger-parallel-rt2 SHARED TSTLogger.cc)
target_include_directories(tstlogger-parallel-rt2 PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

target_compile_definitions(tstlogger-parallel-rt2 PUBLIC -DTITAN_RUNTIME_2)
set_target_properties(tstlogger-parallel-rt2 PROPERTIES VERSION ${TSTLOGGER_VERSION})

#---------------------------------------------------------------------------------------
# Install targets
#---------------------------------------------------------------------------------------
install(TARGETS tstlogger tstlogger-rt2 tstlogger-parallel tstlogger-parallel-rt2
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
