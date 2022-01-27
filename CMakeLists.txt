cmake_minimum_required(VERSION 3.20)
project(AED_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(AED_2 main.cpp Code/ReadCsv.cpp Code/ReadCsv.h Code/Graph.cpp Code/Graph.h Code/MinHeap.h Code/STCPManager.cpp Code/STCPManager.h Code/Stop.cpp Code/Stop.h Code/Line.cpp Code/Line.h Code/Trip.cpp Code/Trip.h Code/Interface.cpp Code/Interface.h)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)