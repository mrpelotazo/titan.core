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
# Bison / Flex targets
#---------------------------------------------------------------------------------------
BISON_TARGET(asn1p ${CMAKE_CURRENT_SOURCE_DIR}/asn1p.y ${CMAKE_CURRENT_BINARY_DIR}/asn1p.tab.cc)

FLEX_TARGET(asn1la ${CMAKE_CURRENT_SOURCE_DIR}/asn1la.l ${CMAKE_CURRENT_BINARY_DIR}/asn1la.yy.cc
    COMPILE_FLAGS "-B -s -Cr -Cfe"
)

FLEX_TARGET(asn1_preparser ${CMAKE_CURRENT_SOURCE_DIR}/asn1_preparser.l ${CMAKE_CURRENT_BINARY_DIR}/asn1_preparser.lex.c
    COMPILE_FLAGS "-B -s -Cr -Cfe -Pasn1_preparser_"
)

ADD_FLEX_BISON_DEPENDENCY(asn1la asn1p)
ADD_FLEX_BISON_DEPENDENCY(asn1_preparser asn1p)

#---------------------------------------------------------------------------------------
# Target asn1_compiler
#---------------------------------------------------------------------------------------
add_library(asn1_compiler
    ${ASN1_STATIC_SOURCES}
    ${BISON_asn1p_OUTPUT_SOURCE}
    ${FLEX_asn1la_OUTPUTS}
    ${FLEX_asn1_preparser_OUTPUTS}
)

target_include_directories(asn1_compiler PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)