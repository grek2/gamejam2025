cmake_minimum_required(VERSION 3.20)

project(Myproject)
set(target_name my_project)
add_executable(${target_name} helloWindow.cpp)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG "master"
    GIT_SHALLOW 1
)

FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Sunday111/glad
    GIT_TAG "main"
    GIT_SHALLOW 1
)

FetchContent_MakeAvailable(glad)

target_link_libraries(${target_name} PUBLIC glfw glad)