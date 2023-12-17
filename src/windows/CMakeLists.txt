cmake_minimum_required(VERSION 3.5)
project(DXFrameworkWindows)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(libs/SDL)

find_package(OpenGL REQUIRED)

if(MSVC)

else()

endif()

set(SOURCE "DXFramework.cpp" "graphics/vertex_buffer.h" "graphics/shader.h" "graphics/shader.cpp" "graphics/index_buffer.h")

add_executable(DXFramework ${SOURCE})
target_include_directories(DXFramework PUBLIC libs/SDL/include)
target_link_libraries(DXFramework PUBLIC SDL2)
target_include_directories(DXFramework PUBLIC libs/glew/include)
target_link_libraries(DXFramework PUBLIC ${PROJECT_SOURCE_DIR}/libs/glew/lib/Release/x64/glew32s.lib)
target_link_libraries(DXFramework PUBLIC opengl32)