##
## @file
## @author     Adrian Antonana
## @brief      TTCN-3 part of the compiler 
##

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# TTCN3 not generated sources
#---------------------------------------------------------------------------------------
set(TTCN3_STATIC_SOURCES
    ArrayDimensions.cc AST_ttcn3.cc Attributes.cc ILT.cc OerAST.cc PatternString.cc
    RawAST.cc Statement.cc TtcnTemplate.cc Templatestuff.cc TextAST.cc
    Ttcnstuff.cc compiler.c port.c signature.c BerAST.cc JsonAST.cc Ttcn2Json.cc profiler.c
)

#---------------------------------------------------------------------------------------
# Bison / Flex targets
#---------------------------------------------------------------------------------------
BISON_TARGET(coding_attrib_p ${CMAKE_CURRENT_SOURCE_DIR}/coding_attrib_p.y ${CMAKE_CURRENT_BINARY_DIR}/coding_attrib_p.cc)

FLEX_TARGET(charstring_la ${CMAKE_CURRENT_SOURCE_DIR}/charstring_la.l ${CMAKE_CURRENT_BINARY_DIR}/charstring_la.cc
    COMPILE_FLAGS "-B -s -Cr -Cfe"
)

FLEX_TARGET(coding_attrib_la ${CMAKE_CURRENT_SOURCE_DIR}/coding_attrib_la.l ${CMAKE_CURRENT_BINARY_DIR}/coding_attrib_la.cc
    COMPILE_FLAGS "-B -s -Cr -Cfe"
)

FLEX_TARGET(comptype_attrib_la ${CMAKE_CURRENT_SOURCE_DIR}/comptype_attrib_la.l ${CMAKE_CURRENT_BINARY_DIR}/comptype_attrib_la.cc
    COMPILE_FLAGS "-B -s -Cr -Cfe"
)

FLEX_TARGET(pstring_la ${CMAKE_CURRENT_SOURCE_DIR}/pstring_la.l ${CMAKE_CURRENT_BINARY_DIR}/pstring_la.cc
    COMPILE_FLAGS "-B -s -Cr -Cfe"
)

BISON_TARGET(compiler.tab ${CMAKE_CURRENT_SOURCE_DIR}/compiler.y ${CMAKE_CURRENT_BINARY_DIR}/compiler.tab.cc
    COMPILE_FLAGS "-p ttcn3_"
)

BISON_TARGET(rawAST.tab ${CMAKE_CURRENT_SOURCE_DIR}/rawAST.y ${CMAKE_CURRENT_BINARY_DIR}/rawAST.tab.cc
    COMPILE_FLAGS "-p rawAST_"
)

FLEX_TARGET(lex.ttcn3 ${CMAKE_CURRENT_SOURCE_DIR}/compiler.l ${CMAKE_CURRENT_BINARY_DIR}/lex.ttcn3.cc
    COMPILE_FLAGS "-B -s -Cr -Cfe -Pttcn3_"
)

FLEX_TARGET(lex.rawAST ${CMAKE_CURRENT_SOURCE_DIR}/rawAST.l ${CMAKE_CURRENT_BINARY_DIR}/lex.rawAST.cc
    COMPILE_FLAGS "-B -s -Cr -Cfe -PrawAST_"
)

FLEX_TARGET(ttcn3_preparser.lex ${CMAKE_CURRENT_SOURCE_DIR}/ttcn3_preparser.l ${CMAKE_CURRENT_BINARY_DIR}/ttcn3_preparser.lex.c
    COMPILE_FLAGS "-B -s -Cr -Cfe -Pttcn3_preparser_"
)

ADD_FLEX_BISON_DEPENDENCY(coding_attrib_la coding_attrib_p)
ADD_FLEX_BISON_DEPENDENCY(lex.ttcn3 compiler.tab)
ADD_FLEX_BISON_DEPENDENCY(lex.rawAST rawAST.tab)

#---------------------------------------------------------------------------------------
# Target ttcn3_compiler
#---------------------------------------------------------------------------------------
add_library(ttcn3_compiler
    ${TTCN3_STATIC_SOURCES}
    ${FLEX_charstring_la_OUTPUTS}
    ${FLEX_coding_attrib_la_OUTPUTS}
    ${FLEX_comptype_attrib_la_OUTPUTS}
    ${FLEX_pstring_la_OUTPUTS}
    ${FLEX_lex.ttcn3_OUTPUTS}
    ${FLEX_lex.rawAST_OUTPUTS}
    ${FLEX_ttcn3_preparser.lex_OUTPUTS}
    ${BISON_coding_attrib_p_OUTPUT_SOURCE}
    ${BISON_compiler.tab_OUTPUT_SOURCE}
    ${BISON_rawAST.tab_OUTPUT_SOURCE}
)

add_dependencies(ttcn3_compiler common_obj)

target_include_directories(ttcn3_compiler PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)
