##
## @file
## @author     Adrian Antonana
## @brief      Common directory of the TTCN-3 Test Executor
##

#---------------------------------------------------------------------------------------
# Common not generated sources
#---------------------------------------------------------------------------------------
set(COMMON_STATIC_SOURCES
    memory.c new.cc userinfo.c path.c config_preproc.cc Quadruple.cc
    Path2.cc ModuleVersion.cc JSON_Tokenizer.cc UnicharPattern.cc openssl_version.c
    NetworkHandler.cc path.c
)

#add_executable(hostid ${COMMON_STATIC_SURCES} ${COMMON_GENERATED_SOURCES})
#add_dependencies(hostid generate-common-files)
#target_include_directories(hostid PUBLIC
#	${CMAKE_CURRENT_SOURCE_DIR}
#)

#---------------------------------------------------------------------------------------
# Bison / Flex targets
#---------------------------------------------------------------------------------------

BISON_TARGET(pattern_p ${CMAKE_CURRENT_SOURCE_DIR}/pattern_p.y ${CMAKE_CURRENT_BINARY_DIR}/pattern_p.cc)

BISON_TARGET(pattern_uni ${CMAKE_CURRENT_SOURCE_DIR}/pattern_uni.y ${CMAKE_CURRENT_BINARY_DIR}/pattern_uni.cc)

BISON_TARGET(config_preproc_p ${CMAKE_CURRENT_SOURCE_DIR}/config_preproc_p.y ${CMAKE_CURRENT_BINARY_DIR}/config_preproc_p.tab.cc
    COMPILE_FLAGS "-p config_process_"
)

FLEX_TARGET(pattern_la ${CMAKE_CURRENT_SOURCE_DIR}/pattern_la.l ${CMAKE_CURRENT_BINARY_DIR}/pattern_la.cc
    COMPILE_FLAGS "-B -s -Cr -Cfe"
)

FLEX_TARGET(config_preproc_la ${CMAKE_CURRENT_SOURCE_DIR}/config_preproc_la.l ${CMAKE_CURRENT_BINARY_DIR}/config_preproc_la.cc
    COMPILE_FLAGS "-B -s -Cr -Cfe"
)

ADD_FLEX_BISON_DEPENDENCY(pattern_la pattern_p)
ADD_FLEX_BISON_DEPENDENCY(config_preproc_la config_preproc_p)

#---------------------------------------------------------------------------------------
# Library common
#---------------------------------------------------------------------------------------
add_library(common_obj OBJECT
    ${COMMON_STATIC_SOURCES}
    ${FLEX_pattern_la_OUTPUTS}
    ${FLEX_config_preproc_la_OUTPUTS}
    ${BISON_pattern_p_OUTPUT_SOURCE}
    ${BISON_pattern_uni_OUTPUT_SOURCE}
    ${BISON_config_preproc_p_OUTPUT_SOURCE}
)

add_dependencies(common_obj cversionHeader)

set_target_properties(common_obj PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

target_include_directories(common_obj PUBLIC
    ${PROJECT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(common STATIC $<TARGET_OBJECTS:common_obj>)
add_library(common-dynamic SHARED $<TARGET_OBJECTS:common_obj>)

target_include_directories(common PUBLIC
#     ${PROJECT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#---------------------------------------------------------------------------------------
# Install target
#---------------------------------------------------------------------------------------
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.hh" PATTERN "*.h"

)
