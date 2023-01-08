#ifndef TRANSFORM_TREE_VISUALIZER
#define TRANSFORM_TREE_VISUALiZER
#include <vector>
#include "transform/transform_tree.hpp"

namespace geometry {

class TransformTreeVisualizer {

    public:
        //TransformTreeVisualizer(TransformTree& tree);
        virtual void visualize() = 0;
        virtual void stop_visualization() = 0;
    protected:
        TransformTree* tree;


};
}
#endif
