##
## @file
## @author     Adrian Antonana
## @brief      TTCN-3 log formatter, log merger and HTML report generator
##

#---------------------------------------------------------------------------------------
# Bison / Flex targets
#---------------------------------------------------------------------------------------
FLEX_TARGET(logformat ${CMAKE_CURRENT_SOURCE_DIR}/logformat.l ${CMAKE_CURRENT_BINARY_DIR}/logformat.c
    COMPILE_FLAGS "-B -s -Cr -Cfe"
)

FLEX_TARGET(parser ${CMAKE_CURRENT_SOURCE_DIR}/parser.l ${CMAKE_CURRENT_BINARY_DIR}/parser.c
    COMPILE_FLAGS "-B -s -Cr -Cfe"
)

#---------------------------------------------------------------------------------------
# Targets logmerge, logfilter, logformat, repgen
#---------------------------------------------------------------------------------------
add_executable(ttcn3_logmerge logmerge.c)
target_link_libraries(ttcn3_logmerge common)

add_executable(ttcn3_logfilter logfilter.c)
target_link_libraries(ttcn3_logfilter common)

add_executable(ttcn3_logformat ${FLEX_logformat_OUTPUTS})
target_link_libraries(ttcn3_logformat common)

add_executable(ttcn3_repgen ${FLEX_parser_OUTPUTS} repgen.c)
target_include_directories(ttcn3_repgen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ttcn3_repgen common)

#---------------------------------------------------------------------------------------
# Install targets
#---------------------------------------------------------------------------------------
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
