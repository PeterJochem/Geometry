#include "transform/symbolic_transform.hpp"
#include "transform/transform.hpp"
#include "transform/frame.hpp"
#include "conversions/conversions.hpp"
#include <gtest/gtest.h>
#include <Eigen/Dense>



TEST(SymbolicTransform1, test_pure_yaw_at_zero_rads_is_identity) {

    GiNaC::symbol yaw("yaw");
    geometry::SymbolicTransform transform = geometry::SymbolicTransform(0., 0., 0., 0., 0., yaw);

    GiNaC::exmap map = {{yaw, 0.}};
    auto result = GiNaC::evalf(transform.matrix.subs(map));

    geometry::Frame parent = geometry::Frame("parent");
    geometry::Frame child = geometry::Frame("child");
    geometry::Transform result_transform = geometry::conversions::convert_to_transform(parent, child, result);

    EXPECT_EQ(result_transform, geometry::Transform::identity(parent, child));
}

TEST(SymbolicTransform1, test_pure_roll_at_zero_rads_is_identity) {

    GiNaC::symbol roll("roll");
    geometry::SymbolicTransform transform = geometry::SymbolicTransform(0., 0., 0., roll, 0., 0.);

    GiNaC::exmap map = {{roll, 0.}};
    auto result = GiNaC::evalf(transform.matrix.subs(map));

    geometry::Frame parent = geometry::Frame("parent");
    geometry::Frame child = geometry::Frame("child");
    geometry::Transform result_transform = geometry::conversions::convert_to_transform(parent, child, result);

    EXPECT_EQ(result_transform, geometry::Transform::identity(parent, child));
}

TEST(SymbolicTransform1, test_pure_pitch_at_zero_rads_is_identity) {

    GiNaC::symbol pitch("pitch");
    geometry::SymbolicTransform transform = geometry::SymbolicTransform(0., 0., 0., 0., pitch, 0.);

    GiNaC::exmap map = {{pitch, 0.}};
    auto result = GiNaC::evalf(transform.matrix.subs(map));

    geometry::Frame parent = geometry::Frame("parent");
    geometry::Frame child = geometry::Frame("child");
    geometry::Transform result_transform = geometry::conversions::convert_to_transform(parent, child, result);

    EXPECT_EQ(result_transform, geometry::Transform::identity(parent, child));
}

TEST(SymbolicTransform1, test_two_equal_and_opposite_yaw_transforms_undo_each_other) {

    GiNaC::symbol yaw1("yaw1");
    geometry::SymbolicTransform transform1 = geometry::SymbolicTransform(0., 0., 0., 0., 0., yaw1);

    GiNaC::symbol yaw2("yaw2");
    geometry::SymbolicTransform transform2 = geometry::SymbolicTransform(0., 0., 0., 0., 0., yaw2);
    
    auto result_symbolic_transform = transform1 * transform2;
        
    for (int i = 1; i < 5; i++) {

        float radians = 3.0 / i;
        GiNaC::exmap map = {{yaw1, -radians}, {yaw2, radians}};
        auto result = GiNaC::evalf(result_symbolic_transform.matrix.subs(map));

        geometry::Frame parent = geometry::Frame("parent");
        geometry::Frame child = geometry::Frame("child");
        geometry::Transform result_transform = geometry::conversions::convert_to_transform(parent, child, result);

        EXPECT_EQ(result_transform, geometry::Transform::identity(parent, child));
    }
}

TEST(SymbolicTransform1, identity_times_transform_should_equal_transform1) {

    float x = 4.;
    float y = 0.;
    float z = 0.;

    GiNaC::symbol yaw1("yaw1");
    geometry::SymbolicTransform transform1 = geometry::SymbolicTransform(0., 0., 0., 0., 0., yaw1);

    GiNaC::symbol yaw2("yaw2");
    geometry::SymbolicTransform transform2 = geometry::SymbolicTransform(x, y, z, 0., 0., yaw2);

    auto result_symbolic_transform = transform1 * transform2;
        
    float radians = M_PI/2;
    GiNaC::exmap map = {{yaw1, 0.}, {yaw2, 0.}};
    auto result = GiNaC::evalf(result_symbolic_transform.matrix.subs(map));

    geometry::Frame parent = geometry::Frame("parent");
    geometry::Frame child = geometry::Frame("child");
    geometry::Transform result_transform = geometry::conversions::convert_to_transform(parent, child, result);

    EXPECT_EQ(result_transform, geometry::conversions::convert_to_transform(parent, child, GiNaC::evalf(transform2.matrix.subs(map))));
}

TEST(SymbolicTransform1, identity_times_transform_should_equal_transform2) {

    float x = -4.;
    float y = -5.;
    float z = 14.;

    GiNaC::symbol roll1("roll1");
    geometry::SymbolicTransform transform1 = geometry::SymbolicTransform(0., 0., 0., roll1, 0., 0.);

    GiNaC::symbol roll2("roll2");
    geometry::SymbolicTransform transform2 = geometry::SymbolicTransform(x, y, z, roll1, 0., 0.);

    auto result_symbolic_transform = transform1 * transform2;
    
    float radians = M_PI/2;
    GiNaC::exmap map = {{roll1, 0.}, {roll2, 0.}};
    auto result = GiNaC::evalf(result_symbolic_transform.matrix.subs(map));

    geometry::Frame parent = geometry::Frame("parent");
    geometry::Frame child = geometry::Frame("child");
    geometry::Transform result_transform = geometry::conversions::convert_to_transform(parent, child, result);

    EXPECT_EQ(result_transform, geometry::conversions::convert_to_transform(parent, child, GiNaC::evalf(transform2.matrix.subs(map))));
}

TEST(SymbolicTransform1, identity_times_transform_should_equal_transform3) {

    float x = 4.;
    float y = 5.;
    float z = 9.;

    GiNaC::symbol pitch1("pitch1");
    geometry::SymbolicTransform transform1 = geometry::SymbolicTransform(0., 0., 0., 0., pitch1, 0.);

    GiNaC::symbol pitch2("pitch2");
    geometry::SymbolicTransform transform2 = geometry::SymbolicTransform(x, y, z, 0., pitch2, 0.);

    auto result_symbolic_transform = transform1 * transform2;
    
    float radians = M_PI/2;
    GiNaC::exmap map = {{pitch1, 0.}, {pitch2, 0.}};
    auto result = GiNaC::evalf(result_symbolic_transform.matrix.subs(map));

    geometry::Frame parent = geometry::Frame("parent");
    geometry::Frame child = geometry::Frame("child");
    geometry::Transform result_transform = geometry::conversions::convert_to_transform(parent, child, result);

    EXPECT_EQ(result_transform, geometry::conversions::convert_to_transform(parent, child, GiNaC::evalf(transform2.matrix.subs(map))));
}

TEST(SymbolicTransform1, test_rotating_around_unit_circle) {

    float x = 4.;
    float y = 0.;
    float z = 0.;

    GiNaC::symbol yaw1("yaw1");
    geometry::SymbolicTransform transform = geometry::SymbolicTransform(x, 0., 0., 0., 0., yaw1);

    GiNaC::symbol yaw2("yaw2");
    geometry::SymbolicTransform rotation_operator = geometry::SymbolicTransform(0., 0, 0., 0., 0., yaw2);

    auto result_symbolic_transform = rotation_operator * transform;
        
    float radians = M_PI/2;
    GiNaC::exmap map = {{yaw1, 0.}, {yaw2, radians}};
    auto result = GiNaC::evalf(result_symbolic_transform.matrix.subs(map));

    geometry::Frame parent = geometry::Frame("parent");
    geometry::Frame child = geometry::Frame("child");
    geometry::Transform result_transform = geometry::conversions::convert_to_transform(parent, child, result);

    EXPECT_EQ(result_transform, geometry::Transform(parent, child, 0., x, 0., 0., 0., radians));
}

TEST(SymbolicTransform1, test_rotating_around_unit_circle2) {

    float x = 4.;
    float y = 0.;
    float z = 2.;

    GiNaC::symbol yaw1("yaw1");
    geometry::SymbolicTransform transform = geometry::SymbolicTransform(x, y, z, 0., 0., yaw1);

    GiNaC::symbol yaw2("yaw2");
    geometry::SymbolicTransform rotation_operator = geometry::SymbolicTransform(0., 0., 0., 0., 0., yaw2);

    auto result_symbolic_transform = rotation_operator * transform;
        
    float radians = M_PI/2;
    GiNaC::exmap map = {{yaw1, 0.}, {yaw2, radians}};
    auto result = GiNaC::evalf(result_symbolic_transform.matrix.subs(map));

    geometry::Frame parent = geometry::Frame("parent");
    geometry::Frame child = geometry::Frame("child");
    geometry::Transform result_transform = geometry::conversions::convert_to_transform(parent, child, result);

    EXPECT_EQ(result_transform, geometry::Transform(parent, child, y, x, z, 0., 0., radians));
}

TEST(SymbolicTransform1, transform_times_identity_should_be_identity) {

    float x = 4.;
    float y = 15.;
    float z = -100.;

    GiNaC::symbol pitch1("pitch1");
    geometry::SymbolicTransform transform = geometry::SymbolicTransform(x, y, z, 0., pitch1, 0.);

    GiNaC::symbol pitch2("pitch2");
    geometry::SymbolicTransform inverse = geometry::SymbolicTransform(-x, -y, -z, 0., pitch2, 0.);
    inverse.matrix = transform.matrix.inverse();

    auto result_symbolic_transform = transform * inverse;
        
    float radians = 0;
    GiNaC::exmap map = {{pitch1, radians}, {pitch2, -radians}};
    auto result = GiNaC::evalf(result_symbolic_transform.matrix.subs(map));

    geometry::Frame parent = geometry::Frame("parent");
    geometry::Frame child = geometry::Frame("child");
    geometry::Transform result_transform = geometry::conversions::convert_to_transform(parent, child, result);

    EXPECT_EQ(result_transform, geometry::Transform(parent, child, 0., 0., 0., 0., 0., 0.));
}