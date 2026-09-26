cmake_minimum_required(VERSION 3.16)

project(binary_layout_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(layout_good src/main.cpp)
add_executable(layout_bad src/main.cpp src/unrelated.cpp)

foreach(target layout_good layout_bad)
  target_link_options(${target} PRIVATE -Wl,--sort-section=name -Wl,-q)
endforeach()
