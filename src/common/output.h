#ifndef __SRC_COMMON__OUTPUT_H__
#define __SRC_COMMON__OUTPUT_H__

/*----------------------------------------------------------------------------*/

#include "common/time_point.h"

#include <vector>
#include <iostream>

/*----------------------------------------------------------------------------*/

template < typename _OutStreamT >
_OutStreamT & operator << (
        _OutStreamT & _os
    ,   std::vector< TimePoint > const & _tps
)
{
    _os << "{ ";
    for ( std::size_t i{ 0 }; i < _tps.size(); ++i )
    {
        _os << _tps[ i ];
        if ( i < _tps.size() - 1 )
        {
            _os << ", ";
        }
    }

    _os << " }";
    return _os;
}

/*----------------------------------------------------------------------------*/

#endif // __SRC_COMMON__OUTPUT_H__