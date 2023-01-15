#ifndef SYMBOLICTRANSFORM
#define SYMBOLICTRANSFORM
#include "transform/transform.hpp"
#include <ginac/ginac.h>
#include <Eigen/Dense>


namespace geometry {

    class SymbolicTransform {
        
        public:
            
            template <class X, class Y, class Z, class Roll, class Pitch, class Yaw>
            SymbolicTransform(X x, Y y, Z z, Roll roll, Pitch pitch, Yaw yaw);
            SymbolicTransform(GiNaC::matrix matrix);
            
            friend SymbolicTransform operator*(const SymbolicTransform &lhs, const SymbolicTransform &rhs);
            
            GiNaC::matrix matrix;
        private:

    };
}
#endif