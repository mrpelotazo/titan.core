##
## @file
## @author	Adrian Antonana
## @brief	Command Line Interface of the TTCN-3 Main Controller
##

#---------------------------------------------------------------------------------------
# Cli not generated sources
#---------------------------------------------------------------------------------------
set(CLI_STATIC_SOURCES
    Cli.cc
)

#---------------------------------------------------------------------------------------
# Bison / Flex targets
#---------------------------------------------------------------------------------------
BISON_TARGET(config_read ${CMAKE_CURRENT_SOURCE_DIR}/config_read.y ${CMAKE_CURRENT_BINARY_DIR}/config_read.tab.cc
    COMPILE_FLAGS "-p config_read_"
)

FLEX_TARGET(config_read.lex ${CMAKE_CURRENT_SOURCE_DIR}/config_read.l ${CMAKE_CURRENT_BINARY_DIR}/config_read.lex.cc
    COMPILE_FLAGS "-B -s -Cr -Cfe -Pconfig_read_"
)

ADD_FLEX_BISON_DEPENDENCY(config_read.lex config_read)

#---------------------------------------------------------------------------------------
# Target cli
#---------------------------------------------------------------------------------------
add_library(cli
	${CLI_STATIC_SOURCES}
    ${FLEX_config_read.lex_OUTPUTS}
    ${BISON_config_read_OUTPUT_SOURCE}
)

target_include_directories(cli PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)
target_compile_definitions(cli PUBLIC -D_REENTRANT)
target_link_libraries(cli PUBLIC common)
