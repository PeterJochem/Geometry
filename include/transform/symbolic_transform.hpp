#include "transform/transform.hpp"
#include <ginac/ginac.h>
#include <Eigen/Dense>


namespace geometry {


    class SymbolicTransform {
        
        public:
            SymbolicTransform(float x, float y, float z, GiNaC::symbol roll, float pitch, float yaw);
            SymbolicTransform(float x, float y, float z, float roll, GiNaC::symbol pitch, float yaw);
            SymbolicTransform(float x, float y, float z, float roll, float pitch, GiNaC::symbol yaw);
            SymbolicTransform(GiNaC::matrix matrix);
            friend SymbolicTransform operator*(const SymbolicTransform &lhs, const SymbolicTransform &rhs);

            // Move this to conversions
            static geometry::Transform convert_to_transform(geometry::Frame parent, geometry::Frame child, GiNaC::ex matrix);

             GiNaC::matrix matrix;
        private:

    };
}