#ifndef POINT
#define POINT
#include <tuple>
#include <vector> 

namespace geometry {

    class Point {

        public:
            virtual std::vector<float> coordinates() const = 0;
            virtual int dimensions() const = 0;
            friend bool operator!=(const Point &lhs, const Point &rhs);
            friend bool operator==(const Point &lhs, const Point &rhs);
    };

    class Point2D: public Point {
        public:
            Point2D(float x, float y);
            int dimensions() const;
            std::vector<float> coordinates() const;
            float get_x();
            float gey_y();
        private:
            float x;
            float y;
    };


    class Point3D: public Point {
        public:
            Point3D(float x, float y, float z);
            int dimensions() const;
            std::vector<float> coordinates() const;
            float get_x();
            float get_y();
            float get_z();
        private:
            float x;
            float y;
            float z;
    };

    std::ostream& operator<<(std::ostream &os, Point& point);
}
#endif