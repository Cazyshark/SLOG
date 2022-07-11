cmake_minimum_required(VERSION 3.16)

project(test)

LINK_DIRECTORIES(
        ${LINK_LIBRARIES_DIR}
)

add_executable(${PROJECT_NAME} ./)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN_LIBS} ailogger ${LIBS})