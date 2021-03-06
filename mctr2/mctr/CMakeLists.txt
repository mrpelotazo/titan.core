##
## @file
## @author  Adrian Antonana
## @brief
##

#---------------------------------------------------------------------------------------
# mctr_cli not generated sources
#---------------------------------------------------------------------------------------
set(MCTR_STATIC_SOURCES MctrError.cc MainController.cc UserInterface.cc config_data.cc)

#---------------------------------------------------------------------------------------
# mctr_cli generated sources
#---------------------------------------------------------------------------------------
set(MCTR_GENERATED_SOURCES Cli_main.cc)

#---------------------------------------------------------------------------------------
# File generation commands
#---------------------------------------------------------------------------------------
add_custom_command(OUTPUT Cli_main.cc
    COMMAND echo "\\#define CLI" > Cli_main.cc
    COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/main.cc >> Cli_main.cc
)

#---------------------------------------------------------------------------------------
# Target rint
#---------------------------------------------------------------------------------------
add_library(rint OBJECT ${PROJECT_SOURCE_DIR}/core/RInt.cc)

add_dependencies(rint
    generateSources
)

#---------------------------------------------------------------------------------------
# Target textbuf
#---------------------------------------------------------------------------------------
add_library(textbuf OBJECT ${PROJECT_SOURCE_DIR}/core/Textbuf.cc)

add_dependencies(textbuf
    generateSources
)

#---------------------------------------------------------------------------------------
# Target mctr_cli
#---------------------------------------------------------------------------------------
add_executable(mctr_cli
    ${MCTR_STATIC_SOURCES}
    ${MCTR_GENERATED_SOURCES}
    $<TARGET_OBJECTS:rint>
    $<TARGET_OBJECTS:textbuf>
)

target_include_directories(mctr_cli PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/core
)

target_link_libraries(mctr_cli
    common
    cli
    edit
    OpenSSL::Crypto
    Threads::Threads
    ${CURSES_LIBRARIES}
)

#---------------------------------------------------------------------------------------
# Install targets
#---------------------------------------------------------------------------------------
install(TARGETS mctr_cli
    EXPORT ${TARGETS_EXPORT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(PROGRAMS ttcn3_start
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(CODE "execute_process( \
        COMMAND ${CMAKE_COMMAND} -E create_symlink mctr_cli mctr \
        WORKING_DIRECTORY ${CMAKE_INSTALL_FULL_BINDIR} \
    )"
)
