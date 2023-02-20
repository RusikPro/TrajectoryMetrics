#ifndef __SRC_COMMON__TIMEPOINT_H__
#define __SRC_COMMON__TIMEPOINT_H__

/*----------------------------------------------------------------------------*/

struct TimePoint
{
    double x;
    double y;
    double t;
};

/*----------------------------------------------------------------------------*/

template < typename _OutStreamT >
_OutStreamT & operator << ( _OutStreamT & _os, TimePoint const & _tp )
{
    _os << '{' << _tp.x << ',' << _tp.y << ',' << _tp.t << '}';
    return _os;
}

/*----------------------------------------------------------------------------*/

#endif // __SRC_COMMON__TIMEPOINT_H__