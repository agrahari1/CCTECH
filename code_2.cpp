#include <iostream>
#include <vector>
#include <algorithm>


using namespace std ;

struct Point {

    int x, y ;
};



int crossProduct(Point a, Point b, Point c) {

    int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

    if (val == 0) return 0 ;

    return (val > 0) ? 1 : 2 ; 
}


vector<Point> convexHull(vector<Point>& points) {

    int n = points.size();
    if (n < 3) return {}; 


    int minY = points[0].y, minIndex = 0;

    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if (y < minY || (y == minY && points[i].x < points[minIndex].x)) {
            minY = y ;
            minIndex = i ;

        }
    }

    
    swap(points[0], points[minIndex]);   
    sort(points.begin() + 1, points.end(), [&](Point a, Point b) {
        int orientation = crossProduct(points[0], a, b);
        if (orientation == 0) {

            return (a.x + a.y < b.x + b.y) ; 

        }
        return (orientation == 2); 
    });

    
    vector<Point> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    
    for (int i = 2; i < n; i++) {
        while (hull.size() > 1 && crossProduct(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) != 2) {

            hull.pop_back();
        }

        hull.push_back(points[i]);
    }

    return hull;
}


double calculateArea(vector<Point>& polygon) {
    int n = polygon.size();
    double area = 0.0;
    for (int i = 0; i < n; i++) {

        int j = (i + 1) % n;
        area += (polygon[i].x * polygon[j].y - polygon[j].x * polygon[i].y) ;

    }
    return abs(area) / 2.0;
}

int main() {
    int n;
    cout << "Enter the number of points: ";
    cin >> n;

    vector<Point> points(n);
    cout << "Enter the points (x, y) :" << endl;
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    vector<Point> convexHullPoints = convexHull(points);
    double largestArea = calculateArea(convexHullPoints);

    cout << "Largest area of the shape formed by the given set of points: " << largestArea << endl;

    return 0 ;
}
