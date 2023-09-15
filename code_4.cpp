#include <iostream>
#include <vector>


struct Point {

    double x;

    double y;

};

Point calculateCentroid(const std::vector<Point>& points) {

    Point centroid = {0.0, 0.0};

    int numPoints = points.size();

    for (const Point& p : points) {

        centroid.x += p.x;
        centroid.y += p.y;

    }

    centroid.x /= numPoints;
    centroid.y /= numPoints;

    return centroid;

}


int main() {

    std::vector<Point> shapePoints = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}}; 

    Point centroid = calculateCentroid(shapePoints);

    std::cout << "Centroid of the shape: (" << centroid.x << ", " << centroid.y << ")\n";

    return 0;

}

