cmake_minimum_required(VERSION 3.6)

set(TSTLOGGER_VERSION_MAJOR 0)
set(TSTLOGGER_VERSION_MINOR 0)
set(TSTLOGGER_VERSION ${TSTLOGGER_VERSION_MAJOR}.${TSTLOGGER_VERSION_MINOR})

#add_library(junitlogger SHARED JUnitLogger.cc)
add_library(tstlogger TSTLogger.cc)
target_include_directories(tstlogger PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

set_target_properties(tstlogger PROPERTIES VERSION ${TSTLOGGER_VERSION})

add_library(tstlogger-rt2 TSTLogger.cc)
target_include_directories(tstlogger-rt2 PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

target_compile_definitions(tstlogger-rt2 PUBLIC -DTITAN_RUNTIME_2)

set_target_properties(tstlogger-rt2 PROPERTIES VERSION ${TSTLOGGER_VERSION})

#add_library(junitlogger-parallel SHARED JUnitLogger.cc)
add_library(tstlogger-parallel TSTLogger.cc)
target_include_directories(tstlogger-parallel PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

set_target_properties(tstlogger-parallel PROPERTIES VERSION ${TSTLOGGER_VERSION})

add_library(tstlogger-parallel-rt2 TSTLogger.cc)
target_include_directories(tstlogger-parallel-rt2 PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

target_compile_definitions(tstlogger-parallel-rt2 PUBLIC -DTITAN_RUNTIME_2)
set_target_properties(tstlogger-parallel-rt2 PROPERTIES VERSION ${TSTLOGGER_VERSION})

install(TARGETS tstlogger tstlogger-rt2 tstlogger-parallel tstlogger-parallel-rt2
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
