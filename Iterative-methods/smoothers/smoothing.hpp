#ifndef   _SMOOTHING_
#define  _SMOOTHING_

#include <iostream>
#include <vector>
#include <stdexcept>
#include "vector.hpp"
#include "matrix.hpp"
#include "utilities.hpp"

using sm_mode = SmootherType;

template<typename T, sm_mode mode>
class smoothing{
    protected:
        vecT<T> init_guess;

    public:

};


#endif