cmake_minimum_required(VERSION 3.16.3)
project(Geometry)

#set(CMAKE_CXX_STANDARD 11)

include_directories(include)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})


add_library(geometry
  src/transform/transform.cpp 
  src/transform/utilities.cpp  
  src/transform/static_transform_tree.cpp
  src/transform/transform_tree.cpp
  src/primitives/vector.cpp
  src/primitives/axis.cpp
  src/transform/frame.cpp
  )

target_link_libraries(geometry PUBLIC Eigen3::Eigen)

set(BUILD_TESTS True)
if (BUILD_TESTS)
  add_subdirectory(tests)
endif()
