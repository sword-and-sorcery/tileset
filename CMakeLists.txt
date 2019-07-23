cmake_minimum_required(VERSION 2.8.12)
project(sword_and_sorcery)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(SOURCES src/tileset.cpp)
file(GLOB HEADERS include/tileset/*)

add_library(tileset ${SOURCES} ${HEADERS})
set_target_properties(tileset PROPERTIES CXX_STANDARD 17)
target_link_libraries(tileset PUBLIC CONAN_PKG::rapidxml CONAN_PKG::boost)

target_include_directories(
    tileset PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(TARGETS tileset
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${HEADERS}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/tileset
        PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
