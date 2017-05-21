##
## @file
## @author     Adrian Antonana
## @brief
##

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# xsd2ttcn not generated sources
#---------------------------------------------------------------------------------------
set(STATIC_SOURCES
    converter.cc XMLParser.cc TTCN3Module.cc TTCN3ModuleInventory.cc
    RootType.cc SimpleType.cc AttributeType.cc ComplexType.cc Annotation.cc
    ImportStatement.cc PredefinedModules.cc GeneralFunctions.cc Mstring.cc Constant.cc
)

#---------------------------------------------------------------------------------------
# Target xsd2ttcn
#---------------------------------------------------------------------------------------
add_executable(xsd2ttcn ${STATIC_SOURCES})
target_include_directories(xsd2ttcn PRIVATE ${LIBXML2_INCLUDE_DIR})
target_link_libraries(xsd2ttcn common ${LIBXML2_LIBRARIES} OpenSSL::Crypto)

#---------------------------------------------------------------------------------------
# Install target
#---------------------------------------------------------------------------------------
install(TARGETS xsd2ttcn
    EXPORT ${TARGETS_EXPORT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
