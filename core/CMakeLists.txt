##
## @file
## @author  Adrian Antonana
## @brief   Base Library of TTCN-3 Test Executor
##

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
    Module_list.cc Objid.cc Octetstring.cc OER.cc Port.cc RAW.cc
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
add_custom_target(generateSources
    DEPENDS ${RT1_DIR}/TitanLoggerApi.hh ${RT1_DIR}/TitanLoggerApi.cc
            ${RT2_DIR}/TitanLoggerApi.hh ${RT2_DIR}/TitanLoggerApi.cc
            ${RT1_DIR}/TitanLoggerApiSimple.hh ${RT2_DIR}/TitanLoggerApiSimple.hh
            ${RT1_DIR}/TitanLoggerControl.hh ${RT1_DIR}/TitanLoggerControl.cc
            ${RT2_DIR}/TitanLoggerControl.hh ${RT2_DIR}/TitanLoggerControl.cc
            ${RT1_DIR}/PreGenRecordOf.hh ${RT1_DIR}/PreGenRecordOf.cc
            ${RT2_DIR}/PreGenRecordOf.hh ${RT2_DIR}/PreGenRecordOf.cc
)

add_custom_command(
    OUTPUT ${RT1_DIR} ${RT2_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RT1_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RT2_DIR}
)

add_custom_command(
    DEPENDS xsd2ttcn compiler
            ${RT1_DIR} ${RT2_DIR}
    OUTPUT  ${GENERATED_MODULE}
            ${RT1_DIR}/TitanLoggerApi.hh ${RT1_DIR}/TitanLoggerApi.cc
            ${RT2_DIR}/TitanLoggerApi.hh ${RT2_DIR}/TitanLoggerApi.cc
    COMMAND ${PROJECT_BINARY_DIR}/xsdconvert/xsd2ttcn ${CMAKE_CURRENT_SOURCE_DIR}/${SCHEMA} &&
            ${SED} -i -e 's/XSD.String/charstring/g' -e 's/XSD.AnySimpleType/charstring/g' -e 's/XSD.Integer/integer/g' -e 's/XSD.Float/float/g' -e 's/XSD.Double/float/g' -e 's/XSD.Boolean/boolean/g' -e 's/import\ from\ XSD\ all\;//g' ${GENERATED_MODULE} &&
            ${PROJECT_BINARY_DIR}/compiler2/compiler -o ${RT1_DIR} ${GENERATED_MODULE} &&
            ${PROJECT_BINARY_DIR}/compiler2/compiler -R -o ${RT2_DIR} ${GENERATED_MODULE}
    COMMENT "Generating logger API sources"
)

add_custom_command(
    DEPENDS ${RT1_DIR}/TitanLoggerApi.hh
            ${RT2_DIR}/TitanLoggerApi.hh
    OUTPUT  ${RT1_DIR}/TitanLoggerApiSimple.hh ${RT2_DIR}/TitanLoggerApiSimple.hh
    COMMAND ${PERL_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/simplify.pl ${RT1_DIR}/TitanLoggerApi.hh > ${RT1_DIR}/TitanLoggerApiSimple.hh
    COMMAND ${PERL_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/simplify.pl ${RT2_DIR}/TitanLoggerApi.hh > ${RT2_DIR}/TitanLoggerApiSimple.hh
    COMMENT "Generating simple logger API sources"
)

add_custom_command(
    DEPENDS compiler
            ${RT1_DIR} ${RT2_DIR}
    OUTPUT  ${RT1_DIR}/PreGenRecordOf.hh ${RT1_DIR}/PreGenRecordOf.cc
            ${RT2_DIR}/PreGenRecordOf.hh ${RT2_DIR}/PreGenRecordOf.cc
    COMMAND ${PROJECT_BINARY_DIR}/compiler2/compiler -F -o ${RT1_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${PREGENERATOR_MODULES}
    COMMAND ${PROJECT_BINARY_DIR}/compiler2/compiler -F -R -o ${RT2_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${PREGENERATOR_MODULES}
    COMMENT "Generating pregenerator sources"
)

add_custom_command(
    DEPENDS compiler
            ${RT1_DIR} ${RT2_DIR}
    OUTPUT  ${RT1_DIR}/TitanLoggerControl.hh ${RT1_DIR}/TitanLoggerControl.cc
            ${RT2_DIR}/TitanLoggerControl.hh ${RT2_DIR}/TitanLoggerControl.cc
    COMMAND ${PROJECT_BINARY_DIR}/compiler2/compiler -F -o ${RT1_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/TitanLoggerControl.ttcn
    COMMAND ${PROJECT_BINARY_DIR}/compiler2/compiler -F -R -o ${RT2_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/TitanLoggerControl.ttcn
    COMMENT "Generating logger control sources"
)

#---------------------------------------------------------------------------------------
# Bison / Flex targets
#---------------------------------------------------------------------------------------
BISON_TARGET(config_process ${CMAKE_CURRENT_SOURCE_DIR}/config_process.y ${CMAKE_CURRENT_BINARY_DIR}/config_process.tab.cc
    COMPILE_FLAGS "-p config_process_"
)

FLEX_TARGET(config_process.lex ${CMAKE_CURRENT_SOURCE_DIR}/config_process.l ${CMAKE_CURRENT_BINARY_DIR}/config_process.lex.cc
    COMPILE_FLAGS "-B -s -Cr -Cfe -Pconfig_process_"
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/config_process.lex.hh"
)

ADD_FLEX_BISON_DEPENDENCY(config_process.lex config_process)

#---------------------------------------------------------------------------------------
# Target gccversion
#---------------------------------------------------------------------------------------
add_executable(gccversion gccversion.c)

add_custom_target(cversionHeader
    COMMAND gccversion > ${CMAKE_BINARY_DIR}/cversion.h
    DEPENDS gccversion
    BYPRODUCTS ${CMAKE_BINARY_DIR}/cversion.h
)

#---------------------------------------------------------------------------------------
# Target logger-plugin
#---------------------------------------------------------------------------------------
add_library(logger-plugin_obj OBJECT
    LoggerPlugin_static.cc
)

add_dependencies(logger-plugin_obj
    cversionHeader
    generateSources
)

target_include_directories(logger-plugin_obj PRIVATE
    ${PROJECT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_BINARY_DIR}
)

add_library(logger-plugin-dynamic_obj OBJECT
    LoggerPlugin_dynamic.cc
)

add_dependencies(logger-plugin-dynamic_obj
    cversionHeader
    generateSources
)

set_target_properties(logger-plugin-dynamic_obj PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

target_include_directories(logger-plugin-dynamic_obj PRIVATE
    ${PROJECT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_BINARY_DIR}
)

#---------------------------------------------------------------------------------------
# Target ttcn3
#---------------------------------------------------------------------------------------
add_library(ttcn3_obj OBJECT ${CORE_STATIC_SOURCES_NO_MAIN}
    Single_main.cc
    ${FLEX_config_process.lex_OUTPUTS}
    ${BISON_config_process_OUTPUT_SOURCE}
)

add_dependencies(ttcn3_obj
    cversionHeader
    generateSources
)

set_target_properties(ttcn3_obj PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

target_include_directories(ttcn3_obj PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_BINARY_DIR}
    ${RT1_DIR}
    ${LIBXML2_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}
)

add_library(ttcn3 STATIC
    $<TARGET_OBJECTS:ttcn3_obj>
    $<TARGET_OBJECTS:common_obj>
    $<TARGET_OBJECTS:logger-plugin_obj>
)

add_library(ttcn3-dynamic SHARED
    $<TARGET_OBJECTS:ttcn3_obj>
    $<TARGET_OBJECTS:common_obj>
    $<TARGET_OBJECTS:logger-plugin-dynamic_obj>
)

target_compile_definitions(ttcn3 INTERFACE
    -DLINUX
)

target_compile_definitions(ttcn3-dynamic INTERFACE
    -DLINUX
)

target_link_libraries(ttcn3-dynamic PUBLIC
    ${LIBEDIT}
)

target_include_directories(ttcn3 INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${RT1_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_include_directories(ttcn3-dynamic INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${RT1_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

#---------------------------------------------------------------------------------------
# Target ttcn3-parallel
#---------------------------------------------------------------------------------------
add_library(ttcn3-parallel_obj OBJECT ${CORE_STATIC_SOURCES_NO_MAIN}
    Parallel_main.cc
    ${FLEX_config_process.lex_OUTPUTS}
    ${BISON_config_process_OUTPUT_SOURCE}
)

add_dependencies(ttcn3-parallel_obj
    cversionHeader
    generateSources
)

target_include_directories(ttcn3-parallel_obj PUBLIC
    ${LIBXML2_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${RT1_DIR}
    ${CMAKE_BINARY_DIR}

)

set_target_properties(ttcn3-parallel_obj PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

add_library(ttcn3-parallel STATIC
    $<TARGET_OBJECTS:ttcn3-parallel_obj>
    $<TARGET_OBJECTS:common_obj>
    $<TARGET_OBJECTS:logger-plugin_obj>
)

add_library(ttcn3-parallel-dynamic SHARED
    $<TARGET_OBJECTS:ttcn3-parallel_obj>
    $<TARGET_OBJECTS:common_obj>
    $<TARGET_OBJECTS:logger-plugin-dynamic_obj>
)

target_link_libraries(ttcn3-parallel-dynamic PUBLIC
    ${LIBEDIT}
)

target_compile_definitions(ttcn3-parallel INTERFACE
    -DLINUX
)

target_compile_definitions(ttcn3-parallel-dynamic INTERFACE
    -DLINUX
)

target_include_directories(ttcn3-parallel INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${RT1_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_include_directories(ttcn3-parallel-dynamic INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${RT1_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

#---------------------------------------------------------------------------------------
# Target ttcn3-rt2
#---------------------------------------------------------------------------------------
add_library(ttcn3-rt2_obj OBJECT ${CORE2_STATIC_SOURCES}
    Single_main.cc
    ${FLEX_config_process.lex_OUTPUTS}
    ${BISON_config_process_OUTPUT_SOURCE}
)

add_dependencies(ttcn3-rt2_obj
    cversionHeader
    generateSources
)

set_target_properties(ttcn3-rt2_obj PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_compile_options(ttcn3-rt2_obj PUBLIC -DTITAN_RUNTIME_2)

target_include_directories(ttcn3-rt2_obj PUBLIC
    ${LIBXML2_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${RT2_DIR}
    ${CMAKE_BINARY_DIR}
)

add_library(ttcn3-rt2 STATIC
    $<TARGET_OBJECTS:ttcn3-rt2_obj>
    $<TARGET_OBJECTS:common_obj>
    $<TARGET_OBJECTS:logger-plugin_obj>
)

add_library(ttcn3-rt2-dynamic SHARED
    $<TARGET_OBJECTS:ttcn3-rt2_obj>
    $<TARGET_OBJECTS:common_obj>
    $<TARGET_OBJECTS:logger-plugin-dynamic_obj>
)

target_compile_definitions(ttcn3-rt2 INTERFACE
    -DLINUX
)

target_compile_definitions(ttcn3-rt2-dynamic INTERFACE
    -DLINUX
)

target_link_libraries(ttcn3-rt2-dynamic PUBLIC
    ${LIBEDIT}
)

target_include_directories(ttcn3-rt2 INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${RT2_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_include_directories(ttcn3-rt2-dynamic INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${RT2_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

#---------------------------------------------------------------------------------------
# Target ttcn3-rt2-parallel
#---------------------------------------------------------------------------------------
add_library(ttcn3-rt2-parallel_obj OBJECT ${CORE2_STATIC_SOURCES}
    Parallel_main.cc
    ${FLEX_config_process.lex_OUTPUTS}
    ${BISON_config_process_OUTPUT_SOURCE}
)

add_dependencies(ttcn3-rt2-parallel_obj
    cversionHeader
    generateSources
)

set_target_properties(ttcn3-rt2-parallel_obj PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_compile_options(ttcn3-rt2-parallel_obj PUBLIC -DTITAN_RUNTIME_2)

target_include_directories(ttcn3-rt2-parallel_obj PUBLIC
    ${LIBXML2_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${RT2_DIR}
    ${CMAKE_BINARY_DIR}
)

add_library(ttcn3-rt2-parallel STATIC
    $<TARGET_OBJECTS:ttcn3-rt2-parallel_obj>
    $<TARGET_OBJECTS:common_obj>
    $<TARGET_OBJECTS:logger-plugin_obj>
)

add_library(ttcn3-rt2-parallel-dynamic SHARED
    $<TARGET_OBJECTS:ttcn3-rt2-parallel_obj>
    $<TARGET_OBJECTS:common_obj>
    $<TARGET_OBJECTS:logger-plugin-dynamic_obj>
)

target_compile_definitions(ttcn3-rt2-parallel INTERFACE
    -DLINUX
)

target_compile_definitions(ttcn3-rt2-parallel-dynamic INTERFACE
    -DLINUX
)

target_link_libraries(ttcn3-rt2-parallel-dynamic PUBLIC
    ${LIBEDIT}
)

target_include_directories(ttcn3-rt2-parallel INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${RT2_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_include_directories(ttcn3-rt2-parallel-dynamic INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${RT2_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
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
                ttcn3_profmerge
    EXPORT ${TARGETS_EXPORT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${RT2_DIR}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hh"
    PATTERN "TitanLoggerControl.hh" EXCLUDE
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hh" PATTERN "*.h"
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

install(FILES ${CMAKE_BINARY_DIR}/cversion.h
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
