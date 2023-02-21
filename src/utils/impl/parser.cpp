#include "utils/parser.h"

#include <algorithm>
#include <iostream>

/*----------------------------------------------------------------------------*/

Parser::~Parser ()
{
    m_ifs.close();
}

/*----------------------------------------------------------------------------*/

Parser::Trajectories Parser::operator () ( std::string const & _filePath )
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

/*----------------------------------------------------------------------------*/