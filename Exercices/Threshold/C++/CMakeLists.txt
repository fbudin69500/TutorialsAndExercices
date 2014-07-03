# This is the root ITK CMakeList file: 
cmake_minimum_required(VERSION 2.8)

# This project is designed to be built outside the Insight source tree.
project(Threshold)

# Find Slicer3
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})

# Find GenerateCLP
find_package(GenerateCLP REQUIRED)
include(${GenerateCLP_USE_FILE})
 
# Find ITK
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

set(Threshold_SOURCE Threshold.cxx)
GENERATECLP(Threshold_SOURCE Threshold.xml) 

add_executable(Threshold ${Threshold_SOURCE})

target_link_libraries(Threshold ${ITK_LIBRARIES})

