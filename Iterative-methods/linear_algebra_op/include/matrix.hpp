#ifndef MATRIX_CLASS
#define MATRIX_CLASS

#include <iostream>
#include <vector>
#include <stdexcept>

#include "vector.hpp"

namespace linalgebra{
    
template<typename T>
class matT : public vecT<T>{
    private:
    size_t _nrows, _ncols;
    size_t _ld; // leading dimensions of the matrix we suppose that we are working in column-major
    public:
    matT(size_t nrow, size_t ncol):_nrows(nrow), _ncols(ncol)
    {
        _ld = _ncols;
        this->set_size(nrow * ncol);
        this->vec_resize(nrow * ncol);
    }
    const T& operator()(int idx, int idy){
        auto id = idy * _ld + idx;
        return (*this)(id);
    }

    size_t get_leading_dim ()const {return _ld;}
    size_t get_nb_rows ()const {return _nrows;}
    size_t get_nb_cols () const {return _ncols;}
};

// compute A = a*A + b*B
template<typename T>
void GEMAd(const matT<T>& A, const matT<T>& B, const T a , const T b);

// add a scalar to all component of a given matrix
template<typename T>
void AdScalToMat(const matT<T>& A, const T a);

// generate identity matrix of size n
template<typename T>
matT<T> eye(const size_t n);


}


#endif