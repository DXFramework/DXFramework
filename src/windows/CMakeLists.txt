cmake_minimum_required(VERSION 3.5)
project(DXFrameworkWindows)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(libs/SDL)

if(MSVC)

else()

endif()

set(SOURCE "DXFramework.cpp")

add_executable(DXFramework ${SOURCE})
target_include_directories(DXFramework PUBLIC libs/SDL/include)
target_link_libraries(DXFramework PUBLIC SDL2)