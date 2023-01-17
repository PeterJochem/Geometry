#include "transform/symbolic_transform.hpp"
#include "transform/transform.hpp"


namespace geometry {
    
    template <class X, class Y, class Z, class Roll, class Pitch, class Yaw>
    SymbolicTransform::SymbolicTransform(X x, Y y, Z z, Roll roll, Pitch pitch, Yaw yaw) {

           using namespace GiNaC;

            auto cos_roll = cos(roll);
            auto sin_roll = sin(roll);
            GiNaC::matrix roll_matrix = {{1.0, 0.0, 0.0, 0.}, 
                                {0., cos_roll, -sin_roll, 0.},
                                {0., sin_roll, cos_roll, 0.},
                                {0., 0., 0., 1.}
                                }; 

            auto cos_pitch = cos(pitch);
            auto sin_pitch = sin(pitch);
            GiNaC::matrix pitch_matrix = {{cos_pitch, 0.0, sin_pitch, 0.}, 
                                {0., 1., 0., 0.},
                                {-sin_pitch, 0., cos_pitch, 0.},
                                {0., 0., 0., 1.}
                                };

            auto cos_yaw = cos(yaw);
            auto sin_yaw = sin(yaw);
            GiNaC::matrix yaw_matrix = {{cos_yaw, -sin_yaw, 0., 0.}, 
                              {sin_yaw, cos_yaw, 0., 0.},
                              {0., 0., 1., 0.},
                              {0., 0., 0., 1.}
                              };

            GiNaC::matrix translation = {{1., 0., 0., x}, 
                              {0., 1., 0., y},
                              {0., 0., 1., z},
                              {0., 0., 0., 1.}
                              };


            this->matrix = translation.mul(roll_matrix.mul(pitch_matrix.mul(yaw_matrix)));
            //this->matrix = (roll_matrix.mul(pitch_matrix.mul(yaw_matrix))).mul(translation);
    }

    template SymbolicTransform::SymbolicTransform(double x, double y, double z, GiNaC::symbol roll, double pitch, double yaw);
    template SymbolicTransform::SymbolicTransform(double x, double y, double z, double roll, GiNaC::ex pitch, double yaw);
    template SymbolicTransform::SymbolicTransform(double x, double y, double z, double roll, GiNaC::symbol pitch, double yaw);
    template SymbolicTransform::SymbolicTransform(double x, double y, double z, double roll, double pitch, GiNaC::symbol yaw);
    template SymbolicTransform::SymbolicTransform(double x, double y, double z, double roll, double pitch, GiNaC::ex yaw);
    template SymbolicTransform::SymbolicTransform(double x, double y, double z, double roll, double pitch, double yaw);

    template SymbolicTransform::SymbolicTransform(double x, double y, double z, GiNaC::ex roll, double pitch, double yaw);
    //GiNaC::ex


    SymbolicTransform::SymbolicTransform(GiNaC::matrix matrix) {
        this->matrix = matrix;
    }

    SymbolicTransform operator*(const SymbolicTransform &lhs, const SymbolicTransform &rhs) {
        
        return SymbolicTransform(lhs.matrix.mul(rhs.matrix));
    }


}