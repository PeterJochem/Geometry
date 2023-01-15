#include "transform/symbolic_transform.hpp"
#include "transform/transform.hpp"


namespace geometry {

    /*
    // Move this to the local conversions
    Transform SymbolicTransform::convert_to_transform(Frame parent, Frame child, GiNaC::ex matrix) {

        // Assert there are exactly 16 items in the array
        int count = 0;
        for (auto it = matrix.begin(); it != matrix.end(); it++) {
            count++;
        } 

        if (count != 16) {
            throw std::runtime_error("The GiNac expression must have exactly 16 elements.");
        }

        // convert to euler angles
        Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Zero(3, 3);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {

                if (GiNaC::is_a<GiNaC::numeric>(matrix[i, j])) {
                    rotation_matrix(i, j) = GiNaC::ex_to<GiNaC::numeric>(matrix[i, j]).to_double();
                } 
                else {
                    throw std::runtime_error("The GiNac expression is not numeric.");
                }
            }
        }

        auto[roll, pitch, yaw] = utilities::rotation_matrix_to_euler_angles(rotation_matrix);

        bool x_is_numeric, y_is_numeric, z_is_numeric;

        x_is_numeric = GiNaC::is_a<GiNaC::numeric>(matrix.let_op(3));
        y_is_numeric = GiNaC::is_a<GiNaC::numeric>(matrix.let_op(7));
        z_is_numeric = GiNaC::is_a<GiNaC::numeric>(matrix.let_op(11));

        if (!(x_is_numeric && y_is_numeric && z_is_numeric)) {
            throw std::runtime_error("Part of the GiNaC expression is not numeric.");
        }

        float x = GiNaC::ex_to<GiNaC::numeric>(matrix.let_op(3)).to_double();
        float y = GiNaC::ex_to<GiNaC::numeric>(matrix.let_op(7)).to_double();
        float z = GiNaC::ex_to<GiNaC::numeric>(matrix.let_op(11)).to_double();

        return geometry::Transform(parent, child, x, y, z, roll, pitch, yaw);
    }
    */

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


    SymbolicTransform::SymbolicTransform(GiNaC::matrix matrix) {
        this->matrix = matrix;
    }

    SymbolicTransform operator*(const SymbolicTransform &lhs, const SymbolicTransform &rhs) {
        
        return SymbolicTransform(lhs.matrix.mul(rhs.matrix));
    }


}