cmake_minimum_required(VERSION 3.10)
set(BUILD pod_serial)
project(${BUILD})

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_executable(${BUILD}
    ${CMAKE_SOURCE_DIR}/main.cpp
)

target_include_directories(${BUILD} PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# print the size of the executable
add_custom_command(TARGET ${BUILD} POST_BUILD
    COMMAND size "$<TARGET_FILE:${BUILD}>"
)
