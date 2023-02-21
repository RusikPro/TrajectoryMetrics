#ifndef __SRC_MATH__LENGTH_DIFFERENCE_H__
#define __SRC_MATH__LENGTH_DIFFERENCE_H__

/*----------------------------------------------------------------------------*/

#include "math/euclidean_distance.h"

#include <vector>

/*----------------------------------------------------------------------------*/

// Compute the length of a trajectory
double trajectoryLength ( std::vector< TimePoint > const & _trajectory );

/*----------------------------------------------------------------------------*/

// Compute the length difference between two trajectories
double lengthDifference (
        std::vector< TimePoint > const & _traj1
    ,   std::vector< TimePoint > const & _traj2
);

/*----------------------------------------------------------------------------*/

#endif // __SRC_MATH__LENGTH_DIFFERENCE_H__