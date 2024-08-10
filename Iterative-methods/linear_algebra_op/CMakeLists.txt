cmake_minimum_required(VERSION 3.22)

project(linear_algebra_operations
    LANGUAGES C CXX
)

add_executable(my_linalgebra
    src/main.cpp
    src/vector.cpp
    src/matrix.cpp
    )

target_include_directories(my_linalgebra PRIVATE ./include)

target_compile_features(my_linalgebra PRIVATE cxx_std_17)