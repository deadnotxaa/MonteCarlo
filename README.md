# Monte Carlo Volume Calculation

## Overview
This project implements a Monte Carlo method to calculate the volume of a 3D shape using C++. The project includes functionality for parallel computation using OpenMP to enhance performance. This project is structured to read input parameters from a file, execute the Monte Carlo simulation, and write the results to an output file. It can be run with or without parallel threading, depending on the specified arguments.

## Files in the Project

* ```main.cpp```: The main program file where the execution starts.
* ```Parser.hpp```: Header file for argument parsing.
* ```hit.h```: Header file containing the ```hit_test``` function declaration.

## How It Works

1. **Argument Parsing**: The program starts by parsing command-line arguments to get input and output file names, the number of points to generate, and whether to use threading.
2. **Reading Input**: It reads the number of points from the input file.
3. **Simulation Execution**: Depending on the threading type specified in the arguments, the program either:
    * Uses OpenMP for parallel processing (```CalculateOMP``` function).
    * Processes points sequentially without parallelism (```CalculateWithoutOMP``` function).
4. **Volume Calculation**: After counting the number of hits, it calculates the volume of the shape.
5. **Writing Output**: The calculated volume is written to the output file.


## How to Use

### Prerequisites
* **C++ Compiler**: A C++ compiler supporting C++11 or later.
* **OpenMP**: Ensure OpenMP is supported and enabled in your compiler.
* **Standard Library**: The project relies on the C++ standard library for random number generation and file I/O.

## Compilation
```bash
g++ -fopenmp main.cpp -o MonteCarloVolume
```

## Running the Program
```bash
./MonteCarloVolume --input input.txt --output output.txt --omp-threads default
```
* ```--input```: Path to the input file containing the number of points.
* ```--output```: Path to the output file where the calculated volume will be written.
* ```--omp-threads```: Number of threads to use (or ```default`` to use maximum number).


### Input File Format
The input file should contain a single integer representing the number of points to generate for the Monte Carlo simulation. For example:
```txt
100000000
```
### Output File Format
The output file will contain a single floating-point number representing the calculated volume.

## Example
Given an input file input.txt containing 1'000'000'000, and using 4 threads with OpenMP, the command to run the program would be:
```bash
./MonteCarloVolume --input input.txt --output output.txt --omp-threads 4
```

## Performance Considerations
**Threading**: Utilizing OpenMP can significantly reduce computation time by leveraging multiple CPU cores.
**Random Number Generation**: Each thread uses its own random number generator to ensure thread safety and improve performance.
**Critical Section**: The ```hit_counter``` is updated in a critical section to prevent race conditions.

## Conclusion
This Monte Carlo Volume Calculation project demonstrates an efficient way to estimate the volume of a 3D shape using random sampling. By leveraging OpenMP, the program can scale its performance based on the available CPU cores, making it suitable for both small-scale and large-scale computations.

