#include <../include/vector.hpp>


template<typename T>
vecT<T>::vecT(const T  a, const size_t N) : size_(N){
    for(size_t i=0; i < N; i++) storage_[i] = a;
}

template<typename T>
vecT<T>::vecT(const vecT<T>&v ) 
{
    for(size_t i = 0; i <v.size_; i++ )
        storage_[i] = v(i);
}


template<typename T>
const vecT<T>& vecT<T>::operator+=(const vecT<T>& v)
{
    size_t N = v.get_size();
    if( N != size_)
        std::__throw_invalid_argument("vectors sould have same size.\n");
    for(size_t i = 0; i <N; i++)
        storage_[i] += v(i);
    return *this;
}

template<typename T>
const vecT<T>& vecT<T>::operator+=(const T& a)
{
    for(size_t i = 0; i <size_; i++)
        storage_[i] += a;
    return *this;
}

template<typename T>
const vecT<T>& vecT<T>::operator-=(const vecT<T>& v)
{

    size_t N = v.get_size();
    if( N != size_)
        std::__throw_invalid_argument("vectors sould have same size.\n");
    for(size_t i = 0; i <N; i++)
        storage_[i] -= v(i);
    return *this;
}

template<typename T>
const vecT<T>& vecT<T>::operator-=(const T& a)
{
    for(size_t i = 0; i <size_; i++)
        storage_[i] -= a;
    return *this;
}

template<typename T>
const vecT<T>& vecT<T>::operator*=(const T& a)
{
    for(size_t i = 0; i <size_; i++)
        storage_[i] *= a;
    return *this;
}

template<typename T>
const vecT<T>& vecT<T>::operator/=(const T& a)
{
    if(a == 0)
        std::__throw_invalid_argument("Division by zero !\n");
    for(size_t i = 0; i <size_; i++)
        storage_[i] /= a;
    return *this;
}

template<typename T>
const vecT<T>& vecT<T>::operator=(const T& a)
{
    for(size_t i = 0; i <size_; i++)
        storage_[i] = a;
    return *this;
}

template<typename T>
const vecT<T>& vecT<T>::operator=(const vecT<T>& v)
{
    size_t N = v.get_size();
    if( N != size_)
        std::__throw_invalid_argument("vectors sould have same size.\n");
    for(size_t i = 0; i <N; i++)
        storage_[i] = v(i);
    return *this;
}

template<typename T>
void print_vec(const vecT<T>& v)
{
    std::cout << "start vector print  : " << "\t" << " size  = " << v.get_size() << "\n";
    std::cout << "[ " ;
    for(int i = 0; i < v.get_size(); i++ )
    {
        std::cout << v(i) << " ";
    }
    std::cout << "]" << "\n";
    
}

template <typename T>
const T dotprod (const vecT<T>&v1, const vecT<T>&v2)
{
    T res = 0.;
    const size_t N = v1.get_size();
    bool has_same_size = (N == v2.get_size());
    if( !has_same_size)
        throw std::invalid_argument("vector should have same size\n");
   
    for(size_t i = 0; i < N; i++)
    {
        res += v1(i) * v2(i);
    }
    return  res;
}

template <typename T>
inline const T Norm2(const vecT<T>&v)
{
    const size_t N = v.get_size();
    T res = SQRT(dotprod(v,v));
    return res; 
}

template <typename T>
const T Norm1 (const vecT<T>&v)
{
    const size_t N = v.get_size();
    T res = 0.;
    for(size_t i = 0; i < N; i++)
        res += ABS(v(i));
    return res;
}

template<typename T>
vecT<T>& vecT<T>::subvector(int i_start, int i_end, size_t vec_len ){
    if(size_ < vec_len )
        throw std::invalid_argument("the subvector size must be less than the  vector size");
    if(size_ < i_end || i_start < 0 || i_end <= i_start)
        throw std::invalid_argument("invalid range");

    vecT<T>res(vec_len);
    for(size_t i = i_start; i < i_end; i++)
        res(i) = storage_[i];
    return res;
}

template<typename T>
void my_axpy(const T alpha, vecT<T>& x, vecT<T>&y)
{
    auto N = x.get_size();
    if(N != y.get_size())
        throw std::invalid_argument("vectors should have same size\n");
    
    for(auto i = 0; i < N; i++)
        y += (x * alpha);
        // y(i) += alpha * x(i);
}

