cmake_minimum_required(VERSION 3.30)
project(tic_tac_toe C)

set(CMAKE_C_STANDARD 23)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

function(include_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
        GIT_REPOSITORY ${gitURL}
        GIT_TAG        ${gitTag}
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
    )
    FetchContent_MakeAvailable(${libName})
endfunction()

set(LIB1 raylib)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
    message(STATUS "Getting ${LIB1} from Github")
    include_dependency(${LIB1} https://github.com/raysan5/raylib.git 5.5)
else()
    message(STATUS "Using local ${LIB1}")
endif()

add_executable(tic_tac_toe
    src/main.c
)

target_include_directories(tic_tac_toe PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(tic_tac_toe PRIVATE ${LIB1})
