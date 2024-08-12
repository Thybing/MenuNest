cmake_minimum_required(VERSION 3.10)
project(MenuNest VERSION 1.0.0)

set(CMAKE_C_STANDARD 99)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(    ${PROJECT_SOURCE_DIR}
                        ${PROJECT_SOURCE_DIR}/inc
                        )

file(GLOB SRC_LIST  ${PROJECT_SOURCE_DIR}/src/*.c
                    ${PROJECT_SOURCE_DIR}/src/menu_nest/*.c
                    )

add_executable(${PROJECT_NAME} ${SRC_LIST})