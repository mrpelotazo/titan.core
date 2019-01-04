#---------------------------------------------------------------------------------------
# Library version
#---------------------------------------------------------------------------------------
set(JUNITLOGGER2_VERSION_MAJOR 0)
set(JUNITLOGGER2_VERSION_MINOR 0)
set(JUNITLOGGER2_VERSION ${JUNITLOGGER2_VERSION_MAJOR}.${JUNITLOGGER2_VERSION_MINOR})

#---------------------------------------------------------------------------------------
# Target junitlogger
#---------------------------------------------------------------------------------------
add_library(junitlogger2 SHARED JUnitLogger2.cc)

add_dependencies(junitlogger2
    cversionHeader
    generateSources
)

target_include_directories(junitlogger2 PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
    ${CMAKE_BINARY_DIR}

)

set_target_properties(junitlogger2 PROPERTIES VERSION ${JUNITLOGGER2_VERSION})

#---------------------------------------------------------------------------------------
# Target junitlogger2-rt2
#---------------------------------------------------------------------------------------
add_library(junitlogger2-rt2 SHARED JUnitLogger2.cc)

add_dependencies(junitlogger2-rt2
    cversionHeader
    generateSources
)

target_include_directories(junitlogger2-rt2 PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
    ${CMAKE_BINARY_DIR}
)

target_compile_definitions(junitlogger2-rt2 PUBLIC -DTITAN_RUNTIME_2)
set_target_properties(junitlogger2-rt2 PROPERTIES VERSION ${JUNITLOGGER2_VERSION})

#---------------------------------------------------------------------------------------
# Target junitlogger-parallel
#---------------------------------------------------------------------------------------
add_library(junitlogger2-parallel SHARED JUnitLogger2.cc)

add_dependencies(junitlogger2-parallel
    cversionHeader
    generateSources
)

target_include_directories(junitlogger2-parallel PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
    ${CMAKE_BINARY_DIR}
)

set_target_properties(junitlogger2-parallel PROPERTIES VERSION ${JUNITLOGGER2_VERSION})

#---------------------------------------------------------------------------------------
# Target junitlogger2-parallel-rt2
#---------------------------------------------------------------------------------------
add_library(junitlogger2-parallel-rt2 SHARED JUnitLogger2.cc)

add_dependencies(junitlogger2-parallel-rt2
    cversionHeader
    generateSources
)

target_include_directories(junitlogger2-parallel-rt2 PUBLIC
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_BINARY_DIR}/core
    ${CMAKE_BINARY_DIR}
)

target_compile_definitions(junitlogger2-parallel-rt2 PUBLIC -DTITAN_RUNTIME_2)
set_target_properties(junitlogger2-parallel PROPERTIES VERSION ${JUNITLOGGER2_VERSION})

#---------------------------------------------------------------------------------------
# Install targets
#---------------------------------------------------------------------------------------
install(TARGETS junitlogger2 junitlogger2-rt2 junitlogger2-parallel junitlogger2-parallel-rt2
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
