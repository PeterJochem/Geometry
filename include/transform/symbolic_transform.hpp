#ifndef SYMBOLICTRANSFORM
#define SYMBOLICTRANSFORM
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
            GiNaC::matrix matrix;
        private:
    };
}
#endif