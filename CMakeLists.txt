cmake_minimum_required(VERSION 3.16.3)
project(Geometry)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)
find_package(Eigen3 3.3 REQUIRED)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})

include_directories(/usr/include/ginac/)
add_subdirectory(src/stl_parser/)

add_library(geometry
  src/transform/transform.cpp 
  src/transform/utilities.cpp  
  src/transform/static_transform_tree.cpp
  src/transform/transform_tree.cpp
  src/primitives/vector.cpp
  src/primitives/axis.cpp
  src/transform/frame.cpp
  src/transform/symbolic_transform.cpp
  src/conversions/conversions.cpp
  src/primitives/point.cpp
  src/meshes/mesh.cpp
  src/meshes/stl_parser.cpp
)

target_include_directories(geometry PUBLIC ${EIGEN3_INCLUDE_DIR} ./include src/stl_parser/)
target_link_libraries(geometry PUBLIC Eigen3::Eigen /usr/lib/libginac.so parse_stl)

set(BUILD_TESTS True)
if (BUILD_TESTS)
  add_subdirectory(tests)
endif()
