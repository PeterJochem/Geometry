#ifndef CONVERSIONS
#define CONVERSIONS
#include "transform/symbolic_transform.hpp"
#include "transform/transform.hpp"
#include <ginac/ginac.h>
#include <cmath>


namespace geometry {
    namespace conversions {

        geometry::Transform convert_to_transform(geometry::Frame parent, geometry::Frame child, GiNaC::ex matrix);
        std::tuple<float, float, float, float> convert_to_quaternion(float roll, float pitch, float yaw);
    }
}
#endif
