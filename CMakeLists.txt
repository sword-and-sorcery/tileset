cmake_minimum_required(VERSION 2.8.12)
project(sword_and_sorcery)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(SOURCES src/tileset.cpp)
# set(HEADERS include/tile.h include/tileset.h)

add_library(tileset ${SOURCES})
set_target_properties(tileset PROPERTIES CXX_STANDARD 17)
target_link_libraries(tileset PUBLIC CONAN_PKG::rapidxml CONAN_PKG::boost)

target_include_directories(
    tileset PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(
    TARGETS tileset
    EXPORT tileset-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
    EXPORT tileset-config
    NAMESPACE tileset::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)

install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
