#include<iostream>
#include "vector.hpp"
#include "matrix.hpp"



int main(int argc, char** argv)
{
    vecT<double> vec(5, 10);
    // print_vec<double>(vec.vec_resize(3));
    auto v = vec.subvector(5,8,2);
    print_vec<double>(v);
    std::cout << Norm1<double>(vec);

    return 0;
}
