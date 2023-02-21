#ifndef __SRC_UTILS__PARSER_H__
#define __SRC_UTILS__PARSER_H__

/*----------------------------------------------------------------------------*/

#include "common/time_point.h"

#include <fstream>
#include <set>
#include <string>
#include <vector>

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

    ~Parser ();

    Trajectories operator () ( std::string const & _filePath );

private:

    std::ifstream m_ifs;
};

/*----------------------------------------------------------------------------*/

#endif // __SRC_UTILS__PARSER_H__