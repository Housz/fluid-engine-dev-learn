set(target my_math_test)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${target}
    ${sources})

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS})

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_definitions(-D_USE_MATH_DEFINES) # for M_PI
endif ()

target_compile_options(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE
)

# Link libraries
target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
    jet)