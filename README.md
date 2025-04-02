# Kiloscore

Kiloscore is a simple CPU benchmarking tool that measures single-core and multi-core performance using Fibonacci number calculations.

## Features
- Computes Fibonacci numbers iteratively for benchmarking.
- Measures execution time in nanoseconds.
- Runs multiple iterations to get an average score.
- Supports multi-threading using pthreads.
- Uses CMake for easy compilation.

## Requirements
- A C compiler (GCC or Clang recommended)
- CMake (version 3.10 or higher)
- Linux or macOS (Windows support may require additional configuration)

## Installation & Compilation
1. Clone the repository:
   ```sh
   git clone https://github.com/iaseth/kiloscore.git
   cd kiloscore
   ```
2. Build using CMake:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. Run the benchmark:
   ```sh
   ./kiloscore
   ```

## Output Example
```
Running single-core benchmark ...
   Single-core average execution time: 3322415 ns
Running multi-core benchmark ...
   Multi-core average execution time (32 threads): 41384270 ns
Single-core average score: 15.05
Multi-core average score: 38.66
```

## License
This project is open-source under the MIT License.

