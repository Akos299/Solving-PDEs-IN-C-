#include "vector.hpp"


template<typename T>
void print_vec(const vecT<T>& v)
{
    std::cout << "start vector print  : " << "\t" << " size  = " << v.vec_capacity() << "\n";
    std::cout << "[ " ;
    for(int i = 0; i < v.vec_capacity(); i++ )
    {
        std::cout << v(i) << " ";
    }
    std::cout << "]" << "\n";
    
}

template <typename T>
inline const T vecNorm2(const vecT<T>&v)
{
    const size_t N = v.vec_capacity();
    T res = SQRT(dotprod(v,v));
    return res; 
}

template <typename T>
const T vecNorm1 (const vecT<T>&v)
{
    const size_t N = v.vec_capacity();
    T res = 0.;
    for(size_t i = 0; i < N; i++)
        res += ABS(v(i));
    return res;
}

template <typename T>
const T dotprod (const vecT<T>&v1, const vecT<T>&v2)
{
    const size_t N = v1.vec_capacity();
    T res = 0.;
    for(size_t i = 0; i < N; i++)
    {
        res += v1(i) * v2(i);
    }

    return  res;
}








template<typename T>
vecT<T>& vecT<T>::subvecT(int i_start, int i_end, size_t vec_len ){
    if(size < vec_len )
        throw std::invalid_argument("the subvector size must be less than the  vector size");
    if(size < i_end || i_start < 0 || i_end <= i_start)
        throw std::invalid_argument("invalid range");

    vecT<T>res(vec_len);
    for(size_t i = 0; i < i_end; i++)
        res(i) = storage_[i];
    return res;
}