#include <iostream>

template<typename T>
class complex{
    T real; // the real part
    T image; // the imaginary par

    public:
        complex(T r = 0., T i = 0.) : real(r), image(i)
        {} // constructor
        complex(const complex&c) : real(c.real), image(c.image)
        {} // copy contsructor

        ~complex(){} // destructor 

        T re() const{return real;} // read real part
        T im() const{return image;} // read imaginary part


        const complex& operator=(const complex&c){
            real  = c.real;
            image = c.image;
            return *this;
        }// assignment operator

        const complex& operator +=(const complex&c){
            real  +=c.real;
            image +=c.image;
            return *this;
        } // add complex to the current complex

        const complex& operator -=(const complex&c){
            real  -=c.real;
            image -=c.image;
            return *this;
        } // substract complex to the current complex

        const complex& operator *= (const complex&c){
            T tmp = real;
            real  = real * c.real - image*c.image;
            image = tmp * c.image + image * c.real;
            return *this;
        } // multiply the current complex by a complex

        const complex& operator /=(T d){
            real /= d;
            image /= d;
            return *this;
        } // divide the current complex by a number of type T

        friend complex operator! (const complex&c);
        template<T> friend T abs2(const complex&c);
};

complex operator! (const complex&c){
    return complex(c.re(), -c.im())
} // conjugate complex

template<T>
T abs2(const complex&c){
    return c.re() * c.re() + c.im() * c.im();
} // square of the absolute value of a complex

const complex& operator/= (const complex&c){
    return *this *=( !c) / abs2(c);
} // divide the current complex by another one

const complex operator-(const complex&c){
    return complex(-c.re(), c.im());
} // negative of a complex number

const complex operator- (const complex&c, const complex&d){
    return complex(c.re() - d.re(),c.im() - d.im() );
} // substraction of two complex numbers

const complex operator+ (const complex&c, const complex&d) {
    return complex(c.re() + d.re(), c.im() + d.im());
} // addition of two complex numbers

const complex operator* (const complex&c, const complex&d){
    return complex(c) *=d;
} // multiplication of two complex numbers

const complex operator/ (const complex&c, const complex&d){
    return complex(c) /=d;
} // division of two complex numbers