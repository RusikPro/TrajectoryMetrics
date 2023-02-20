#ifndef __SRC_MATH__SPEED_DIFFERENCE_H__
#define __SRC_MATH__SPEED_DIFFERENCE_H__

/*----------------------------------------------------------------------------*/

#include "math/euclidean_distance.h"

#include <vector>

/*----------------------------------------------------------------------------*/

inline double
speedDifference (
        std::vector< TimePoint > const & _traj1
    ,   std::vector< TimePoint > const & _traj2
)
{
    // Compute the speed of each point in trajectory 1
    std::vector< double > speeds1;
    for ( std::size_t i{ 0 }; i < _traj1.size() - 1; ++i )
    {
        double dt = _traj1[ i + 1 ].t - _traj1[ i ].t;
        double speed = euclideanDistance( _traj1[ i + 1 ], _traj1[ i ] ) / dt;
        speeds1.push_back( speed );
    }

    // Compute the speed of each point in trajectory 2
    std::vector< double > speeds2;
    for ( std::size_t i{ 0 }; i < _traj2.size() - 1; ++i )
    {
        double dt = _traj2[ i + 1 ].t - _traj2[ i ].t;
        double speed = euclideanDistance( _traj2[ i + 1 ], _traj2[ i ] ) / dt;
        speeds2.push_back( speed );
    }

    // Compute the average speed difference between the two trajectories
    double sum = 0.0;
    std::size_t count = 0;

    auto minSpeedVectorSize = std::min( speeds1.size(), speeds2.size() );
    for ( std::size_t i{ 0 }; i < minSpeedVectorSize; ++i )
    {
        sum += std::abs( speeds1[ i ] - speeds2[ i ] );
        ++count;
    }

    if ( count == 0 )
    {
        return -1; // Return -1 if there are no valid points to compare
    }
    else
    {
        return sum / count;
    }
}

/*----------------------------------------------------------------------------*/

#endif // __SRC_MATH__SPEED_DIFFERENCE_H__