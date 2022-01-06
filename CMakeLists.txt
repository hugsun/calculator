cmake_minimum_required(VERSION 3.10.2)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set(CMAKE_C_STANDARD 11)

include_directories("src/include")

if (WIN32)
    set(DEPS gtk+-3.0)
elseif (APPLE)
    set(DEPS gtk+-3.0 glib-2.0)
else()
    set(DEPS gtk+-3.0)
endif ()

FIND_PACKAGE(PkgConfig REQUIRED)
foreach (dep ${DEPS})
    PKG_CHECK_MODULES(${dep} REQUIRED ${dep})

    INCLUDE_DIRECTORIES(${${dep}_INCLUDE_DIRS})
    LINK_DIRECTORIES(${${dep}_LIBRARY_DIRS})
endforeach ()

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_executable(${ProjectId} ${files})

foreach (dep ${DEPS})
    target_link_libraries(${ProjectId} ${${dep}_LIBRARIES})
endforeach ()