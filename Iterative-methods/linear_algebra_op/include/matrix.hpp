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

    vecT<T> get_row(int row_nb) const;
    vecT<T> get_col(int col_nb) const;
    void set_row(int row_nb, vecT<T>& v);
    void set_col(int col_nb, vecT<T>& v);
    matT<T> get_submat(int idx_row_start, int idx_row_end, int idx_col_start, int idx_col_end) const;

    size_t get_leading_dim ()const {return _ld;}
    size_t get_nb_rows ()const {return _nrows;}
    size_t get_nb_cols () const {return _ncols;}
};

enum gemv_layering_operation{
    DOT  =0,
    AXPY =1
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

// template<typename T>
// const T dots(size_t N, matT<T>& x, int pos_ptrx, int incx, matT<T>& y, int pos_ptry,int incy);

// matrix-vector multiplication
template<typename T, class gemv_mode>
void my_gemv(matT<T>&A, vecT<T>& x, vecT<T>& y);

}


#endif