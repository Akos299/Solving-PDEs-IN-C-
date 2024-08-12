cmake_minimum_required(VERSION 3.22)

set(My_project_name  linear_algebra_operations_tests)

set(Sources 
    vectorTests.cp
)


add_executable(${My_project_name} ${Sources})

target_link_libraries(${My_project_name} PUBLIC 
    gtest_main
    linear_algebra_operations
)

add_test(
    NAME ${My_project_name}
    COMMAND ${My_project_name}
)