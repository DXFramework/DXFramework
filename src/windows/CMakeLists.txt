cmake_minimum_required(VERSION 3.0)
project(DXFrameworkWindows)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)

else()

endif()

set(SOURCE "DXFramework.cpp")

add_executable(DXFramework ${SOURCE})