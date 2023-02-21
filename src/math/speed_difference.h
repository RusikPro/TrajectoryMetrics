#ifndef __SRC_MATH__SPEED_DIFFERENCE_H__
#define __SRC_MATH__SPEED_DIFFERENCE_H__

/*----------------------------------------------------------------------------*/

#include "math/euclidean_distance.h"

#include <vector>

/*----------------------------------------------------------------------------*/

double speedDifference (
        std::vector< TimePoint > const & _traj1
    ,   std::vector< TimePoint > const & _traj2
);

/*----------------------------------------------------------------------------*/

#endif // __SRC_MATH__SPEED_DIFFERENCE_H__