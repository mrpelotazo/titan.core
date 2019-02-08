find_program(ADOC_BIN
    NAMES asciidoctor-pdf
          asciidoctor-pdf.ruby2.5
)

if(NOT ADOC_BIN)
    message(FATAL_ERROR "asciidoctor-pdf not found")
else()
    set(ADOC_CMD ${ADOC_BIN} --attribute skip-front-matter --destination-dir ${CMAKE_CURRENT_BINARY_DIR})
    set(GENERATED_DOCS
            ${CMAKE_CURRENT_BINARY_DIR}/Apiguide.pdf
            ${CMAKE_CURRENT_BINARY_DIR}/installationguide.pdf
            ${CMAKE_CURRENT_BINARY_DIR}/PRI.pdf
            ${CMAKE_CURRENT_BINARY_DIR}/ReferenceGuide.pdf
            ${CMAKE_CURRENT_BINARY_DIR}/releasenotes.pdf
            ${CMAKE_CURRENT_BINARY_DIR}/SoC_TITAN.pdf
            ${CMAKE_CURRENT_BINARY_DIR}/SoC_XML_TITAN.pdf
            ${CMAKE_CURRENT_BINARY_DIR}/UserGuide.pdf
    )
endif()

add_custom_target(build-documentation ALL
    DEPENDS ${GENERATED_DOCS}
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Apiguide.pdf
    DEPENDS apiguide/*.adoc apiguide/images/*
    COMMAND ${ADOC_CMD} ${CMAKE_CURRENT_SOURCE_DIR}/apiguide/Apiguide.adoc
    COMMENT "Generating API guide"
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/installationguide.pdf
    DEPENDS installationguide/*.adoc installationguide/images/*
    COMMAND ${ADOC_CMD} ${CMAKE_CURRENT_SOURCE_DIR}/installationguide/installationguide.adoc
    COMMENT "Generating installation guide"
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/PRI.pdf
    DEPENDS PRI/*.adoc
    COMMAND ${ADOC_CMD} ${CMAKE_CURRENT_SOURCE_DIR}/PRI/PRI.adoc
    COMMENT "Generating PRI document"
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ReferenceGuide.pdf
    DEPENDS referenceguide/*.adoc referenceguide/images/*
    COMMAND ${ADOC_CMD} ${CMAKE_CURRENT_SOURCE_DIR}/referenceguide/ReferenceGuide.adoc
    COMMENT "Generating reference guide"
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/releasenotes.pdf
    DEPENDS releasenotes/*.adoc releasenotes/images/*
    COMMAND ${ADOC_CMD} ${CMAKE_CURRENT_SOURCE_DIR}/releasenotes/releasenotes.adoc
    COMMENT "Generating release notes document"
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/SoC_TITAN.pdf
    DEPENDS SoC_TITAN/*.adoc SoC_TITAN/images/*
    COMMAND ${ADOC_CMD} ${CMAKE_CURRENT_SOURCE_DIR}/SoC_TITAN/SoC_TITAN.adoc
    COMMENT "Generating SoC document"
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/SoC_XML_TITAN.pdf
    DEPENDS SoC_XML_TITAN/*.adoc SoC_XML_TITAN/images/*
    COMMAND ${ADOC_CMD} ${CMAKE_CURRENT_SOURCE_DIR}/SoC_XML_TITAN/SoC_XML_TITAN.adoc
    COMMENT "Generating SoC XML document"
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/UserGuide.pdf
    DEPENDS userguide/*.adoc userguide/images/*
    COMMAND ${ADOC_CMD} ${CMAKE_CURRENT_SOURCE_DIR}/userguide/UserGuide.adoc
    COMMENT "Generating user guide"
)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
    FILES_MATCHING PATTERN "*.pdf"
)
