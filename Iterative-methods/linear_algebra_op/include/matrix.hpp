#ifndef MATRIX_CLASS
#define MATRIX_CLASS

#include <iostream>
#include <vector>
#include <stdexcept>

#include <../include/vector.hpp>



template<typename T>
class matT : public vecT<T>{
    private:
    size_t _nrows, _ncols;
    size_t _ld; // leading dimensions of the matrix we suppose that we are working in column-major
    
    public:
    matT(){}

    matT(const size_t nrow, const size_t ncol):_nrows(nrow), _ncols(ncol)
    {
        _ld = _ncols;
        this->set_size(nrow * ncol);
        this->vec_resize(nrow * ncol);
    }

    matT(const matT& M){
        _nrows(M.get_nb_rows());
        _ncols(M.get_nb_cols());
        _ld(M.get_leading_dim());
        for(size_t i = 0; i < _ncols; i++)
        {
            auto col = M.get_col(i);
            set_col(i,col);
        }
    }

    const matT& operator= (const matT& M)
    {
        _nrows(M.get_nb_rows());
        _ncols(M.get_nb_cols());
        _ld(M.get_leading_dim());
        for(size_t i = 0; i < _ncols; i++)
        {
            auto col = M.get_col(i);
            set_col(i,col);
        }
    }

    const T operator() (size_t i, size_t j) {
        return this->storage_[_ld*j + i];
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
template<typename T, gemv_layering_operation gemv_mode>
void my_gemv(matT<T>&A, vecT<T>& x, vecT<T>& y);



#endif