# This is the root ITK CMakeList file: 
cmake_minimum_required(VERSION 2.8)

# This project is designed to be built outside the Insight source tree.
project(smooth)
 
# Find VTK
find_package(VTK 6.1 REQUIRED)
include(${VTK_USE_FILE})

add_executable(smooth smooth.cxx)

target_link_libraries(smooth ${VTK_LIBRARIES})
