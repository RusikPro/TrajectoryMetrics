#ifndef __SRC_UTILS__PARSER_H__
#define __SRC_UTILS__PARSER_H__

/*----------------------------------------------------------------------------*/

#include "common/time_point.h"

#include <algorithm>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <iostream>

/*----------------------------------------------------------------------------*/

namespace {

bool ascending ( TimePoint const & _p1, TimePoint const & _p2 )
{
    return _p1.t < _p2.t;
}

} // namespace

/*----------------------------------------------------------------------------*/

class Parser
{
public:

    using Trajectory = std::vector< TimePoint >;
    using Trajectories = std::vector< Trajectory >;

    // Sorted by time
    using TrajectorySorted = std::set< TimePoint, decltype( &ascending ) >;

    Parser () = default;

    ~Parser ()
    {
        m_ifs.close();
    }

    Trajectories
    operator () ( std::string const & _filePath )
    {
        m_ifs.open( _filePath );

        int numberOfTrajectories{ 0 };

        m_ifs >> numberOfTrajectories;

        if ( !numberOfTrajectories )
        {
            return Trajectories();
        }

        Trajectories trajectories;
        trajectories.reserve( numberOfTrajectories );

        for ( int i{ 0 }; i < numberOfTrajectories; ++i )
        {
            int numberOfPoints{ 0 };

            m_ifs >> numberOfPoints;

            trajectories.push_back( Trajectory() );

            TrajectorySorted traj( &ascending );

            for ( int j{ 0 }; j < numberOfPoints; ++j )
            {
                TimePoint tp;
                m_ifs >> tp.x >> tp.y >> tp.t;
                
                traj.insert( tp );
            }

            std::copy(
                    traj.begin()
                ,   traj.end()
                ,   std::back_inserter( trajectories[ i ] )
            );
        }

        m_ifs.close();

        return trajectories;
    }

private:

    std::ifstream m_ifs;
};

/*----------------------------------------------------------------------------*/

#endif // __SRC_UTILS__PARSER_H__