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
    auto const sz = _tps.size() - 1;
    for ( std::size_t i{ 0 }; i < sz; ++i )
    {
        _os << _tps[ i ] << ", ";
    }
    _os << _tps[ sz ];

    _os << " }";
    return _os;
}

/*----------------------------------------------------------------------------*/

#endif // __SRC_COMMON__OUTPUT_H__