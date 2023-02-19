#include "primitives/point.hpp"
#include "transform/utilities.hpp"
#include <ostream>


namespace geometry {


    Point3D::Point3D(float x, float y, float z): x(x), y(y), z(z) {
    }

    int Point3D::dimensions() const {
        return 3;
    }

    float Point3D::get_x() {
        return x;
    }

    float Point3D::get_y() {
        return y;
    }

    float Point3D::get_z() {
        return z;
    }

    std::vector<float> Point3D::coordinates() const {
        return {x, y, z};
    }

    bool operator==(const Point &lhs, const Point &rhs) {

        if (lhs.dimensions() != rhs.dimensions()) {
            return false;
        }

        const std::vector<float> lhs_coordinates = lhs.coordinates();
        const std::vector<float> rhs_coordinates = rhs.coordinates();

        for (int i = 0; i < lhs_coordinates.size(); i++) {
            if (!utilities::nearly_equal(lhs_coordinates[i], rhs_coordinates[i])) {
                return false;
            }
        }

        return true;
    }


    bool operator!=(const Point &lhs, const Point &rhs) {
        return !(lhs == rhs);
    }


}