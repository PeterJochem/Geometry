#include "transform/transform.hpp"

namespace geometry {

    Transform::Transform(Frame parent, Frame child, double x, double y, double z, double roll, double pitch, double yaw) : 
    parent(parent), child(child), x(x), y(y), z(z), roll(roll), pitch(pitch), yaw(yaw) {
        
        matrix = constructMatrix(x, y, z, roll, pitch, yaw);
    }

    Transform::Transform(std::string parent, std::string child, double x, double y, double z, double roll, double pitch, double yaw): 
    x(x), y(y), z(z), roll(roll), pitch(pitch), yaw(yaw) {

        this->parent = Frame(parent); 
        this->child = Frame(child);

        matrix = constructMatrix(x, y, z, roll, pitch, yaw);
    }

    Transform::Transform(Frame parent, Frame child, Eigen::Matrix4d matrix): parent(parent), child(child), matrix(matrix) {
        
        std::tie(x, y, z) = utilities::parse_position(matrix);
        std::tie(roll, pitch, yaw) = utilities::parse_euler_angles(matrix);
    }

    Transform::Transform(Frame parent, Frame child, Vector3D position, Vector3D euler_angles): parent(parent), child(child) {
        
        
        std::vector<float> coordinates = position.coordinates();
        x = coordinates[0];
        y = coordinates[1];
        z = coordinates[2];

        std::vector<float> euler_angles1 = euler_angles.coordinates();
        roll = euler_angles1[0];
        pitch = euler_angles1[1];
        yaw = euler_angles1[2];

        matrix = constructMatrix(x, y, z, roll, pitch, yaw);
    }

    Transform::Transform() {
        
    }

    double Transform::get_x() {
        return x;
    }

    double Transform::get_y() {
        return y;
    }

    double Transform::get_z() {
        return z;
    }

    double Transform::get_roll() {
        return roll;
    } 
    
    double Transform::get_pitch() {
        return pitch;
    }
    
    double Transform::get_yaw() {
        return yaw;
    }

    void Transform::set_roll(double roll) {

        this->roll = roll;
        this->matrix = constructMatrix(x, y, z, roll, pitch, yaw);
    }
    
    void Transform::set_pitch(double pitch) {

        this->pitch = pitch;
        this->matrix = constructMatrix(x, y, z, roll, pitch, yaw);
    }
    
    void Transform::set_yaw(double yaw) {

        this->yaw = yaw;
        this->matrix = constructMatrix(x, y, z, roll, pitch, yaw);
    }

    Eigen::Matrix4d Transform::constructMatrix(double x, double y, double z, double roll, double pitch, double yaw) {
        
        Eigen::Matrix4d matrix = Eigen::Matrix4d::Zero(4, 4);

        // Set the position components.
        matrix(0,3) = x;
        matrix(1,3) = y;
        matrix(2,3) = z;

        // Construct the rotation matrix.
        Eigen::Matrix3d rotation_matrix = utilities::euler_angles_to_rotation_matrix(roll, pitch, yaw);
        
        // Copy the rotation entries into the larger transformation matrix.
        for (int row = 0; row < rotation_matrix.rows(); row++) {
            for (int col = 0; col < rotation_matrix.cols(); col++) {
                matrix(row, col) = rotation_matrix(row, col);
            }
        }

        // Set the homogenous coordinate.
        matrix(3,3) = 1.;
        return matrix;
    }

    Frame Transform::get_parent() const {
        return parent;
    }

    Frame Transform::get_child() const {
        return child;
    }

    Vector3D Transform::getPosition() const {
        return Vector3D(x, y, z);
    }

    Vector3D Transform::getEulerAngles() const {
        return Vector3D(roll, pitch, yaw);
    }

    Transform Transform::multiply(std::vector<Transform> transforms) {
        

        if (transforms.size() < 2) {
            throw std::runtime_error("The list of transforms must have at least two items.");
        }

        Frame parent = transforms[0].get_parent();
        Frame child = transforms[transforms.size() - 1].get_child();

        std::vector<Eigen::Matrix4d> matrices = std::vector<Eigen::Matrix4d>();
        for (std::vector<Transform>::iterator itr = transforms.begin(); itr != transforms.end(); itr++) {
            matrices.push_back(itr->matrix);
        }

        Eigen::Matrix4d result = Eigen::Matrix4d::Identity(4,4);
        for (std::vector<Eigen::Matrix4d>::iterator itr = matrices.begin(); itr != matrices.end(); itr++) {
            result = result * (*itr);
        }

        return Transform(parent, child, result);
    }

    Transform operator*(const Transform &lhs, const Transform &rhs) {
        return Transform(lhs.get_parent(), rhs.get_child(), lhs.matrix * rhs.matrix);
    }

    bool operator==(const Transform &lhs, const Transform &rhs) {

        bool matching_parents = lhs.get_parent() == (rhs.get_parent());
        bool matching_children = lhs.get_child() == (rhs.get_child());
        if (!(matching_parents && matching_children)) {
            return false;
        }

        bool equal_position = lhs.getPosition() == rhs.getPosition();
        bool equal_angles = lhs.getEulerAngles() == rhs.getEulerAngles();
        return equal_position && equal_angles;
    }

    bool operator!=(const Transform &lhs, const Transform &rhs) {

        return !(lhs == rhs);
    }

    /**
     * @brief Inverse of transformation matrix reverses which 
     * frame is the parent frame.
     * 
     * @return Transform 
     */
    Transform Transform::Transform::inverse() {

        return Transform(child, parent, matrix.inverse());
    }

    std::ostream& operator<<(std::ostream &os, Transform &transform) {
        
        Vector3D position = transform.getPosition();
        Vector3D euler_angles = transform.getEulerAngles();
        os << "Transform from " << transform.get_parent() << " to " << transform.get_child() << "\n";
        os << "\t Position = " << position << ").\n";
        os << "\t Euler Angles = " << euler_angles << std::endl;
        os << "\t Matrix = " << transform.matrix << std::endl;
        return os;
    }

    Transform Transform::identity(Frame parent, Frame child) {
        return Transform(parent, child, 0., 0., 0., 0., 0., 0.);
    }
}
