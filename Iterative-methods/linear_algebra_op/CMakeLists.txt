#cmake_minimum_required(VERSION 3.22)

cmake_minimum_required(VERSION 3.7)

if(${CMAKE_VERSION} VERSION_LESS 3.22)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.22)
endif()



set(My_project_name  linear_algebra_operations)


project(${My_project_name}
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers 
    ./include/vector.hpp
    ./include/matrix.hpp
    )

set(Sources 
    ./src/vector.cpp 
    ./src/matrix.cpp 
    ./src/main.cpp)

add_library(${My_project_name} STATIC ${Sources} ${Headers})

add_subdirectory(test)