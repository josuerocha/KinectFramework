cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
 
project(PCL_openni_viewer)
 
find_package(PCL 1.8 REQUIRED)
 
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
 
set(PCL_BUILD_TYPE Release)
 
file(GLOB PCL_openni_viewer_SRC
    "src/*.h"
    "src/*.cpp"
)
add_executable(execute ${PCL_openni_viewer_SRC})
 
target_link_libraries (execute ${PCL_LIBRARIES})
