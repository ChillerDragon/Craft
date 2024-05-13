cmake_minimum_required(VERSION 3.12...3.27.4)

project(craft)

option(CURL_FROM_SOURCE "build curl from source" OFF)

FILE(GLOB CRAFT_SOURCE_FILES src/*.c)

set(ALL_SOURCES
    ${CRAFT_SOURCE_FILES}
    deps/lodepng/lodepng.c
    deps/noise/noise.c
    deps/sqlite/sqlite3.c
    deps/tinycthread/tinycthread.c
)

add_executable(craft ${ALL_SOURCES})
add_library(craftlib ${ALL_SOURCES})

add_definitions(-std=c99 -O3)

include_directories(deps/lodepng)
include_directories(deps/noise)
include_directories(deps/sqlite)
include_directories(deps/tinycthread)
include_directories(src)

if(CURL_FROM_SOURCE OR WIN32)
    include_directories(deps/curl)

    set(CURL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/curl)
    set(CURL_BUILD_DIR ${CURL_SOURCE_DIR}/build)

    if(EXISTS ${CURL_SOURCE_DIR})
        if(NOT(EXISTS ${CURL_BUILD_DIR}))
            file(MAKE_DIRECTORY ${CURL_BUILD_DIR})
        endif()
    endif()

    add_definitions(-DCURL_STATICLIB)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" ..
      RESULT_VARIABLE result
      WORKING_DIRECTORY ${CURL_BUILD_DIR}
    )
    if(result)
        message(ERROR "CMake step for curl failed: ${result}")
    else()
        execute_process(COMMAND ${CMAKE_COMMAND} --build .
          RESULT_VARIABLE result
          WORKING_DIRECTORY ${CURL_BUILD_DIR}
        )
        if(result)
            message(ERROR "Build step for curl failed: ${result}")
        endif()
    endif()


    set(CURL_INCLUDE_DIR ${CURL_SOURCE_DIR}/include)

    if(EXISTS ${CURL_BUILD_DIR}/lib/libcurl.so.4.8.0)
        set(CURL_LIBRARY ${CURL_BUILD_DIR}/lib/libcurl.so.4.8.0)
    elseif(EXISTS ${CURL_BUILD_DIR}/lib/Debug/libcurl-d_imp.lib)
        SET(CURL_LIBRARY ${CURL_BUILD_DIR}/lib/Debug/libcurl-d_imp.lib)
    elseif(EXISTS ${CURL_BUILD_DIR}/lib/Release/libcurl-d_imp.lib)
        SET(CURL_LIBRARY ${CURL_BUILD_DIR}/lib/Release/libcurl-d_imp.lib)
    else()
        message(WARNING "did not find libcurl")
    endif()

    add_subdirectory(
        ${CURL_SOURCE_DIR}
        ${CURL_BUILD_DIR}
        EXCLUDE_FROM_ALL)
endif()

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

set(LINK_LIBS_PLATFORM "")

if(APPLE)
    set(LINK_LIBS_PLATFORM "")
endif()

if(UNIX AND NOT APPLE)
    set(LINK_LIBS_PLATFORM dl m)
endif()

if(WIN32)
    set(LINK_LIBS_PLATFORM "ws2_32.lib")
endif()

# target_compile_options(craft PRIVATE -Wall -Wno-format-truncation)

add_definitions(-DGLEW_STATIC)
add_subdirectory(deps/glfw EXCLUDE_FROM_ALL)
add_subdirectory(deps/glew EXCLUDE_FROM_ALL)

set(CRAFT_DEPS
    ${GLFW_LIBRARIES}
    ${CURL_LIBRARIES}
    ${LINK_LIBS_PLATFORM}
)

target_link_libraries(craft
    PRIVATE glfw
    PRIVATE libglew_static
    ${CRAFT_DEPS}
)
target_link_libraries(craftlib
    PRIVATE glfw
    PRIVATE libglew_static
    ${CRAFT_DEPS}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data)

include(CTest)

add_executable(TestCraft tests/test_matrix.c
)
target_link_libraries(TestCraft
    PRIVATE glfw
    PRIVATE libglew_static
    craftlib)
add_test(NAME TestCraft
         COMMAND TestCraft)

