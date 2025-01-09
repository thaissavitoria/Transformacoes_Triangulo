cmake_minimum_required(VERSION 3.27.6)

project(Matrizes)

add_executable(Matrizes Matrizes.cpp)


target_include_directories(Matrizes PRIVATE dependencias/glm
                                            dependencias/stb
                                            dependencias/glfw/include
                                            dependencias/glew/include)

target_link_directories(Matrizes PRIVATE dependencias/glfw/lib-vc2022
                                         dependencias/glew/lib/Release/x64)

target_link_libraries(Matrizes PRIVATE glfw3.lib
                                       glew32.lib
                                       opengl32.lib)

add_custom_command(TARGET Matrizes POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   -E copy "${CMAKE_SOURCE_DIR}/dependencias/glew/bin/Release/x64/glew32.dll"
                   "${CMAKE_BINARY_DIR}")