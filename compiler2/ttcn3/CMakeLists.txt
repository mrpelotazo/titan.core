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
    ArrayDimensions.cc AST_ttcn3.cc Attributes.cc ILT.cc PatternString.cc
    RawAST.cc Statement.cc TtcnTemplate.cc Templatestuff.cc TextAST.cc
    Ttcnstuff.cc compiler.c port.c signature.c BerAST.cc JsonAST.cc Ttcn2Json.cc profiler.c
)

#---------------------------------------------------------------------------------------
# TTCN3 generated sources
#---------------------------------------------------------------------------------------
set(TTCN3_GENERATED_SOURCES
    lex.ttcn3.cc compiler.tab.cc lex.rawAST.cc rawAST.tab.cc
    charstring_la.cc pstring_la.cc comptype_attrib_la.cc coding_attrib_la.cc
    coding_attrib_p.cc ttcn3_preparser.lex.c
)

#---------------------------------------------------------------------------------------
# Target ttcn3_compiler
#---------------------------------------------------------------------------------------
add_library(ttcn3_compiler ${TTCN3_STATIC_SOURCES} ${TTCN3_GENERATED_SOURCES})
add_dependencies(ttcn3_compiler generate-common-files)
target_include_directories(ttcn3_compiler PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${PROJECT_SOURCE_DIR}
)

#---------------------------------------------------------------------------------------
# File generation commands
#---------------------------------------------------------------------------------------
add_custom_command(OUTPUT coding_attrib_p.cc coding_attrib_p.hh
    COMMAND bison -d ${CMAKE_CURRENT_LIST_DIR}/coding_attrib_p.y
    VERBATIM
)

add_custom_command(OUTPUT charstring_la.cc
    COMMAND flex -B -s -Cr -Cfe -o charstring_la.cc ${CMAKE_CURRENT_LIST_DIR}/charstring_la.l
    VERBATIM
)

add_custom_command(OUTPUT coding_attrib_la.cc
    COMMAND flex -B -s -Cr -Cfe -o coding_attrib_la.cc ${CMAKE_CURRENT_LIST_DIR}/coding_attrib_la.l
    VERBATIM
)

add_custom_command(OUTPUT comptype_attrib_la.cc
    COMMAND flex -B -s -Cr -Cfe -o comptype_attrib_la.cc ${CMAKE_CURRENT_LIST_DIR}/comptype_attrib_la.l
    VERBATIM
)

add_custom_command(OUTPUT pstring_la.cc
    COMMAND flex -B -s -Cr -Cfe -o pstring_la.cc ${CMAKE_CURRENT_LIST_DIR}/pstring_la.l
    VERBATIM
)

add_custom_command(OUTPUT compiler.tab.cc compiler.tab.hh
    COMMAND bison -d -p ttcn3_ -o compiler.tab.cc ${CMAKE_CURRENT_LIST_DIR}/compiler.y
    VERBATIM
)

add_custom_command(OUTPUT rawAST.tab.cc rawAST.tab.hh
    COMMAND bison -d -p rawAST_ -o rawAST.tab.cc ${CMAKE_CURRENT_LIST_DIR}/rawAST.y
    VERBATIM
)

add_custom_command(OUTPUT lex.ttcn3.cc
    COMMAND flex -B -s -Cr -Cfe -Pttcn3_ -o lex.ttcn3.cc ${CMAKE_CURRENT_LIST_DIR}/compiler.l
    VERBATIM
)

add_custom_command(OUTPUT lex.rawAST.cc
    COMMAND flex -B -s -Cr -Cfe -PrawAST_ -o lex.rawAST.cc ${CMAKE_CURRENT_LIST_DIR}/rawAST.l
    VERBATIM
)

add_custom_command(OUTPUT ttcn3_preparser.lex.c
    COMMAND flex -B -s -Cr -Cfe -Pttcn3_preparser_ -o ttcn3_preparser.lex.c  ${CMAKE_CURRENT_LIST_DIR}/ttcn3_preparser.l
    VERBATIM
)
