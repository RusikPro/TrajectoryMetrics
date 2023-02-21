#ifndef __SRC_UTILS__MENU_H__
#define __SRC_UTILS__MENU_H__

/*----------------------------------------------------------------------------*/

#include "common/time_point.h"

#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

/*----------------------------------------------------------------------------*/

class Menu
{
    struct TrajData
    {
        std::size_t index;
        double difference;
    };

public:

    using Trajectory = std::vector< TimePoint >;
    using Trajectories = std::vector< Trajectory >;
    using MetricFunction =
        std::function< double( Trajectory const &, Trajectory const & ) >
    ;
    using TrajDatas = std::vector< TrajData >;
    using CalculatedTrajs = std::unordered_map< int, TrajDatas >;

    Menu ( Trajectories const & _trajectories );

    void run () const;

private:

    void printTrajectories () const;

    void printTrajectories ( TrajDatas const & _result ) const;

    int selectTrajectory () const;

    bool inputFailed () const;

    struct Compare
    {
        bool operator () ( TrajData _lhs, TrajData _rhs ) const
        {
            return ( _lhs.difference + epsilon < _rhs.difference );
        }

        static constexpr double epsilon =
            std::numeric_limits< double >::epsilon()
        ;
    };

    TrajDatas const & findClosestByMetric ( int _index ) const;

private:

    Trajectories const & m_trajectories;
    const std::size_t m_size;
    
    mutable MetricFunction m_metricFunction;
    mutable CalculatedTrajs m_calculatedTrajectoriesByLengthMetric;
    mutable CalculatedTrajs m_calculatedTrajectoriesBySpeedMetric;
    mutable CalculatedTrajs * m_pCurrentCalculatedTrajectories;
};

/*----------------------------------------------------------------------------*/

#endif // __SRC_UTILS__MENU_H__