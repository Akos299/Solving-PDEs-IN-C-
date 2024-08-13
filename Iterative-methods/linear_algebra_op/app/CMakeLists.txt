add_executable(my_main main.cpp)
target_compile_features(my_main PUBLIC cxx_std_11)
target_link_libraries(my_main PRIVATE op_lib)