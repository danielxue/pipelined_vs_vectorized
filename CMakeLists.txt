cmake_minimum_required(VERSION 3.21)
project(pipelined_vs_vectorized)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

file(GLOB HEADERS "src/common/*.h")
add_executable(pipelined_executor src/pipelined_executor/pipelined_executor.cpp ${HEADERS})
add_executable(vectorized_executor src/vectorized_executor/vectorized_executor.cpp ${HEADERS})
add_executable(vectorized_executor_no_simd src/vectorized_executor/vectorized_executor.cpp ${HEADERS})

target_link_libraries(pipelined_executor LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries(vectorized_executor LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries(vectorized_executor_no_simd LINK_PUBLIC ${Boost_LIBRARIES})

set_target_properties(pipelined_executor PROPERTIES COMPILE_FLAGS "-Wall -fPIC -save-temps -g -march=native -O3 -fno-tree-vectorize")
set_target_properties(vectorized_executor PROPERTIES COMPILE_FLAGS "-Wall -fPIC -save-temps -g -march=native -O3")
set_target_properties(vectorized_executor_no_simd PROPERTIES COMPILE_FLAGS "-Wall -fPIC -save-temps -g -O3 -fno-tree-vectorize")
