#include "meshes/stl_parser.hpp"

STLParser::STLParser(std::string file_name) {

    // check that the path exists.
    // check that the file has a .stl file ending.
    try {
        load(file_name);
    }
    catch (const std::exception &e) {
        std::cout << "Failed to load stl file: " << e.what() << std::endl << std::flush;
        throw e;
    }
}

std::vector<geometry::Point3D> STLParser::get_points() {
    return points;
}


std::vector<std::tuple<int, int, int>> STLParser::get_triangle_indices() {
    return triangle_indices;
}

void STLParser::load(std::string file_name) {

    const std::string a = file_name;
    auto stl_data = stl::parse_stl(a);

    std::vector<geometry::Point3D> points;
    std::vector<std::tuple<int, int, int>> triangle_indices;
    auto triangles = stl_data.triangles;
    for (int i = 0; i < triangles.size(); i++) {
        auto point1 = geometry::conversions::to_point(triangles[i].v1);
        auto point2 = geometry::conversions::to_point(triangles[i].v2);
        auto point3 = geometry::conversions::to_point(triangles[i].v3);

        points.push_back(point1);
        points.push_back(point2);
        points.push_back(point3);

        int index = i * 3;
        auto indices = std::make_tuple(index, index + 1, index + 2);
        triangle_indices.push_back(indices);
    }

    this->points = points;
    this->triangle_indices = triangle_indices;
}