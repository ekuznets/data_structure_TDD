//
// Created by eugene on 2020-10-22.
//

#include "MathUtils.h"
#include <inttypes.h>
#include <cassert>

// g++ -c MathUtils.not_used_cpp
// g++ -shared -o libMathUtils.so MathUtils.o

extern uint32_t GetNextPowerOfTwo(uint32_t value)
{
    if(value == 0)
        return 0;

    for(int i=0; i<=32; i++)
    {
        if((1<<i) >= value)
            return 1<<i;
    }

    // should never happen
    assert(false);
    return 0;
}