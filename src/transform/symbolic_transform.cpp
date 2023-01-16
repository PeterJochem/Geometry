#include "transform/symbolic_transform.hpp"
#include "transform/transform.hpp"


namespace geometry {
    
    template <class X, class Y, class Z, class Roll, class Pitch, class Yaw>
    SymbolicTransform::SymbolicTransform(X x, Y y, Z z, Roll roll, Pitch pitch, Yaw yaw) {

           using namespace GiNaC;

            GiNaC::matrix roll_matrix = {{1.0, 0.0, 0.0, 0.}, 
                                {0., cos(roll), -sin(roll), 0.},
                                {0., sin(roll), cos(roll), 0.},
                                {0., 0., 0., 1.}
                                }; 

            
            GiNaC::matrix pitch_matrix = {{cos(pitch), 0.0, sin(pitch), 0.}, 
                                {0., 1., 0., 0.},
                                {-sin(pitch), 0., cos(pitch), 0.},
                                {0., 0., 0., 1.}
                                };


            GiNaC::matrix yaw_matrix = {{cos(yaw), -sin(yaw), 0., x}, 
                              {sin(yaw), cos(yaw), 0., y},
                              {0., 0., 1., z},
                              {0., 0., 0., 1.}
                              };
            
            this->matrix = roll_matrix.mul(pitch_matrix.mul(yaw_matrix));
    }

    template SymbolicTransform::SymbolicTransform(double x, double y, double z, GiNaC::symbol roll, double pitch, double yaw);
    template SymbolicTransform::SymbolicTransform(double x, double y, double z, double roll, GiNaC::symbol pitch, double yaw);
    template SymbolicTransform::SymbolicTransform(double x, double y, double z, double roll, double pitch, GiNaC::symbol yaw);
    template SymbolicTransform::SymbolicTransform(double x, double y, double z, double roll, double pitch, double yaw);



    SymbolicTransform::SymbolicTransform(GiNaC::matrix matrix) {
        this->matrix = matrix;
    }

    SymbolicTransform operator*(const SymbolicTransform &lhs, const SymbolicTransform &rhs) {
        
        return SymbolicTransform(lhs.matrix.mul(rhs.matrix));
    }


}