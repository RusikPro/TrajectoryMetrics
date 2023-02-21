#include "math/euclidean_distance.h"

/*----------------------------------------------------------------------------*/

double euclideanDistance ( TimePoint const & _p1, TimePoint const & _p2 )
{
    auto dx = _p1.x - _p2.x;
    auto dy = _p1.y - _p2.y;
    return sqrt( dx * dx + dy * dy );
}

/*----------------------------------------------------------------------------*/