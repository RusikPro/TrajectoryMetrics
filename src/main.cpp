#include "utils/parser.h"
#include "utils/menu.h"

#include "common/output.h"

#include <iostream>

/*----------------------------------------------------------------------------*/

int main ( int _argc, char * _argv[] )
{
    if ( _argc < 2 )
    {
        std::cerr << "Specify the file to read!" << std::endl;
        std::cout << "Usage: <binary> <path/to/trajectories_file>";
        return -1;
    }

    std::string filePath = _argv[ 1 ];

    Parser parser;

    auto trajs = parser( filePath );

    Menu menu( trajs );

    menu.run();

    return 0;
}