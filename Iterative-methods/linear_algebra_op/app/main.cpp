#include<iostream>
#include <../include/vector.hpp>
#include <../include/matrix.hpp>



int main(int argc, char** argv)
{
    vecT<double> vec(0, 10);
    print_vec<double>(vec);

    return 0;
}