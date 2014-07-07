# This is the root ITK CMakeList file: 
cmake_minimum_required(VERSION 2.6)

# This project is designed to be built outside the Insight source tree.
PROJECT(GUI)

## Find Libraries ##
# find package(libraryName /QUIET /REQUIRED) generate variables containing the library way
# include(${VariableName}) 

# Find VTK
find_package(VTK 5.10 REQUIRED)
include(${VTK_USE_FILE})

# Find QT
find_package(Qt4 REQUIRED)
INCLUDE (${QT_USE_FILE})

# Find ITK
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# Find ItkVtkGlue
#find_package(ItkVtkGlue REQUIRED)
#include(${ItkVtkGlue_USE_FILE})

# MotherWindow.h generation
QT4_WRAP_UI(UI_SOURCES MotherWindow.ui)

# Meta Object Compiler
QT4_WRAP_CPP(MOC_SOURCES DaughterWindow.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

# window_SOURCES and window_HEADERS
SET(Window_SOURCES GUI.cxx DaughterWindow.cxx)
SET(Window_HEADERS DaughterWindow.h)

# EXECUTABLE
ADD_EXECUTABLE(GUI ${MOC_SOURCES} ${UI_SOURCES} ${Window_SOURCES} ${Window_HEADERS})

TARGET_LINK_LIBRARIES(GUI  ${QT_LIBRARIES} ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${ItkVtkGlue_LIBRARIES} QVTK)
