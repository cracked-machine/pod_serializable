cmake_minimum_required(VERSION 3.10)
project(pod_serial)

add_executable(pod_serial 
    ${CMAKE_SOURCE_DIR}/main.cpp
)

target_include_directories(pod_serial PRIVATE
    ${CMAKE_SOURCE_DIR}
)