cmake_minimum_required(VERSION 3.25)
project(lab_3 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_3 main.c)

find_package(X11 REQUIRED)
target_link_libraries(lab_3 ${X11_LIBRARIES})
target_include_directories(lab_3 PUBLIC ${X11_INCLUDE_DIR})
target_link_libraries(lab_3 m)