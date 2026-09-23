#include "algorithm.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>

int main()
{
    // Warm up the instruction cache before the actual benchmarking.
    run_algorithm(/* iterations: */ 1);

    const auto start = std::chrono::steady_clock::now();
    const auto checksum = run_algorithm(/* iterations: */ 100'000'000);
    const auto elapsed = std::chrono::steady_clock::now() - start;
    const auto seconds = std::chrono::duration<double>(elapsed);

    std::cout << std::fixed << std::setprecision(2)
              << "duration: " << seconds.count() << " s, checksum: 0x"
              << std::hex << checksum << '\n';
}
