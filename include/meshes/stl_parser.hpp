#ifndef STLPARSER
#define STLPARSER
#include "parse_stl.h"
#include "primitives/point.hpp"
#include "conversions/conversions.hpp"
#include <string>
#include <vector>

class STLParser {

    public:
        STLParser(std::string file_name);
        std::vector<geometry::Point3D> get_points();
        std::vector<std::tuple<int, int, int>> get_triangle_indices();
    
    private:
        std::vector<geometry::Point3D> points;
        std::vector<std::tuple<int, int, int>> triangle_indices;
        void load(std::string file_name);
};
#endif