cmake_minimum_required(VERSION 3.30)
project(tic_tac_toe_raylib C)

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

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(tic_tac_toe_raylib
    src/main.c
    src/button.c
    src/game.c
    include/constants.h
    include/types.h
    include/game.h
    include/button.h
)

target_include_directories(tic_tac_toe_raylib PRIVATE ${raylib_INCLUDE_DIRS})
target_include_directories(tic_tac_toe_raylib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tic_tac_toe_raylib PRIVATE ${LIB1})
