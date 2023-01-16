#ifndef TRANSFORM
#define TRANSFORM
#include <ostream>
#include <vector>
#include <string>
#include <Eigen/Dense>
#include <chrono>
#include <unistd.h>
#include "transform/utilities.hpp"
#include "transform/transform.hpp"
#include "transform/frame.hpp"
#include "primitives/vector.hpp"


namespace geometry {

    class Transform {
        public:
            Transform(Frame parent, Frame child, double x, double y, double z, double roll, double pitch, double yaw);
            Transform(Frame parent, Frame child, Vector3D position, Vector3D euler_angles);
            Transform(Frame parent, Frame child, Eigen::Matrix4d matrix);
            Transform(std::string parent, std::string child, double x, double y, double z, double roll, double pitch, double yaw);
            Transform();
            friend Transform operator*(const Transform &lhs, const Transform &rhs);
            friend bool operator==(const Transform &lhs, const Transform &rhs);
            friend bool operator!=(const Transform &lhs, const Transform &rhs);
            Vector3D getPosition() const;
            Vector3D getEulerAngles() const;
            double get_x();
            double get_y();
            double get_z();
            double get_roll();
            double get_pitch();
            double get_yaw();
            Frame get_parent() const;
            Frame get_child() const;
            void set_roll(double);
            void set_pitch(double);
            void set_yaw(double);
            static Transform identity(Frame parent, Frame child);
            Eigen::Matrix4d matrix;
            static Transform multiply(std::vector<Transform>); 
            Transform inverse();
        private:
            double roll, pitch, yaw;
            double x, y, z;
            Frame parent, child;
            Eigen::Matrix4d constructMatrix(double x, double y, double z, double roll, double pitch, double yaw);
    };

    // Make this a friend?
    std::ostream& operator<<(std::ostream &os, Transform &transform);
}
#endif
