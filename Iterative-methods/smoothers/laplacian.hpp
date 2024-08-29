#ifndef _LAPLACIAN
#define _LAPLACIAN

#include <iostream>
#include <vector>
#include <stdexcept>
#include "../linear_algebra_op/include/vector.hpp"
#include "../linear_algebra_op/include/matrix.hpp"
#include "utilities.hpp"

template<typename T>
class laplacian{
    private:
        size_t r_iterior_points, c_iterior_points;
        size_t dimension;
        double delta_xyz;
        matT<T> poissons_mat;

};
#endif