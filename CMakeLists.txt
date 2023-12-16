cmake_minimum_required(VERSION 3.0)
project(DXFramework)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

if(WIN32)
    set(external_projectpath "src/windows")
elseif(UNIX)
    if(CMAKE_SYSTEM_NAME MATCHES "Linux")
        set(external_projectpath "src/linux")
    elseif(CMAKE_SYSTEM_NAME MATCHES "BSD")
        set(external_projectpath "src/freebsd")
    endif()
endif()

add_subdirectory(${external_projectpath})