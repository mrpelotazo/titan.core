##
## @file
## @author     Adrian Antonana
## @brief      TTCN-3 log formatter, log merger and HTML report generator
##

cmake_minimum_required(VERSION 3.6)

add_executable(ttcn3_logmerge logmerge.c)
target_link_libraries(ttcn3_logmerge common)

add_executable(ttcn3_logfilter logfilter.c)
target_link_libraries(ttcn3_logfilter common)

add_executable(ttcn3_logformat ${CMAKE_CURRENT_BINARY_DIR}/logformat.c)
target_link_libraries(ttcn3_logformat common)

add_executable(ttcn3_repgen ${CMAKE_CURRENT_BINARY_DIR}/parser.c repgen.c)
target_include_directories(ttcn3_repgen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ttcn3_repgen common)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/logformat.c
    COMMAND flex -B -s -Cr -Cfe -o logformat.c ${CMAKE_CURRENT_SOURCE_DIR}/logformat.l
    VERBATIM
)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/parser.c
    COMMAND flex -B -s -Cr -Cfe -o parser.c ${CMAKE_CURRENT_SOURCE_DIR}/parser.l
    VERBATIM
)

install(TARGETS ttcn3_repgen ttcn3_logformat ttcn3_logfilter ttcn3_logmerge
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(CODE "execute_process( \
        COMMAND ${CMAKE_COMMAND} -E create_symlink ttcn3_repgen repgen \
        WORKING_DIRECTORY ${CMAKE_INSTALL_FULL_BINDIR} \
    )"
)

install(CODE "execute_process( \
        COMMAND ${CMAKE_COMMAND} -E create_symlink ttcn3_logformat logformat \
        WORKING_DIRECTORY ${CMAKE_INSTALL_FULL_BINDIR} \
    )"
)
