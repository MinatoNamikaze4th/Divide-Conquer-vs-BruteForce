This program provides an implementation to find the closest pair of points among a set of points in a plane using two methods: a brute-force approach and a divide-and-conquer approach. It measures the performance of both methods by calculating the empirical runtime for each approach over multiple iterations and different numbers of points.

Requirements:
C++ Compiler (GCC preferred)
sys/time.h library for timing measurements
Usage:
Compile the program with a C++ compiler using the following command:


g++ -o closest_pair closest_pair.cpp


Run the program:


./closest_pair


Functionality:
struct Point: Defines a point in 2D space with integer coordinates (x, y).
calculateDistance(): Computes the Euclidean distance between two points.
BruteForce(): Determines the closest pair of points using the brute-force method.
stripClosest(): A helper function used in the divide-and-conquer approach to find the closest pair within a strip.
DivideAndConquer(): Implements the divide-and-conquer approach to find the closest pair.
main(): Drives the program by generating random points, invoking the algorithms, timing their execution, and printing the results.
Output:
Outputs the number of points (n) and the average empirical runtimes for both the divide-and-conquer (ALG1) and brute-force (ALG2) methods.

Additional Notes:
The program measures the runtime using gettimeofday() and outputs the results in milliseconds.
For simplicity, the current implementation only tests one iteration (m = 1), but this can be adjusted for more thorough testing.
The number of points tested (max_n) starts from 10,000 and increases by 5,000 up to 20,000 points. This can be adjusted as needed.
Development:
Developed with standard C++ libraries, this program is intended for educational purposes to demonstrate algorithm efficiency and comparative analysis between different approaches to solving the Closest Pair problem.






