#ifndef VECTOR_CLASS
#define VECTOR_CLASS

#include <iostream>
#include <vector>
#include <stdexcept>

#define SQRT(x) sqrt(x)
#define ABS(x) abs(x)

template <typename T>
class vecT {
    private:
    std::vector<T> storage_;
    size_t size;

    public:
        vecT(){}
        vecT(size_t n) :storage_(n), size(n) {}
        vecT(std::vector<T>& v): storage_{v.data()}, size(v.size()){}
        ~vecT(){}

        decltype(auto) data()       { return storage_.data(); }
        decltype(auto) data() const { return storage_.data(); }

        T& operator()(int i)       { return storage_[i]; }
        T  operator()(int i) const { return storage_[i]; }
        const vecT& operator+ (const vecT& );
        const vecT& operator- (const vecT& );
        const vecT& operator= (const vecT&);
        const vecT& operator+ (const T&);
        const vecT& operator- (const T&);
        const vecT& operator= (const T&);
        const vecT& operator* (const T&);
        const vecT& vec_resize(const size_t new_size){storage_.resize(new_size); }
        //const vecT& vec_resize(const vecT<T>& v, const size_t new_size);
        vecT<T>& subvecT(int i_start, int i_end, size_t vec_len );
        void set_size (const size_t new_size){size = new_size;}
        

        void set(int i, const T& a) {storage_[i] =  a;}
        size_t vec_capacity() const {return size;}
};


template<typename T>
const vecT<T>& vecT<T>::operator= (const vecT<T>& v){
    for(auto i = 0; i < size; i++)
        storage_[i] = v(i);
    return *this;
}

template<typename T>
const vecT<T>& vecT<T>::operator- (const vecT<T>& v){
    for(auto i = 0; i < size; i++)
        storage_[i] -= v(i);
    return *this;
}

template<typename T>
const vecT<T>& vecT<T>::operator+ (const vecT<T>& v){
    for(auto i = 0; i < size; i++)
        storage_[i] += v(i);
    return *this;
}

template<typename T>
const vecT<T>& vecT<T>::operator+ (const T& a){
    for(auto i = 0; i < size; i++)
        storage_[i] += a;
    return *this;
}

template<typename T>
const vecT<T>& vecT<T>::operator- (const T& a){
    for(auto i = 0; i < size; i++)
        storage_[i] -= a;
    return *this;
}

template<typename T>
const vecT<T>& vecT<T>::operator= (const T& a){
    for(auto i = 0; i < size; i++)
        storage_[i] = a;
    return *this;
}

template<typename T>
const vecT<T>& vecT<T>::operator* (const T& a){
    for(auto i = 0; i < size; i++)
        storage_[i] += a;
    return *this;
}

#endif

