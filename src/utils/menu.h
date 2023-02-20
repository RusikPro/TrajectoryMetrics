#ifndef __SRC_UTILS__MENU_H__
#define __SRC_UTILS__MENU_H__

/*----------------------------------------------------------------------------*/

#include "common/time_point.h"

#include "common/output.h"
#include "common/constants.h"

#include <iostream>
#include <limits>
#include <unordered_map>
#include <queue>
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

    Menu ( Trajectories const & _trajectories )
        :   m_trajectories( _trajectories )
        ,   m_size( _trajectories.size() )
        ,   m_metricFunction( lengthDifference )
        ,   m_pCurrentCalculatedTrajectories(
                &m_calculatedTrajectoriesByLengthMetric
            )
    {
    }

    void run () const
    {
        char choice = '.';

        do
        {
            std::cout
                <<  "Menu" << std::endl
                <<  "p - Print trajectories" << std::endl
                <<  "l - Calculate length difference" << std::endl
                <<  "s - Calculate speed difference" << std::endl
                <<  "q - Exit" << std::endl
            ;

            std::cout << " > ";
            std::cin >> choice;

            switch ( choice )
            {
                case 'p':
                {
                    printTrajectories();
                }
                break;

                case 'l':
                {
                    m_metricFunction = lengthDifference;
                    m_pCurrentCalculatedTrajectories =
                        &m_calculatedTrajectoriesByLengthMetric
                    ;

                    printTrajectories(
                        findClosestByMetric(
                            selectTrajectory()
                        )
                    );
                }
                break;

                case 's':
                {
                    m_metricFunction = speedDifference;
                    m_pCurrentCalculatedTrajectories =
                        &m_calculatedTrajectoriesBySpeedMetric
                    ;

                    printTrajectories(
                        findClosestByMetric(
                            selectTrajectory()
                        )
                    );
                }
                break;

                case 'q':
                    std::cout << "Quiting..." << std::endl;
                break;
                default:
                    std::cout << "Invalid choice. Try again.\n";
                break;
            }
        }
        while ( choice != 'q' );
    }

private:

    void printTrajectories () const
    {
        std::cout << "You chose to print trajectories!" <<  std::endl;

        if ( m_size <= MaximumPrinted )
        {
            int i{ 0 };
            for ( auto const & traj: m_trajectories )
            {
                std::cout << "#" << ++i << ": " << traj << std::endl;
            }
            return;
        }

        std::cout
            <<  "The number of trajectories in file is bigger than maximum "
                "printable: " << m_size << "!" << std::endl
            <<  "The maximum printable trajectories number is - "
            <<  MaximumPrinted << std::endl
        ;

        int min, max;
        do
        {
            std::cout
                <<  "Please insert the range up to this limit in this form - "
                <<  "\"min max\" and with range - [1, " << m_size << "]. "
                <<  std::endl
                <<  "For example, \"100 150\", will show the trajectories from "
                    "100th to 150th."
                <<  std::endl
            ;

            std::cout << " > ";
            std::cin >> min >> max;

            if ( inputFailed() )
            {
                continue;
            }

            std::cout << "Min: " << min << " Max: " << max << std::endl;

            if (    !( min < max ) || ( max - min ) > MaximumPrinted
                ||  min < 1 || max > m_size
            )
            {
                std::cout << "Incorrect range! Please try again!" << std::endl;

                continue;
            }

            for ( int i{ min - 1 }; i < max; ++i )
            {
                std::cout
                    <<  "#" << i + 1 << ": " << m_trajectories[ i ]
                    <<  std::endl
                ;
            }
        }
        while ( !( min < max ) || ( max - min ) > MaximumPrinted
            ||  min < 1 || max > m_size
        );
    }

    void printTrajectories ( TrajDatas const & _result ) const
    {
        std::cout
            <<  NumberOfClosest << " closest trajectories: "
            <<  std::endl
        ;

        for ( std::size_t i = 0; i < _result.size(); ++i )
        {
            std::cout
                <<  "#" << i + 1 << ". "
                <<  "Index - " << _result[ i ].index + 1
                <<  ", Difference - " << _result[ i ].difference
                <<  ", Trajectory " <<  m_trajectories[ _result[ i ].index ]
                << std::endl
            ;
        }
    }

    int selectTrajectory () const
    {
        int index;
        do
        {
            std::cout
                <<  "Please insert the index of the trajectory with range - "
                <<  "[1, " << m_size << "] - for which you want to find "
                <<  NumberOfClosest << " closest trajectories by chosen metric!"
                <<  std::endl
            ;

            std::cout << " > ";
            std::cin >> index;

            if ( inputFailed() )
            {
                continue;
            }

            if ( index < 1 || index > m_size )
            {
                std::cout << "Incorrect index! Please try again!" << std::endl;

                continue;
            }

            std::cout
                <<  "Reference trajectory: " << m_trajectories[ index - 1 ]
                <<  std::endl
            ;
        }
        while ( index < 1 || index > m_size );

        return index - 1;
    }

    bool inputFailed () const
    {
        if ( std::cin.fail() )
        {
            std::cout << "Invalid input!" << std::endl;
            std::cin.clear();
            std::cin.ignore(
                    std::numeric_limits< std::streamsize >::max()
                ,   '\n'
            );
            return true;
        }
        return false;
    }

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

    TrajDatas const & findClosestByMetric ( int _index ) const
    {
        auto calculated = m_pCurrentCalculatedTrajectories->find( _index );
        if ( calculated != m_pCurrentCalculatedTrajectories->end() )
        {
            return calculated->second;
        }

        std::priority_queue< TrajData, TrajDatas, Compare > minHeap;
        TrajDatas result;
        result.reserve( NumberOfClosest );

        auto const & refTraj = m_trajectories[ _index ];

        for ( std::size_t i = 0; i < m_trajectories.size(); ++i )
        {
            if ( i == _index )
            {
                continue;
            }

            auto diff = m_metricFunction( refTraj, m_trajectories[ i ] );
            minHeap.push( { i, diff } );

            if ( minHeap.size() > NumberOfClosest )
            {
                minHeap.pop();
            }
        }

        while ( !minHeap.empty() )
        {
            result.push_back( minHeap.top() );
            minHeap.pop();
        }

        std::reverse( result.begin(), result.end() );

        return m_pCurrentCalculatedTrajectories->insert(
            { _index, result } 
        ).first->second;
    }

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