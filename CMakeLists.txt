cmake_minimum_required(VERSION 3.16)

project(Ailogger VERSION 0.1 DESCRIPTION "AiLogger Cpp" LANGUAGES C CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_VERSION_MAKEFILE ON)
IF ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    MESSAGE("CMAKE_BUILD_TYPR=Debug")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -g -Wall -Wl,--whole-archive  -lpthread -Wl,--no-whole-archive -lc -ldl")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++17 -Wl,--whole-archive  -lpthread -Wl,--no-whole-archive -lc -ldl")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0" )
    ADD_DEFINITIONS(-D _DEBUG)
    SET(OUTPUT_SUB_PATH "debug")
ELSE ()
    MESSAGE("CMAKE_BUILD_TYPE=Release")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Os -Wl,--whole-archive  -lpthread -Wl,--no-whole-archive -lc -ldl -s")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG -std=c++17 -O3 -Os -Wl,--whole-archive  -lpthread -Wl,--no-whole-archive -lc -s")
    SET(OUTPUT_SUB_PATH "release")
ENDIF ()

message("CMAKE_SYSTEM_NAME=" ${CMAKE_SYSTEM_NAME})


#Install path
SET(INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/install/${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_LIBRARY_ARCHITECTURE})
SET(INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/install/${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_LIBRARY_ARCHITECTURE})
string(TOLOWER ${INSTALL_BIN_DIR} INSTALL_BIN_DIR)
string(TOLOWER ${INSTALL_LIB_DIR} INSTALL_LIB_DIR)

message("INSTALL_LIB_DIR" =${INSTALL_LIB_DIR})
#Complier path
SET(HEADER_DIR ${PROJECT_SOURCE_DIR})

#Link directories

#Sub directories
add_subdirectory(src)


aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC)
include_directories(${CMAKE_SOURCE_DIR}/src ${CONAN_INCLUDE_DIRS} )
#add_subdirectory(${CMAKE_SOURCE_DIR}/test)


add_library(ailogger STATIC ${HEADER_LIST} ${SRC})
add_library(ailog SHARED ${HEADER_LIST} ${SRC})

install(TARGETS ailog ailogger
    LIBRARY DESTINATION lib  # 动态库安装路径
    ARCHIVE DESTINATION lib  # 静态库安装路径
    PUBLIC_HEADER DESTINATION include  # 头文件安装路径
        )