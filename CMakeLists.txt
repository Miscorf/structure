cmake_minimum_required(VERSION 3.23)

project (structure)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

aux_source_directory(. DIR_SRCS)
include_directories("src")
include_directories("include")


include_directories(${PROJECT_SOURCE_DIR}/HDF5/include)
link_directories(${PROJECT_SOURCE_DIR}/HDF5/lib/vc14/x64/release)
# add_subdirectory(src)
link_libraries(ws2_32)

add_executable(st main.cpp)
add_executable(test test.cpp)


target_link_libraries(st hdf5.lib)
target_link_libraries(st hdf5_cpp.lib)

