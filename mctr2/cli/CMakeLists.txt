##
## @file
## @author	Adrian Antonana
## @brief	Command Line Interface of the TTCN-3 Main Controller
##

cmake_minimum_required(VERSION 3.6)

set(CLI_STATIC_SOURCES
    Cli.cc
)

set(CLI_GENERATED_SOURCES
    config_read.lex.cc config_read.tab.cc
)

add_library(cli ${CLI_STATIC_SOURCES} ${CLI_GENERATED_SOURCES})
target_include_directories(cli PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(cli PUBLIC -D_REENTRANT)
target_link_libraries(cli PUBLIC common)

add_custom_command(OUTPUT config_read.lex.cc
    COMMAND flex -B -s -Cr -Cfe -Pconfig_read_ -o config_read.lex.cc ${CMAKE_CURRENT_SOURCE_DIR}/config_read.l
    VERBATIM
)

add_custom_command(OUTPUT config_read.tab.cc config_read.tab.hh
    COMMAND bison -d -o config_read.tab.cc -p config_read_ ${CMAKE_CURRENT_SOURCE_DIR}/config_read.y
    VERBATIM
)
