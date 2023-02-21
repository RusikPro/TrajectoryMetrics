#include "utils/menu.h"

#include "math/length_difference.h"
#include "math/speed_difference.h"

#include "common/output.h"
#include "common/constants.h"

#include <iostream>

/*----------------------------------------------------------------------------*/

Menu::Menu ( Trajectories const & _trajectories )
    :   m_trajectories( _trajectories )
    ,   m_size( _trajectories.size() )
    ,   m_metricFunction( lengthDifference )
    ,   m_pCurrentCalculatedTrajectories(
            &m_calculatedTrajectoriesByLengthMetric
        )
{
}

/*----------------------------------------------------------------------------*/

void Menu::run () const
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

/*----------------------------------------------------------------------------*/

void Menu::printTrajectories () const
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

void Menu::printTrajectories ( TrajDatas const & _result ) const
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

/*----------------------------------------------------------------------------*/

int Menu::selectTrajectory () const
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

/*----------------------------------------------------------------------------*/

bool Menu::inputFailed () const
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

/*----------------------------------------------------------------------------*/

Menu::TrajDatas const & Menu::findClosestByMetric ( int _index ) const
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

/*----------------------------------------------------------------------------*/