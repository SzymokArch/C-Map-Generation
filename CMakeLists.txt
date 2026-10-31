
cmake_minimum_required(VERSION 3.21)

project(MapGenC
    VERSION 1.0.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Noise generation library
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

# Output utilities library
add_library(output STATIC
    output/output.c
)

target_include_directories(output
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/output
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external
)

# Main executable
add_executable(MapGenC
    main.c
    cli/cli.c
)

target_link_libraries(MapGenC
    PRIVATE
        noise
        output
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    foreach(target noise output MapGenC)
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic
        )
    endforeach()
endif()
