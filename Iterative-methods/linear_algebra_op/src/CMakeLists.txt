
set(Sources 
    matrix.cpp 
    vector.cpp)

set(Headers 
    ../include/vector.hpp 
    ../include/matrix.hpp)

add_library(op_lib ${Sources} ${Headers})

target_include_directories(op_lib PUBLIC ../include)

target_compile_features(op_lib PUBLIC cxx_std_11)
