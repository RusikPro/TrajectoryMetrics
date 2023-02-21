#include "math/length_difference.h"

/*----------------------------------------------------------------------------*/

double trajectoryLength ( std::vector< TimePoint > const & _trajectory )
{
    double length = 0.0;
    for ( std::size_t i{ 1 }; i < _trajectory.size(); ++i )
    {
        length += euclideanDistance( _trajectory[ i - 1 ], _trajectory[ i ] );
    }
    return length;
}

/*----------------------------------------------------------------------------*/

double lengthDifference (
        std::vector< TimePoint > const & _traj1
    ,   std::vector< TimePoint > const & _traj2
)
{
    double length1 = trajectoryLength( _traj1 );
    double length2 = trajectoryLength( _traj2 );
    return std::abs( length1 - length2 );
}

/*----------------------------------------------------------------------------*/