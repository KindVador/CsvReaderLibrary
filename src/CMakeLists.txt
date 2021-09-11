cmake_minimum_required(VERSION 3.14)

project(CsvReader LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_library(CsvReader SHARED
            csvreader.cpp
            csvreader.hpp
            gmtfield.cpp
            gmtfield.hpp)

target_link_libraries(CsvReader PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(CsvReader PRIVATE CSVREADER_LIBRARY)
