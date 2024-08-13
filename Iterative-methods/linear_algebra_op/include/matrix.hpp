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



using gemv_layer_mode = gemv_layering_operation;

template<typename T>
vecT<T> matT<T>::get_row(int row_nb) const{
    
    auto N = get_nb_cols();
    vecT<T> res(0,N);
    auto ld = get_leading_dim();
    size_t i = 0;
    while(i < N)
    {
        res(i) = this->storage_[row_nb + (i*ld)];
        i+=1;
    }
    return res;
}

template<typename T>
vecT<T> matT<T>::get_col(int col_nb) const{

    auto N = get_nb_rows();
    vecT<T> res(N);
    auto ld = get_leading_dim();
    size_t i = 0;
    while(i < N)
    {
        res(i) = this->storage_[ld*col_nb + i];
        i+=1;
    }
    return res;
}

template<typename T>
void matT<T>::set_row(int row_nb, vecT<T>& v)
{
    auto N = v.get_size();
    auto ld = get_leading_dim();
    if(N != get_nb_cols())
        throw std::invalid_argument("vector size's must be the same with matrix column number\n");

    size_t i = 0;
    for(i; i < N; i++)   
    {
        this->storage_[row_nb + (i*ld)] = v(i);
    }
}

template<typename T>
void matT<T>::set_col(int col_nb, vecT<T>& v)
{
    auto N = v.get_size();
    auto ld = get_leading_dim();
    if(N != get_nb_rows())
        throw std::invalid_argument("vector size's must be the same with matrix column number\n");
    
    size_t i = 0;
    for(; i< N; i++)
    {
        this->storage_[ld*col_nb + i] = v(i);
    }

}

template<typename T>
void GEMAd(const matT<T>& A, const matT<T>& B, const T a , const T b)
{
    if (A.get_leading_dim() != B.get_leading_dim())
        throw std::invalid_argument("The two matrices should have same leading dimensions.\n");
    if ((A.get_nb_cols() != B.get_nb_cols()) ||(A.get_nb_rows() != B.get_nb_rows()))
        throw std::invalid_argument("Matrices should have same dimensions.\n");
    
    size_t ncol { A.get_nb_cols()}, nrow {A.get_nb_rows()};

    for (auto j = 0;  j < ncol; j++)
        for (auto i = 0; i < nrow; i++)
            A(i,j) = a*A(i,j) + b*B(i,j);
    
}

template<typename T>
void AdScalToMat(const matT<T>& A, const T a)
{

    size_t ncol { A.get_nb_cols()}, nrow {A.get_nb_rows()};
    for (auto j = 0;  j < ncol; j++)
        for (auto i = 0; i < nrow; i++)
            A(i,j) = A(i,j) + a;

}

template<typename T>
matT<T> eye(const size_t n) {
    matT<T> I_nn(n,n);
    for(size_t i = 0; i < n; i++)   I_nn[i*n + i] = (T)1.0;
    return I_nn;
}


template<typename T>
matT<T> matT<T>::get_submat(int idx_row_start, int idx_row_end, int idx_col_start, int idx_col_end) const
{
    size_t nb_row{get_nb_rows()}, nb_col{get_nb_cols()};
    if((idx_col_start < 0 ) || (idx_col_end > nb_col) || (idx_col_end <= idx_col_start))
        throw std::invalid_argument("Invalid column range\n");
    if((idx_row_start < 0) || (idx_row_end > nb_row) || (idx_row_end <= idx_row_start))
        throw std::invalid_argument("Invalid row range\n");
    
    size_t nb_col_res{idx_col_end - idx_col_start}, nb_row_res{idx_row_end - idx_row_start};
    matT<T> mat_res(nb_row_res, nb_col_res);
    for(auto i = idx_col_start; i< nb_col_res; i++)
    {
        auto j = 0;
        if(j < nb_col_res)
            mat_res.set_col(j,get_col(i).subvecT(idx_row_start,idx_row_end,nb_row_res));
        j++;
    }

}

template<typename T, gemv_layer_mode gemv_mode>
void my_gemv(matT<T>&A, vecT<T>&x, vecT<T>&y)
{
    size_t nb_rowA {A.get_nb_rows()}, nb_x{x.get_size()}, nb_y{y.get_size()};
    if((nb_rowA != nb_x) || (nb_rowA != nb_y))
        throw std::invalid_argument("Size don't match.\n");

    if constexpr(gemv_mode == DOT)
        for(int i = 0; i < nb_y;i++)
        {
            auto row_i = A.get_row(i);
            y(i) = y(i) + dotprod(row_i, x);
        }
    if constexpr (gemv_mode == AXPY)
        for(int i = 0; i <nb_x; i++ )
        {
            auto col_i = A.get_col(i);
            y +=(col_i*x(i));
        }
        
}


#endif
