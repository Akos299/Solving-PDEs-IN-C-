#include "../include/matrix.hpp"

namespace lin_op = linalgebra;
using gemv_layer_mode = lin_op::gemv_layering_operation;

template<typename T>
lin_op::vecT<T> lin_op::matT<T>::get_row(int row_nb) const{
    
    auto N = get_nb_cols();
    lin_op::vecT<T> res(N);
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
lin_op::vecT<T> lin_op::matT<T>::get_col(int col_nb) const{

    auto N = get_nb_rows();
    lin_op::vecT<T> res(N);
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
void lin_op::matT<T>::set_row(int row_nb, vecT<T>& v)
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
void lin_op::matT<T>::set_col(int col_nb, vecT<T>& v)
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
void lin_op::GEMAd(const lin_op::matT<T>& A, const lin_op::matT<T>& B, const T a , const T b)
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
void lin_op::AdScalToMat(const lin_op::matT<T>& A, const T a)
{

    size_t ncol { A.get_nb_cols()}, nrow {A.get_nb_rows()};
    for (auto j = 0;  j < ncol; j++)
        for (auto i = 0; i < nrow; i++)
            A(i,j) = A(i,j) + a;

}

template<typename T>
lin_op::matT<T> lin_op::eye(const size_t n) {
    lin_op::matT<T> I_nn(n,n);
    for(size_t i = 0; i < n; i++)   I_nn[i*n + i] = (T)1.0;
    return I_nn;
}


template<typename T>
lin_op::matT<T> lin_op::matT<T>::get_submat(int idx_row_start, int idx_row_end, int idx_col_start, int idx_col_end) const
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
void lin_op::my_gemv(lin_op::matT<T>&A, lin_op::vecT<T>&x, lin_op::vecT<T>&y)
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