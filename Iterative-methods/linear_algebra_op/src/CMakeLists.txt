
set(Sources 
    matrix.cpp 
    vector.cpp)

set(INCLUDE_DIR 
    ../include)

add_library(op_lib ${Sources})

target_include_directories(op_lib PUBLIC ${INCLUDE_DIR})

target_compile_features(op_lib PUBLIC cxx_std_11)
