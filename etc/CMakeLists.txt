##
## @file
## @author  Adrian Antonana
## @brief   TTCN-3 etc directory
##

#---------------------------------------------------------------------------------------
# Install targets
#---------------------------------------------------------------------------------------
install(FILES CaseFolding.txt
    DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}
)

install(DIRECTORY xsd
    DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}
)

install(DIRECTORY scripts
    DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}
)