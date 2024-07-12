#ifndef MATRIX_CLASS
#define MATRIX_CLASS

#include <iostream>
#include <vector>
#include <stdexcept>

#include "vector.hpp"

template<typename T>
class matT : public vecT<T>{
    private:
    size_t _nrows, _ncols;
    public:
    matT(size_t nrow, size_t ncol):_nrows(nrow), _ncols(ncol)
    {
        (*this).set_size(nrow * ncol);
        (*this).vec_resize(nrow * ncol);
    }
    const T& operator()(int idx, int idy){
        auto id = idx * _nrows + idy;
        return (*this)(id);
    }
};


#endif