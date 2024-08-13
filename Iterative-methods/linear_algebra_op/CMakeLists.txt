cmake_minimum_required(VERSION 3.22)


project(my_project
    LANGUAGES C CXX
)

# set(Sources 
#     src/matrix.cpp 
#     src/vector.cpp)

# set(Headers 
#     ./include/vector.hpp 
#     ./include/matrix.hpp)

# add_library(lin_operations STATIC ${Sources} ${Headers} )
# target_include_directories(lin_operations PUBLIC ./include)
# target_compile_features(lin_operations PUBLIC cxx_std_11)
# add_executable(my_main src/main.cpp)
# target_link_libraries(my_main PUBLIC lin_operations)
add_subdirectory(src)
add_subdirectory(app)
