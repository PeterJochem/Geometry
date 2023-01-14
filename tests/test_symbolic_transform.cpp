#include "transform/symbolic_transform.hpp"
#include "transform/transform.hpp"
#include "transform/frame.hpp"
#include <gtest/gtest.h>
#include <Eigen/Dense>



TEST(SymbolicTransform1, test_pure_yaw_at_zero_rads_is_identity) {

    GiNaC::symbol yaw("yaw");
    geometry::SymbolicTransform transform = geometry::SymbolicTransform(0., 0., 0., yaw, 0., 0.);

    //geometry::SymbolicTransform result = transform1 * transform1;

    GiNaC::exmap map = {{yaw, 0.}};
    auto result = GiNaC::evalf(transform.matrix.subs(map));

    geometry::Frame parent = geometry::Frame("parent");
    geometry::Frame child = geometry::Frame("child");
    geometry::Transform result_transform = geometry::SymbolicTransform::convert_to_transform(parent, child, result);

    EXPECT_EQ(result_transform, geometry::Transform::identity(parent, child));
}