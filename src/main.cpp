#include "math/speed_difference.h"
#include "math/length_difference.h"
#include "utils/parser.h"
#include "utils/menu.h"

#include "common/output.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>

/*----------------------------------------------------------------------------*/

int main ()
{
    Parser parser;

    auto trajs = parser( "data/small_trajectory.dat" );

    Menu menu( trajs );

    menu.run();

    return 0;
}