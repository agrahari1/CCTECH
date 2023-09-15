#include <iostream>
#include <vector>
#include <cmath>


struct Point {

    double x, y;
    Point(double _x, double _y) : x(_x), y(_y) {}

} ;


double calculateArea(const std::vector<Point>& polygon) {

    double area = 0.0 ;
    int n = polygon.size() ;

    for (int i = 0; i < n; i++) {

        int j = (i + 1) % n ;
        area += (polygon[i].x * polygon[j].y - polygon[j].x * polygon[i].y) ;

    }

    return 0.5 * std::abs(area) ;

}


int findPointToRemove(const std::vector<Point>& points) {

    int n = points.size();
    double maxArea = 0.0;
    int pointToRemove = -1;

    for (int i = 0; i < n; i++) {

        std::vector<Point> tempPoints = points;  
        tempPoints.erase(tempPoints.begin() + i);  
        double area = calculateArea(tempPoints);    

        if (area > maxArea) {

            maxArea = area;
            pointToRemove = i;

        }
    }

    return pointToRemove;
}

int main() {

    std :: vector<Point> points ;
    int n ;

    std:: cout << "Enter the number of points: " ;
    std:: cin >> n ;

    std::cout << "Enter the coordinates of each point (x y) : " << std :: endl ;
    for (int i = 0; i < n; i++) {

        double x, y ;
        std:: cin >> x >> y;
        points.emplace_back(x, y) ;

    }

    int pointToRemove = findPointToRemove(points);
    if (pointToRemove != -1) {

        std::cout << "Remove point (" << points[pointToRemove].x << ", " << points[pointToRemove].y << ") to maximize the area" << std::endl;
    
    } else {

        std:: cout << "No point can be removed to maximize the area " << std::endl;

    }

    return 0;
}
