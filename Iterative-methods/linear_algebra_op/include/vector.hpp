#ifndef VECTOR_CLASS
#define VECTOR_CLASS

#include <iostream>
#include <vector>
#include <stdexcept>

#define SQRT(x) sqrtf(x)
#define ABS(x) std::abs(x)




template <typename T>
class vecT {
    protected:
    std::vector<T> storage_;
    size_t size_;

    public:
        vecT(){}
        vecT(const T  a, const size_t N);
        vecT(const vecT&);

        ~vecT(){}

        decltype(auto) data()       { return storage_.data(); }
        decltype(auto) data() const { return storage_.data(); }

        T& operator()(int i)       { return storage_[i]; }
        T  operator()(int i) const { return storage_[i]; }

        const vecT& operator += (const vecT&);
        const vecT& operator += (const T&);
        const vecT& operator -= (const vecT&);
        const vecT& operator -= (const T&);
        const vecT& operator *= (const T&);
        const vecT& operator /= (const T&);

        const vecT& operator= (const T&);
        const vecT& operator= (const vecT&);

        const vecT& vec_resize(const size_t new_size){
            size_ = new_size;
            storage_.resize(new_size);
            return *this; 
        }       

        // extract subvector of size vec_len
        vecT<T> subvector(int i_start, int i_end, size_t vec_len );
        // set size to new_size
        void set_size (const size_t new_size){size_ = new_size;}
        // get size of vector
        size_t get_size() const {return size_;}
        // set all component of vector to a
        void set(int i, const T& a) {storage_[i] =  a;}
        // get ptr to vector storage
        std::vector<T> get_storage()const{return storage_; }
};

// constructor
template<typename T>
vecT<T>::vecT(const T  a, const size_t N) : size_(N){
    storage_.resize(N);
    for(size_t i=0; i < N; i++) storage_[i] = a;
}

// constructor
template<typename T>
vecT<T>::vecT(const vecT<T>&v ) 
{
    storage_.resize(v.get_size());
    for(size_t i = 0; i <v.get_size(); i++ )
        storage_[i] = v(i);
}

//unary addition operator (with a vector)
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


// unary addition operator (with a scalar)
template<typename T>
const vecT<T>& vecT<T>::operator+=(const T& a)
{
    for(size_t i = 0; i <size_; i++)
        storage_[i] += a;
    return *this;
}

// unary substraction (with a vector)
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

// unary substraction operator(with a scalar)
template<typename T>
const vecT<T>& vecT<T>::operator-=(const T& a)
{
    for(size_t i = 0; i <size_; i++)
        storage_[i] -= a;
    return *this;
}

// unary multiplication operator (with a scalar)
template<typename T>
const vecT<T>& vecT<T>::operator*=(const T& a)
{
    for(size_t i = 0; i <size_; i++)
        storage_[i] *= a;
    return *this;
}

// unary division operator with a scalar
template<typename T>
const vecT<T>& vecT<T>::operator/=(const T& a)
{
    if(a == 0)
        std::__throw_invalid_argument("Division by zero !\n");
    for(size_t i = 0; i <size_; i++)
        storage_[i] /= a;
    return *this;
}


// unary assignement operator with a scalar 
template<typename T>
const vecT<T>& vecT<T>::operator=(const T& a)
{
    for(size_t i = 0; i <size_; i++)
        storage_[i] = a;
    return *this;
}


// unary assignement operator with a vector
template<typename T>
const vecT<T>& vecT<T>::operator=(const vecT<T>& v)
{
    if(this != &v){
    size_t N = v.get_size();
    if( N != size_)
        std::__throw_invalid_argument("vectors sould have same size.\n");
    for(size_t i = 0; i <N; i++)
        storage_[i] = v(i);
    }
    return *this;
}



// multiply a vector by -1
template<typename T>
const vecT<T>& operator-(const vecT<T>& v)
{
    return vecT<T>(v) *=-1;
}

// add two vectors
template<typename T>
const vecT<T>& operator+(const vecT<T>& v1, const vecT<T>& v2)
{
    return vecT<T>(v1) += v2;
}


// print a vector
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

// dotprod between vectors
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


// L2 norm of vector
template <typename T>
inline const T Norm2(const vecT<T>&v)
{
    const size_t N = v.get_size();
    T res = SQRT(dotprod(v,v));
    return res; 
}


// L1 norm of vector
template <typename T>
const T Norm1 (const vecT<T>&v)
{
    const size_t N = v.get_size();
    T res = 0.;
    for(size_t i = 0; i < N; i++)
        res += ABS(v(i));
    std::cout << "res = " << res <<"\n\n";
    return res;
}


// subvector
template<typename T>
vecT<T> vecT<T>::subvector(int i_start, int i_end, size_t vec_len ){
    if(size_ < vec_len )
        throw std::invalid_argument("the subvector size must be less than the  vector size");
    if(size_ < i_end || i_start < 0 || i_end <= i_start)
        throw std::invalid_argument("invalid range");

    vecT<T>res(0,vec_len);
     size_t j = i_start;
    for(size_t i = 0; i < vec_len; i++)
    {
        if(j  < i_end)
        {
            res(i) = storage_[j];
            j++;
        }        
    }
        
    return res;
}


// AXPY operation
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


#endif
