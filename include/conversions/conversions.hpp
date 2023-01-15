#ifndef CONVERSIONS
#define CONVERSIONS
#include "transform/symbolic_transform.hpp"
#include "transform/transform.hpp"
#include <ginac/ginac.h>


namespace geometry {
    namespace conversions {

        geometry::Transform convert_to_transform(geometry::Frame parent, geometry::Frame child, GiNaC::ex matrix);
    }
}
#endif
