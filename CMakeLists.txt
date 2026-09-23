cmake_minimum_required(VERSION 3.16)

project(binary_layout_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(layout_good main.cpp algorithm.cpp)
add_executable(layout_bad main.cpp algorithm.cpp unrelated.cpp)

foreach(target layout_good layout_bad)
  target_compile_options(${target} PRIVATE -fno-pie)
  target_link_options(${target} PRIVATE -no-pie -Wl,--sort-section=name -Wl,-q)
endforeach()

find_program(BOLT_EXECUTABLE NAMES llvm-bolt-20 llvm-bolt REQUIRED)

set(BOLT_INSTRUMENTED ${CMAKE_BINARY_DIR}/layout_bad.instrumented)
set(BOLT_PROFILE ${CMAKE_BINARY_DIR}/layout.fdata)
set(BOLT_OPTIMIZED ${CMAKE_BINARY_DIR}/bolt/layout_bolt)

add_custom_command(
  OUTPUT ${BOLT_INSTRUMENTED}
  COMMAND ${BOLT_EXECUTABLE} $<TARGET_FILE:layout_bad>
          -o ${BOLT_INSTRUMENTED}
          -instrument
          -instrumentation-file=${BOLT_PROFILE}
  DEPENDS layout_bad
)
add_custom_target(layout_bad_instrumented DEPENDS ${BOLT_INSTRUMENTED})

add_custom_command(
  OUTPUT ${BOLT_PROFILE}
  COMMAND ${BOLT_INSTRUMENTED}
  DEPENDS layout_bad_instrumented
)

add_custom_command(
  OUTPUT ${BOLT_OPTIMIZED}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bolt
  COMMAND ${BOLT_EXECUTABLE} $<TARGET_FILE:layout_bad>
          -data ${BOLT_PROFILE}
          -o ${BOLT_OPTIMIZED}
          -reorder-blocks=ext-tsp
          -reorder-functions=hfsort
          -split-functions
          -split-all-cold
  DEPENDS layout_bad ${BOLT_PROFILE}
)
add_custom_target(layout_bolt DEPENDS ${BOLT_OPTIMIZED})

add_custom_target(benchmark
  COMMAND $<TARGET_FILE:layout_good>
  COMMAND $<TARGET_FILE:layout_bad>
  COMMAND ${BOLT_OPTIMIZED}
  DEPENDS layout_good layout_bad layout_bolt
  USES_TERMINAL
)
