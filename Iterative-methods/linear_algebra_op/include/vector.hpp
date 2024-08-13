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
        const vecT& operator=( const vecT&);

        const vecT& vec_resize(const size_t new_size){
            size_ = new_size;
            storage_.resize(new_size); 
        }       
        vecT<T>& subvector(int i_start, int i_end, size_t vec_len );
        void set_size (const size_t new_size){size_ = new_size;}
        size_t get_size() const {return size_;}
        void set(int i, const T& a) {storage_[i] =  a;}
};


template<typename T>
void print_vec(const vecT<T>& v);

template <typename T>
const T dotprod (const vecT<T>&v1, const vecT<T>&v2);

template<typename T>
void my_axpy(const T alpha, vecT<T>& x, vecT<T>&y); 


#endif