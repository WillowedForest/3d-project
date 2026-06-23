cmake_minimum_required(VERSION 4.2)
project(the_cube)

set(CMAKE_CXX_STANDARD 26)
find_package(raylib REQUIRED)


add_executable(the_cube main.cpp)

target_link_libraries(${PROJECT_NAME}
        raylib
        GL
        m
        pthread
        dl
        rt
        X11
)