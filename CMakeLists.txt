cmake_minimum_required(VERSION 3.16)

project(QtCryptarxis VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Looks for Qt6.8.0
list(APPEND CMAKE_PREFIX_PATH "~/Qt/6.8.0/gcc_64")
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

enable_testing()

add_subdirectory(tests)
add_subdirectory(external)
add_subdirectory(src)
