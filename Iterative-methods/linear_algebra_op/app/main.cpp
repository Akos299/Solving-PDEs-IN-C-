#include<iostream>
#include "vector.hpp"
#include "matrix.hpp"



int main(int argc, char** argv)
{
    vecT<double> vec(5, 10);
    print_vec<double>(vec);

    return 0;
}