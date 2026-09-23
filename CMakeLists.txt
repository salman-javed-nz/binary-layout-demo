cmake_minimum_required(VERSION 3.16)

project(binary_layout_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(layout_good main.cpp algorithm.cpp)
add_executable(layout_bad main.cpp algorithm.cpp unrelated.cpp)

foreach(target layout_good layout_bad)
  target_compile_options(${target} PRIVATE -fno-pie)
  target_link_options(${target} PRIVATE -no-pie -Wl,--sort-section=name)
endforeach()

add_custom_target(benchmark
  COMMAND $<TARGET_FILE:layout_good>
  COMMAND $<TARGET_FILE:layout_bad>
  DEPENDS layout_good layout_bad
  USES_TERMINAL
)
