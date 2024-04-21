cmake_minimum_required(VERSION 3.12...3.27.4)

project(craft)

FILE(GLOB SOURCE_FILES src/*.c)

add_executable(
    craft
    ${SOURCE_FILES}
    deps/lodepng/lodepng.c
    deps/noise/noise.c
    deps/sqlite/sqlite3.c
    deps/tinycthread/tinycthread.c)

add_definitions(-std=c99 -O3)

include_directories(deps/lodepng)
include_directories(deps/noise)
include_directories(deps/sqlite)
include_directories(deps/tinycthread)

if(MINGW)
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
        "C:/Program Files/CURL/lib" "C:/Program Files (x86)/CURL/lib")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH}
        "C:/Program Files/CURL/include" "C:/Program Files (x86)/CURL/include")
endif()

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

set(LINK_LIBS_PLATFORM "")

if(APPLE)
    set(LINK_LIBS_PLATFORM "")
endif()

if(UNIX)
    set(LINK_LIBS_PLATFORM "dl")
endif()

if(MINGW)
    set(LINK_LIBS_PLATFORM "ws2_32.lib")
endif()

target_compile_options(craft PRIVATE -Wall)

add_definitions(-DGLEW_STATIC)
add_subdirectory(deps/glfw EXCLUDE_FROM_ALL)
add_subdirectory(deps/glew EXCLUDE_FROM_ALL)

target_link_libraries(craft
    PRIVATE glfw
    PRIVATE libglew_static
    dl
    ${GLFW_LIBRARIES}
    ${CURL_LIBRARIES}
    ${LINK_LIBS_PLATFORM}
)

