cmake_minimum_required(VERSION 3.6)

set(JUNITLOGGER_VERSION_MAJOR 0)
set(JUNITLOGGER_VERSION_MINOR 0)
set(JUNITLOGGER_VERSION ${JUNITLOGGER_VERSION_MAJOR}.${JUNITLOGGER_VERSION_MINOR})

#add_library(junitlogger SHARED JUnitLogger.cc)
add_library(junitlogger JUnitLogger.cc)
target_include_directories(junitlogger PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

set_target_properties(junitlogger PROPERTIES VERSION ${JUNITLOGGER_VERSION})

add_library(junitlogger-rt2 JUnitLogger.cc)
target_include_directories(junitlogger-rt2 PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

target_compile_definitions(junitlogger-rt2 PUBLIC -DTITAN_RUNTIME_2)

set_target_properties(junitlogger-rt2 PROPERTIES VERSION ${JUNITLOGGER_VERSION})

#add_library(junitlogger-parallel SHARED JUnitLogger.cc)
add_library(junitlogger-parallel JUnitLogger.cc)
target_include_directories(junitlogger-parallel PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

set_target_properties(junitlogger-parallel PROPERTIES VERSION ${JUNITLOGGER_VERSION})

add_library(junitlogger-parallel-rt2 JUnitLogger.cc)
target_include_directories(junitlogger-parallel-rt2 PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
)

target_compile_definitions(junitlogger-parallel-rt2 PUBLIC -DTITAN_RUNTIME_2)
set_target_properties(junitlogger-parallel PROPERTIES VERSION ${JUNITLOGGER_VERSION})

install(TARGETS junitlogger junitlogger-rt2 junitlogger-parallel junitlogger-parallel-rt2 
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
