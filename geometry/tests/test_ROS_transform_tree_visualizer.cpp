#include "transform/ROS_transform_tree_visualizer.hpp"
#include <gtest/gtest.h>

using namespace geometry;

TEST(ROSTransformTreeVisualizer, testConstructor) {

    ROSTransformTreeVisualizer visualizer = ROSTransformTreeVisualizer(nullptr, "a fake name");

    EXPECT_EQ(1, 1);
}