##
## @file
## @author  Adrian Antonana
## @brief   Base Library of TTCN-3 Test Executor
##

cmake_minimum_required(VERSION 3.6)

set(SCHEMA TitanLoggerApi.xsd)
set(GENERATED_MODULE TitanLoggerApi.ttcn)
set(GENERATED_LOGGERAPI_SOURCES TitanLoggerApi.cc)
set(PREGENERATOR_MODULES PreGenRecordOf.ttcn)
set(GENERATED_LOGGERCONTROL_SOURCES TitanLoggerControl.cc)
set(PREGENERATED_SOURCES PreGenRecordOf.cc)
set(GENERATED_SOURCES
    ${GENERATED_LOGGERAPI_SOURCES}
    ${GENERATED_LOGGERCONTROL_SOURCES}
    config_process.lex.cc config_process.tab.cc
    ${PREGENERATED_SOURCES}
)

#---------------------------------------------------------------------------------------
# Core main not generated sources
#---------------------------------------------------------------------------------------
set(CORE_STATIC_SOURCES_MAIN
    Parallel_main.cc
    Single_main.cc
    ProfMerge_main.cc
)

#---------------------------------------------------------------------------------------
# Core not-main not generated sources
#---------------------------------------------------------------------------------------
set(CORE_STATIC_SOURCES_NO_MAIN
    Addfunc.cc Array.cc ASN_Any.cc ASN_CharacterString.cc
    ASN_EmbeddedPDV.cc ASN_External.cc ASN_Null.cc Basetype.cc BER.cc Bitstring.cc
    Boolean.cc Charstring.cc Communication.cc Component.cc Default.cc Encdec.cc
    Error.cc Float.cc Hexstring.cc RInt.cc Integer.cc Logger.cc LoggerPlugin.cc
    LoggerPluginManager.cc LegacyLogger.cc LoggingBits.cc
    Module_list.cc Objid.cc Octetstring.cc Port.cc RAW.cc
    Runtime.cc Snapshot.cc Struct_of.cc Template.cc TEXT.cc
    Textbuf.cc Timer.cc Param_Types.cc Universal_charstring.cc
    Verdicttype.cc XER.cc XmlReader.cc TitanLoggerControlImpl.cc TCov.cc JSON.cc
    Profiler.cc ProfilerTools.cc Debugger.cc DebuggerUI.cc
)

#---------------------------------------------------------------------------------------
# Core2 not generated sources
#---------------------------------------------------------------------------------------
set(CORE2_STATIC_SOURCES
    ${CORE_STATIC_SOURCES_NO_MAIN}
    ${PROJECT_SOURCE_DIR}/core2/Basetype2.cc
)

set(RT1_DIR ${CMAKE_CURRENT_BINARY_DIR}/RT1)
set(RT2_DIR ${CMAKE_CURRENT_BINARY_DIR}/RT2)

#---------------------------------------------------------------------------------------
# File generation commands
#---------------------------------------------------------------------------------------
add_custom_command(OUTPUT ${RT1_DIR}/TitanLoggerApi.hh ${RT2_DIR}/TitanLoggerApi.hh
    COMMAND mkdir ${RT1_DIR}
    COMMAND mkdir ${RT2_DIR}
    COMMAND ${PROJECT_BINARY_DIR}/xsdconvert/xsd2ttcn ${CMAKE_CURRENT_SOURCE_DIR}/${SCHEMA}
    COMMAND sed -i -e 's/XSD.String/charstring/g' -e 's/XSD.AnySimpleType/charstring/g' -e 's/XSD.Integer/integer/g' -e 's/XSD.Float/float/g' -e 's/XSD.Double/float/g' -e 's/XSD.Boolean/boolean/g' -e 's/import\ from\ XSD\ all\;//g' ${GENERATED_MODULE}
    COMMAND ${PROJECT_BINARY_DIR}/compiler2/compiler -o ${RT1_DIR} ${GENERATED_MODULE}
    COMMAND ${PROJECT_BINARY_DIR}/compiler2/compiler -R -o ${RT2_DIR} ${GENERATED_MODULE}
)

add_custom_command(OUTPUT ${RT1_DIR}/TitanLoggerApiSimple.hh ${RT2_DIR}/TitanLoggerApiSimple.hh
    COMMAND perl ${CMAKE_CURRENT_SOURCE_DIR}/simplify.pl ${RT1_DIR}/TitanLoggerApi.hh > ${RT1_DIR}/TitanLoggerApiSimple.hh
    COMMAND perl ${CMAKE_CURRENT_SOURCE_DIR}/simplify.pl ${RT2_DIR}/TitanLoggerApi.hh > ${RT2_DIR}/TitanLoggerApiSimple.hh
)

add_custom_command(OUTPUT ${RT1_DIR}/PreGenRecordOf.hh ${RT2_DIR}/PreGenRecordOf.hh
    COMMAND ${PROJECT_BINARY_DIR}/compiler2/compiler -F -o ${RT1_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${PREGENERATOR_MODULES}
    COMMAND ${PROJECT_BINARY_DIR}/compiler2/compiler -F -R -o ${RT2_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${PREGENERATOR_MODULES}
)

add_custom_command(OUTPUT ${RT1_DIR}/TitanLoggerControl.hh ${RT2_DIR}/TitanLoggerControl.hh
    COMMAND ${PROJECT_BINARY_DIR}/compiler2/compiler -F -o ${RT1_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/TitanLoggerControl.ttcn
    COMMAND ${PROJECT_BINARY_DIR}/compiler2/compiler -F -R -o ${RT2_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/TitanLoggerControl.ttcn
)

#---------------------------------------------------------------------------------------
# Target gccversion
#---------------------------------------------------------------------------------------
add_executable(gccversion gccversion.c)

add_custom_command(OUTPUT cversion.h
    COMMAND gccversion > cversion.h
)

#---------------------------------------------------------------------------------------
# Target ttcn3
#---------------------------------------------------------------------------------------
add_library(ttcn3_obj OBJECT ${CORE_STATIC_SOURCES_NO_MAIN}
    Single_main.cc LoggerPlugin_static.cc ${RT1_DIR}/TitanLoggerApi.hh
    ${RT1_DIR}/TitanLoggerApiSimple.hh ${RT1_DIR}/PreGenRecordOf.hh
    ${RT1_DIR}/TitanLoggerControl.hh cversion.h
)

set_target_properties(ttcn3_obj PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_include_directories(ttcn3_obj PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_BINARY_DIR}
    ${RT1_DIR}
    ${LIBXML2_INCLUDE_DIR}
)

add_library(ttcn3 STATIC $<TARGET_OBJECTS:ttcn3_obj>)
add_library(ttcn3-dynamic SHARED $<TARGET_OBJECTS:ttcn3_obj>)

# target_sources(ttcn3 PUBLIC
#     ${CORE_STATIC_SOURCES_NO_MAIN}
# )

target_include_directories(ttcn3 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_BINARY_DIR}
    ${RT1_DIR}
    ${LIBXML2_INCLUDE_DIR}
)

target_link_libraries(ttcn3-dynamic PUBLIC
    common-dynamic
    edit-dynamic
)

#---------------------------------------------------------------------------------------
# Target ttcn3-parallel
#---------------------------------------------------------------------------------------
add_library(ttcn3-parallel_obj OBJECT ${CORE_STATIC_SOURCES_NO_MAIN}
    Parallel_main.cc LoggerPlugin_static.cc ${RT1_DIR}/TitanLoggerApi.hh
    ${RT1_DIR}/TitanLoggerApiSimple.hh ${RT1_DIR}/PreGenRecordOf.hh
    ${RT1_DIR}/TitanLoggerControl.hh cversion.h
)

set_target_properties(ttcn3-parallel_obj PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

add_library(ttcn3-parallel STATIC $<TARGET_OBJECTS:ttcn3-parallel_obj>)
add_library(ttcn3-parallel-dynamic SHARED $<TARGET_OBJECTS:ttcn3-parallel_obj>)

target_include_directories(ttcn3-parallel_obj PUBLIC
    ${LIBXML2_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${RT1_DIR}

)

target_link_libraries(ttcn3-parallel-dynamic PUBLIC
    common-dynamic
    edit-dynamic
)
#---------------------------------------------------------------------------------------
# Target ttcn3-rt2
#---------------------------------------------------------------------------------------
add_library(ttcn3-rt2_obj OBJECT ${CORE2_STATIC_SOURCES}
    Single_main.cc ${RT2_DIR}/TitanLoggerApi.hh
    ${RT2_DIR}/TitanLoggerApiSimple.hh ${RT2_DIR}/PreGenRecordOf.hh
    ${RT2_DIR}/TitanLoggerControl.hh cversion.h
)

set_target_properties(ttcn3-rt2_obj PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_compile_options(ttcn3-rt2_obj PUBLIC -DTITAN_RUNTIME_2)

target_include_directories(ttcn3-rt2_obj PUBLIC
    ${LIBXML2_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${RT2_DIR}
)

add_library(ttcn3-rt2 STATIC $<TARGET_OBJECTS:ttcn3-rt2_obj>)
add_library(ttcn3-rt2-dynamic SHARED $<TARGET_OBJECTS:ttcn3-rt2_obj>)

target_link_libraries(ttcn3-rt2-dynamic PUBLIC
    common-dynamic
    edit-dynamic
)

#---------------------------------------------------------------------------------------
# Target ttcn3-rt2-parallel
#---------------------------------------------------------------------------------------
add_library(ttcn3-rt2-parallel_obj OBJECT ${CORE2_STATIC_SOURCES}
    Parallel_main.cc ${RT2_DIR}/TitanLoggerApi.hh
    ${RT2_DIR}/TitanLoggerApiSimple.hh ${RT2_DIR}/PreGenRecordOf.hh
    ${RT2_DIR}/TitanLoggerControl.hh cversion.h
)

set_target_properties(ttcn3-rt2-parallel_obj PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_compile_options(ttcn3-rt2-parallel_obj PUBLIC -DTITAN_RUNTIME_2)

target_include_directories(ttcn3-rt2-parallel_obj PUBLIC
    ${LIBXML2_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${RT2_DIR}
)

add_library(ttcn3-rt2-parallel STATIC $<TARGET_OBJECTS:ttcn3-rt2-parallel_obj>)
add_library(ttcn3-rt2-parallel-dynamic SHARED $<TARGET_OBJECTS:ttcn3-rt2-parallel_obj>)

target_link_libraries(ttcn3-rt2-parallel-dynamic PUBLIC
    common-dynamic
    edit-dynamic
)

#---------------------------------------------------------------------------------------
# Target ttcn3_profmerge
#---------------------------------------------------------------------------------------
get_target_property(COMMON_INCLUDE_DIR common_obj INTERFACE_INCLUDE_DIRECTORIES)
add_library(profilertools-profmerge OBJECT ProfilerTools.cc)
target_compile_options(profilertools-profmerge PRIVATE -DPROF_MERGE)
target_include_directories(profilertools-profmerge PUBLIC ${COMMON_INCLUDE_DIR})
add_executable(ttcn3_profmerge ProfMerge_main.cc $<TARGET_OBJECTS:profilertools-profmerge>)
target_link_libraries(ttcn3_profmerge PRIVATE common)

#---------------------------------------------------------------------------------------
# Install targets
#---------------------------------------------------------------------------------------
install(TARGETS ttcn3 ttcn3-parallel ttcn3-rt2 ttcn3-rt2-parallel
                ttcn3-dynamic ttcn3-parallel-dynamic ttcn3-rt2-dynamic ttcn3-rt2-parallel-dynamic
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY ${RT2_DIR}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hh"
    PATTERN "TitanLoggerControl.hh" EXCLUDE
)

install(TARGETS ttcn3_profmerge
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hh"
    PATTERN "Array.hh" EXCLUDE
    PATTERN "ASN_Any.hh" EXCLUDE
    PATTERN "Communication.hh" EXCLUDE
    PATTERN "Fd_And_Timeout_User.hh" EXCLUDE
    PATTERN "LegacyLogger.hh" EXCLUDE
    PATTERN "LoggerPlugin.hh" EXCLUDE
    PATTERN "LoggerPluginManager.hh" EXCLUDE
    PATTERN "LoggingBits.hh" EXCLUDE
    PATTERN "LoggingParam.hh" EXCLUDE
    PATTERN "Message_types.hh" EXCLUDE
    PATTERN "String_struct.hh" EXCLUDE
    PATTERN "TCov.hh" EXCLUDE
)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/RT1
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hh"
    PATTERN "TitanLoggerControl.hh" EXCLUDE
)
