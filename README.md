# Geometry
Geometry module mainly meant for robotics applications.


# Dependencies
1. Eigen3.3
2. GTest
3. CMake 

# Installing Dependencies
```
sudo apt install libeigen3-dev=3.3.7-2
sudo apt-get install libgtest-dev=1.10.0-2
sudo apt-get install cmake=3.16.3-1ubuntu1.20.04.1
```

# Building Code
```
cmake -S . -B build
cmake --build build
```

# Testing Code
```
./build/tests/test_geometry_library
```

# Installing
...
