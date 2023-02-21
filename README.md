# Trajectory Metrics

This project is a C++ command-line tool for finding closest trajectories to the reference one using length and speed difference metrics.

## Requirements

To use this tool, you will need to have C++ compiler installed on your computer, which supports C++17 and higher standards.

## Installation

1. Clone this repository to your local machine.
2. Open a terminal and navigate to the root directory of the project.
3. Run the following command to compile the code:

    ```
    cmake -S . -B build
    make -C build
    ```

## Usage

To use the tool, navigate to the build directory and run the following command:

```bash
./build/the_binary <path/to/trajectories_file>
```

This will then outpout the menu and prompt to enter the option.
The options are as follows:
```bash
Menu
p - Print trajectories
l - Calculate length difference
s - Calculate speed difference
q - Exit
```

Use `p` to print the trajectories from earlier read file.
Every trajectory has its index, which starts from 1.
If the number of trajectories exceeds 100, it will ask to enter the minimum and maximum index of the range needed to be printed in such format: "\<min\> \<max\>" .  For example,
```bash
 > 1 55
 ```

Above command will print the trajectories from the first one to the 55th.
After printing it will come back to initial state - print the Menu.

`l` and `s` options specifies length and speed difference calculations metric respectively.
After choosing one of this option, the index of reference trajectory will be prompted. 
Remember that indexes start not from 0, but from 1, and up to the number of trajectories inclusively. 
Choose the index for reference trajectory by inserting the index. For example,
```bash
 > 4
 ```
 For the index 4, with length difference (`l`) calculation metric and file `data/small_trajectory.dat` it should output this:
 ```bash
 > 4
Reference trajectory: { {18,76,73}, {5,58,74}, {89,98,75}, {29,92,76}, {34,26,77}, {83,66,78}, {21,53,79}, {6,67,80}, {37,1,81}, {67,15,82} }
3 closest trajectories:
#1. Index - 10, Difference - 8.88004, Trajectory { {75,27,9}, {6,41,10}, {74,42,11}, {96,6,12}, {48,24,13}, {28,10,14}, {1,24,15}, {99,82,16}, {32,65,17}, {58,43,18} }
#2. Index - 6, Difference - 25.649, Trajectory { {51,55,65}, {95,92,66}, {10,6,67}, {23,26,68}, {20,77,69}, {9,46,70}, {46,86,71}, {49,38,72}, {77,64,73}, {55,100,74} }
#3. Index - 5, Difference - 44.5916, Trajectory { {47,87,33}, {11,4,34}, {43,30,35}, {6,94,36}, {59,9,37}, {34,35,38}, {31,59,39}, {13,75,40}, {29,50,41}, {57,38,42} }
```
After printing this it will come back to initial "Menu".

Choose `q` option to exit the program.

## Features

- Reads the trajectories from the file.
- Prints the read trajectories in human readable format.
- Calculates 3 closest trajectories for the given reference one using length and speed difference metrics.

## Project Structure

The project is structured as follows:

- `src/` - source code directory
- `CMakeLists.txt` - CMake build system configuration file
- `README.md` - this file

The source code directory includes the following files:

- `src/main.cpp` - the main entry point for the application.
- `src/common/time_point.h` - a data structure to represent a point in time.
- `src/math/euclidean_distance.h` - a function to calculate the Euclidean distance between two points.
- `src/math/speed_difference.h` - a function to calculate the speed difference between two trajectories.
- `src/math/length_difference.h` - a function to calculate the length difference between two trajectories.
- `src/math/impl/euclidean_distance.cpp`, `src/math/impl/speed_distance.cpp`, `src/math/impl/length_distance.cpp` - implementations.
- `src/utils/parser.h` - a utility to parse trajectory data from a file.
- `src/utils/menu.h` - a menu class to print trajectories, choose the reference trajectory and metrics.
- `src/utils/parser.cpp`, `src/utils/menu.cpp`,  - implementations.
- `data/test_trajectory.dat` - a test data with two trajectories.
- `data/small_trajectory.dat` - a test data with ten trajectories.
- `data/large_trajectory.dat` - a large test data file which consists of 10000 with different lengths.

## TODO
- Apply some parallel SIMD computing to improve performance. There is a lot of trajectories, and their speed and length differences can be calculated in parallel.
- Refactor menu class.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Contact

If you have any questions or comments about this project, please contact me at `rusik.arhireev@gmail.com`.
