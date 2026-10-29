
cmake_minimum_required(VERSION 3.21)

project(MapGenC
    VERSION 1.0.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

find_package(raylib REQUIRED)

add_library(noise STATIC
    noise.c
    noise_utils.c
    GradientNoise/gradient_noise.c
    SimplexNoise/simplex_noise.c
    ValueNoise/value_noise.c
)

target_include_directories(noise
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if(UNIX)
    target_link_libraries(noise PUBLIC m)
endif()

add_executable(MapGenC main.c)

target_link_libraries(MapGenC
    PRIVATE
        noise
        raylib
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(noise PRIVATE
        -Wall -Wextra -Wpedantic
    )

    target_compile_options(MapGenC PRIVATE
        -Wall -Wextra -Wpedantic
    )
endif()
