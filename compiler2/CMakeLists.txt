##
## @file
## @author     Adrian Antonana
## @brief      Integrated (TTCN-3 and ASN.1) compiler and the makefile generator
##

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Compiler not generated sources
#---------------------------------------------------------------------------------------
set(COMPILER_STATIC_SOURCES
    encdec.c enum.c functionref.c record.c record_of.c union.c
    PredefFunc.cc AST.cc Code.cc Constraint.cc CompilerError.cc
    CompField.cc CompType.cc EnumItem.cc Identifier.cc Int.cc
    main.cc Real.cc Setting.cc SigParam.cc string.cc subtype.cc
    Stopwatch.cc Type.cc Type_chk.cc Type_codegen.cc TypeCompat.cc
    Typestuff.cc ustring.cc Value.cc Valuestuff.cc XerAttributes.cc
    subtypestuff.cc CodeGenHelper.cc DebuggerStuff.cc XSD_Types.cc
)

set(MFGEN_SOURCES
    makefile.c xpather.cc ProjectGenHelper.cc
)

set(TCOV2LCOV_SOURCES
    tcov2lcov.cc
)

#---------------------------------------------------------------------------------------
# Target compiler
#---------------------------------------------------------------------------------------
add_executable(compiler ${COMPILER_STATIC_SOURCES})
target_link_libraries(compiler asn1_compiler ttcn3_compiler common OpenSSL::Crypto Threads::Threads)

target_include_directories(compiler PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#---------------------------------------------------------------------------------------
# Target ttcn3_makefilegen
#---------------------------------------------------------------------------------------
add_executable(ttcn3_makefilegen ${MFGEN_SOURCES})
target_link_libraries(ttcn3_makefilegen asn1_compiler ttcn3_compiler common ${LIBXML2_LIBRARIES})
target_include_directories(ttcn3_makefilegen PRIVATE ${LIBXML2_INCLUDE_DIR})

#---------------------------------------------------------------------------------------
# Target tcov2lcov
#---------------------------------------------------------------------------------------
add_executable(tcov2lcov ${TCOV2LCOV_SOURCES})
target_link_libraries(tcov2lcov ${LIBXML2_LIBRARIES})
target_include_directories(tcov2lcov PRIVATE ${LIBXML2_INCLUDE_DIR})

#---------------------------------------------------------------------------------------
# Install targets
#---------------------------------------------------------------------------------------
install(TARGETS compiler ttcn3_makefilegen tcov2lcov
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES titanver
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ
)

install(CODE "execute_process( \
        COMMAND ${CMAKE_COMMAND} -E create_symlink compiler asn1_compiler \
        WORKING_DIRECTORY ${CMAKE_INSTALL_FULL_BINDIR} \
    )"
)

install(CODE "execute_process( \
        COMMAND ${CMAKE_COMMAND} -E create_symlink compiler ttcn3_compiler \
        WORKING_DIRECTORY ${CMAKE_INSTALL_FULL_BINDIR} \
    )"
)

install(CODE "execute_process( \
        COMMAND ${CMAKE_COMMAND} -E create_symlink ttcn3_makefilegen makefilegen \
        WORKING_DIRECTORY ${CMAKE_INSTALL_FULL_BINDIR} \
    )"
)
