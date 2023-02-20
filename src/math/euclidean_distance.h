#ifndef __SRC_MATH__EUCLIDEAN_DISTANCE_H__
#define __SRC_MATH__EUCLIDEAN_DISTANCE_H__

/*----------------------------------------------------------------------------*/

#include "common/time_point.h"

#include <cmath>

/*----------------------------------------------------------------------------*/

inline double euclideanDistance ( TimePoint const & _p1, TimePoint const & _p2 )
{
    auto dx = _p1.x - _p2.x;
    auto dy = _p1.y - _p2.y;
    return sqrt( dx * dx + dy * dy );
}

/*----------------------------------------------------------------------------*/

#endif // __SRC_MATH__EUCLIDEAN_DISTANCE_H__