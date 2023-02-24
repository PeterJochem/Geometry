#include "meshes/mesh.hpp"
#include "transform/utilities.hpp"
#include <ostream>


namespace geometry {

    Mesh::Mesh() {

    }

    Mesh::Mesh(Transform transform): transform(transform) {

    }

    Mesh::Mesh(Transform transform, std::string file_name): transform(transform) {
        // load the mesh from file
    }

    Transform Mesh::get_transform() {
        return transform;
    }


    VisualMesh::VisualMesh(Transform transform, std::string file_name): file_name(file_name) {
        this->transform = transform;
        this->file_name = file_name;
    }

    VisualMesh::VisualMesh() {
        // delete me
    }

    std::string VisualMesh::get_file_name() {
        return file_name;
    }

    CollisionMesh::CollisionMesh() {

    }

    CollisionMesh::CollisionMesh(std::vector<Point3D> vertices, std::vector<std::tuple<int, int, int>> triangles): vertices(vertices), triangles(triangles) {

    }

    std::vector<Point3D> CollisionMesh::get_vertices() {
        return vertices;
    }

    std::vector<std::tuple<int, int, int>> CollisionMesh::get_triangles() {
        return triangles;
    }



}