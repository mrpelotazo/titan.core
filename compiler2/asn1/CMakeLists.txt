##
## @file
## @author     Adrian Antonana
## @brief      ASN.1 Compiler
##

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# ASN1 not generated sources
#---------------------------------------------------------------------------------------
set(ASN1_STATIC_SOURCES
    AST_asn1.cc Ref.cc Block.cc Object.cc OCSV.cc
    Tag.cc TableConstraint.cc TokenBuf.cc Type_parse.cc
)

#---------------------------------------------------------------------------------------
# ASN1 generated sources
#---------------------------------------------------------------------------------------
set(ASN1_GENERATED_SOURCES
    asn1la.yy.cc asn1p.tab.cc asn1_preparser.lex.c
)

#---------------------------------------------------------------------------------------
# Target asn1_compiler
#---------------------------------------------------------------------------------------
add_library(asn1_compiler ${ASN1_STATIC_SOURCES} ${ASN1_GENERATED_SOURCES})

target_include_directories(asn1_compiler PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#---------------------------------------------------------------------------------------
# File generation commands
#---------------------------------------------------------------------------------------
add_custom_command(OUTPUT asn1p.tab.cc asn1p.tab.hh
    COMMAND bison -d ${CMAKE_CURRENT_LIST_DIR}/asn1p.y
    VERBATIM
)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/asn1la.yy.cc
    COMMAND flex -B -s -Cr -Cfe -o asn1la.yy.cc ${CMAKE_CURRENT_SOURCE_DIR}/asn1la.l
    VERBATIM
)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/asn1_preparser.lex.c
    COMMAND flex -B -s -Cr -Cfe -Pasn1_preparser_ -o asn1_preparser.lex.c ${CMAKE_CURRENT_SOURCE_DIR}/asn1_preparser.l
    VERBATIM
)

