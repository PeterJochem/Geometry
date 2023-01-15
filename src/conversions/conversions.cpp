#include "conversions/conversions.hpp"

namespace geometry {
    namespace conversions {

        geometry::Transform convert_to_transform(geometry::Frame parent, geometry::Frame child, GiNaC::ex matrix) {

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
    }
}