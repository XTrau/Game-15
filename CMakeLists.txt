cmake_minimum_required(VERSION 3.29)
project(MyGame_15)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(
        MyGame_15
        src/main.cpp
        src/game.cpp
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} raylib opengl32 gdi32 winmm)
elseif (UNIX)
    target_link_libraries(${PROJECT_NAME} raylib m)
endif ()
