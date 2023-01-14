#include "transform/symbolic_transform.hpp"
#include "transform/transform.hpp"


namespace geometry {

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
        //rotation_matrix_to_euler_angles
        Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Zero(3, 3);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {

                if (GiNaC::is_a<GiNaC::numeric>(  matrix[i, j] )) {
                    double d = GiNaC::ex_to<GiNaC::numeric>(matrix[i, j]).to_double();
                    rotation_matrix(i, j) = d;
                } 
                else {
                    throw std::runtime_error("The GiNac expression is not numeric.");
                }
            }
        }

        auto[roll, pitch, yaw] = utilities::rotation_matrix_to_euler_angles(rotation_matrix);

        bool x_is_numeric, y_is_numeric, z_is_numeric;

        x_is_numeric = GiNaC::is_a<GiNaC::numeric>(matrix[0, 3]);
        y_is_numeric = GiNaC::is_a<GiNaC::numeric>(matrix[1, 3]);
        z_is_numeric = GiNaC::is_a<GiNaC::numeric>(matrix[2, 3]);

        if (!(x_is_numeric && y_is_numeric && z_is_numeric)) {
            throw std::runtime_error("Part of the GiNaC expression is not numeric.");
        }

        float x, y, z;
        x = GiNaC::ex_to<GiNaC::numeric>(matrix[0, 3]).to_double();
        y = GiNaC::ex_to<GiNaC::numeric>(matrix[1, 3]).to_double();
        z = GiNaC::ex_to<GiNaC::numeric>(matrix[2, 3]).to_double();

        return geometry::Transform(parent, child, 0., 0., 0., 0., 0., 0.);
    }



    SymbolicTransform::SymbolicTransform(float x, float y, float z, GiNaC::symbol roll, float pitch, float yaw) {

           using namespace GiNaC;

           this->matrix = {{1.0, 0.0, 0.0, x}, 
                            {0., cos(roll), -sin(roll), y},
                            {0., sin(roll), cos(roll), z},
                            {0., 0., 0., 1.}
                          }; 
    }


    SymbolicTransform::SymbolicTransform(float x, float y, float z, float roll, GiNaC::symbol pitch, float yaw) {

        using namespace GiNaC;

        this->matrix = {{cos(pitch), 0.0, sin(pitch), x}, 
                        {0., 1., 0., y},
                        {-sin(pitch), 0., cos(pitch), z},
                        {0., 0., 0., 1.}
                        };
    }

    SymbolicTransform::SymbolicTransform(float x, float y, float z, float roll, float pitch, GiNaC::symbol yaw) {
        
        using namespace GiNaC;

        this->matrix = {{cos(yaw), -sin(yaw), 0., x}, 
                        {sin(yaw), cos(yaw), 0., y},
                        {0., 0., 1., z},
                        {0., 0., 0., 1.}
                        };
    }

    SymbolicTransform::SymbolicTransform(GiNaC::matrix matrix) {
        this->matrix = matrix;
    }

    SymbolicTransform operator*(const SymbolicTransform &lhs, const SymbolicTransform &rhs) {
        
        return SymbolicTransform(lhs.matrix.mul(rhs.matrix));
    }


}