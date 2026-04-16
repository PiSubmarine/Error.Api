cmake_minimum_required(VERSION 3.25)

include(FetchContent)

set(_build_cmake_local "${CMAKE_CURRENT_SOURCE_DIR}/../Build.CMake/PiSubmarine.Build.CMake.cmake")

if (EXISTS "${_build_cmake_local}")
    set(PISUBMARINE_BUILD_SYSTEM "${_build_cmake_local}")
else()
    FetchContent_Declare(
            PiSubmarineBuild
            GIT_REPOSITORY "https://github.com/PiSubmarine/Build.CMake.git"
            GIT_TAG        "main"
    )

    FetchContent_MakeAvailable(PiSubmarineBuild)
    set(PISUBMARINE_BUILD_SYSTEM "${pisubmarinebuild_SOURCE_DIR}/PiSubmarine.Build.CMake.cmake")
endif()

include("${PISUBMARINE_BUILD_SYSTEM}")

PiSubmarineInitModule("PiSubmarine.Error.Api")
project(${PISUBMARINE_MODULE_NAME})
PiSubmarineConfigureModule()
