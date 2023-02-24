#ifndef MESH
#define MESH
#include "transform/transform.hpp"
#include "primitives/point.hpp"
#include "parse_stl.h"
#include <tuple>
#include <vector>

namespace geometry {

class Mesh {

    public:
        Mesh();

        // Get rid of thsee       
        Mesh(Transform transform);
        Mesh(Transform transform, std::string file_name);
        Mesh(Transform transform, std::vector<Point3D> vertices, std::vector<std::tuple<int, int, int>> triangles);
        Transform get_transform();

    protected:
        Transform transform;

    private:
        
};

class CollisionMesh: public Mesh {

    public:
        CollisionMesh();
        CollisionMesh(std::vector<Point3D> vertices, std::vector<std::tuple<int, int, int>> triangles);
        std::vector<Point3D> get_vertices();
        std::vector<std::tuple<int, int, int>> get_triangles();
    private:
        std::vector<Point3D> vertices;
        std::vector<std::tuple<int, int, int>> triangles;
};

class VisualMesh: public Mesh {

    public:
        VisualMesh();
        VisualMesh(Transform transform, std::string file_name);
        std::string get_file_name();

    private:
        std::string file_name;
};
}
#endif