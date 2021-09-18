cmake_minimum_required(VERSION 3.14)

enable_testing()

project(CsvReader LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
