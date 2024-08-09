#include "include/matrix.hpp"

namespace lin_op = linalgebra;
template<typename T>
void lin_op::GEMAd(const lin_op::matT<T>& A, const lin_op::matT<T>& B, const T a , const T b)
{
    if (A.get_leading_dim() != B.get_leading_dim())
        throw std::invalid_argument("The two matrices should have same leading dimensions.\n");
    if ((A.get_nb_cols() ! B.get_nb_cols()) ||(A.get_nb_rows() != B.get_nb_rows()))
        throw std::invalid_argument("Matrices should have same dimensions.\n")
    
    size_t ncol { A.get_nb_cols()}, nrow {A.get_nb_rows()};

    for (auto j = 0;  j < ncol; j++)
        for (auto i = 0; i < nrow; i++)
            A(i,j) = a*A(i,j) + b*B(i,j);
    
}

template<typename T>
void lin_op::AdScalToMat(const lin_op::matT<T>& A, const T a)
{

    size_t ncol { A.get_nb_cols()}, nrow {A.get_nb_rows()}
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