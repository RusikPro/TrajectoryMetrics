#include "utils/parser.h"
#include "utils/menu.h"

#include "common/output.h"

#include <iostream>

/*----------------------------------------------------------------------------*/

int main ()
{
    Parser parser;

    auto trajs = parser( "data/small_trajectory.dat" );

    Menu menu( trajs );

    menu.run();

    return 0;
}