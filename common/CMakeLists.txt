##
## @file
## @author     Adrian Antonana
## @brief      Common directory of the TTCN-3 Test Executor
##

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Common not generated sources
#---------------------------------------------------------------------------------------
set(COMMON_STATIC_SOURCES
    memory.c new.cc userinfo.c path.c config_preproc.cc Quadruple.cc
    Path2.cc ModuleVersion.cc JSON_Tokenizer.cc UnicharPattern.cc openssl_version.c
    NetworkHandler.cc path.c
)

#---------------------------------------------------------------------------------------
# Common generated sources
#---------------------------------------------------------------------------------------
set(COMMON_GENERATED_SOURCES
    pattern_la.cc pattern_p.cc pattern_uni.cc config_preproc_la.cc config_preproc_p.tab.cc
)

#add_executable(hostid ${COMMON_STATIC_SURCES} ${COMMON_GENERATED_SOURCES})
#add_dependencies(hostid generate-common-files)
#target_include_directories(hostid PUBLIC
#	${CMAKE_CURRENT_SOURCE_DIR}
#)

#---------------------------------------------------------------------------------------
# Library common
#---------------------------------------------------------------------------------------
add_library(common_obj OBJECT ${COMMON_STATIC_SOURCES} ${COMMON_GENERATED_SOURCES})
set_target_properties(common_obj PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
add_dependencies(common_obj generate-common-files)
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
# File generation commands
#---------------------------------------------------------------------------------------
add_custom_command(OUTPUT pattern_la.cc
    COMMAND flex -B -s -Cr -Cfe -o pattern_la.cc ${CMAKE_CURRENT_SOURCE_DIR}/pattern_la.l
    VERBATIM
)

add_custom_command(OUTPUT pattern_p.cc pattern_p.hh
    COMMAND bison -d ${CMAKE_CURRENT_SOURCE_DIR}/pattern_p.y
    VERBATIM
)

add_custom_command(OUTPUT pattern_uni.cc pattern_uni.hh
    COMMAND bison -d ${CMAKE_CURRENT_SOURCE_DIR}/pattern_uni.y
    VERBATIM
)

add_custom_command(OUTPUT config_preproc_la.cc
    COMMAND flex -B -s -Cr -Cfe -o config_preproc_la.cc ${CMAKE_CURRENT_SOURCE_DIR}/config_preproc_la.l
    VERBATIM
)

add_custom_command(OUTPUT config_preproc_p.tab.cc config_preproc_p.tab.hh
    COMMAND bison -d -o config_preproc_p.tab.cc -p config_process_ ${CMAKE_CURRENT_SOURCE_DIR}/config_preproc_p.y
    VERBATIM
)

add_custom_target(generate-common-files
    DEPENDS config_preproc_p.tab.cc config_preproc_p.tab.hh config_preproc_la.cc pattern_uni.cc pattern_uni.hh pattern_p.cc pattern_p.hh pattern_la.cc
)
