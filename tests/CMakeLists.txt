cmake_minimum_required(VERSION 3.14)

project(TestsCsvReader LANGUAGES CXX)

include_directories(../src)

find_package(Qt6 COMPONENTS Core Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(TestsCsvReader tst_csvreader.cpp)

add_test(NAME TestsCsvReader COMMAND TestsCsvReader)

find_library (
    CSV_READER_LIB
    NAMES libCsvReader.dylib
    HINTS "${CMAKE_BINARY_DIR}/src"
    NO_DEFAULT_PATH
)

# check if we found the library
message(STATUS "CSV_READER_LIB: [${CSV_READER_LIB}]")

target_link_libraries(TestsCsvReader PRIVATE Qt6::Test ${CSV_READER_LIB})
