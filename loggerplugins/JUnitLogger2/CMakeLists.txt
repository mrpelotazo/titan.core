cmake_minimum_required(VERSION 3.6)

set(JUNITLOGGER_VERSION_MAJOR 0)
set(JUNITLOGGER_VERSION_MINOR 0)
set(JUNITLOGGER_VERSION ${JUNITLOGGER_VERSION_MAJOR}.${JUNITLOGGER_VERSION_MINOR})

#add_library(junitlogger SHARED JUnitLogger.cc)
add_library(junitlogger2 JUnitLogger2.cc)
target_include_directories(junitlogger2 PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

set_target_properties(junitlogger PROPERTIES VERSION ${JUNITLOGGER_VERSION})

add_library(junitlogger2-rt2 JUnitLogger2.cc)
target_include_directories(junitlogger2-rt2 PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

target_compile_definitions(junitlogger2-rt2 PUBLIC -DTITAN_RUNTIME_2)

set_target_properties(junitlogger2-rt2 PROPERTIES VERSION ${JUNITLOGGER_VERSION})

#add_library(junitlogger-parallel SHARED JUnitLogger.cc)
add_library(junitlogger2-parallel JUnitLogger2.cc)
target_include_directories(junitlogger2-parallel PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

set_target_properties(junitlogger2-parallel PROPERTIES VERSION ${JUNITLOGGER_VERSION})

add_library(junitlogger2-parallel-rt2 JUnitLogger2.cc)
target_include_directories(junitlogger2-parallel-rt2 PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

target_compile_definitions(junitlogger2-parallel-rt2 PUBLIC -DTITAN_RUNTIME_2)
set_target_properties(junitlogger2-parallel PROPERTIES VERSION ${JUNITLOGGER_VERSION})

install(TARGETS junitlogger2 junitlogger2-rt2 junitlogger2-parallel junitlogger2-parallel-rt2 
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
