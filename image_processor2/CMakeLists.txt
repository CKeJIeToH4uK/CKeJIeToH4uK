cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0048 NEW)

project(image_processor VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(image_processor
        image_processor.cpp

        Color/color.cpp

        BmpFiles/bmp_header.cpp
        BmpFiles/dib_header.cpp
        BmpFiles/image.cpp


        MakeFilters/MakeFilters.cpp

        Filters/MainFilter.cpp
        Filters/CropFilter.cpp


        Filters/MatrixFilters/MatrixFilter.cpp
        Filters/MatrixFilters/SharpFilter.cpp
        Filters/MatrixFilters/EdgeDetectionFilter.cpp


        Filters/FormulaFIlters/FormulaFilter.cpp
        Filters/FormulaFIlters/NegativeFilter.cpp
        Filters/FormulaFIlters/GrayscaleFilter.cpp


        Filters/GaussBlurFilter.cpp

        Filters/ParallelolgrammFilter.cpp
        Filters/ParallelolgrammFilter.h
)

target_include_directories(image_processor PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Color
        ${CMAKE_CURRENT_SOURCE_DIR}/BmpFiles
        ${CMAKE_CURRENT_SOURCE_DIR}/Filters
        ${CMAKE_CURRENT_SOURCE_DIR}/Filters/MatrixFilters
        ${CMAKE_CURRENT_SOURCE_DIR}/Filters/FormulaFIlters
        ${CMAKE_CURRENT_SOURCE_DIR}/MakeFilters
)

add_library(catch_static INTERFACE)
target_include_directories(catch_static INTERFACE contrib/catch)

function(add_unit_test TARGET_NAME)
    add_executable(${TARGET_NAME} ${ARGN})
    target_link_libraries(${TARGET_NAME} catch_static)
    target_include_directories(${TARGET_NAME} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/Color
            ${CMAKE_CURRENT_SOURCE_DIR}/BmpFiles
            ${CMAKE_CURRENT_SOURCE_DIR}/Filters
            ${CMAKE_CURRENT_SOURCE_DIR}/Filters/MatrixFilters
            ${CMAKE_CURRENT_SOURCE_DIR}/Filters/FormulaFIlters
            ${CMAKE_CURRENT_SOURCE_DIR}/MakeFilters
    )
endfunction()

add_unit_test(ParallelogramTest
        TestBmpParallelogramm/Tests.cpp

        Color/color.cpp
        BmpFiles/bmp_header.cpp
        BmpFiles/dib_header.cpp
        BmpFiles/image.cpp

        MakeFilters/MakeFilters.cpp
        Filters/MainFilter.cpp
        Filters/CropFilter.cpp
        Filters/MatrixFilters/MatrixFilter.cpp
        Filters/MatrixFilters/SharpFilter.cpp
        Filters/MatrixFilters/EdgeDetectionFilter.cpp
        Filters/FormulaFIlters/FormulaFilter.cpp
        Filters/FormulaFIlters/NegativeFilter.cpp
        Filters/FormulaFIlters/GrayscaleFilter.cpp
        Filters/GaussBlurFilter.cpp
        Filters/ParallelolgrammFilter.cpp
)
