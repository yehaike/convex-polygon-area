a#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <sstream>

using namespace std;

// Helper methods
vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

//Split method to create the polygon
vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

//co-ordinates of each point of the polygon
class Point {
public:
    Point(double x, double y) : mX(x), mY(y) {}
    double getX() const { return mX; }
    double getY() const { return mY; }

    static double getDistance(const Point& point1, const Point& point2)  {
        double ac = abs(point1.getX() - point2.getX());
        double bc = abs(point1.getY() - point2.getY());
        return sqrt(ac * ac + bc * bc);
    }
    double getDistance(const Point& point) {
        return Point::getDistance(point, *this);
    }

public:
    double mX,mY;
};

//area of each polygon is calculated as a triangle
class Triangle {
public:
    Triangle(Point a, Point b, Point c) : mA(a), mB(b), mC(c) {}
    const Point& getA() { return mA; }
    const Point& getB() { return mB; }
    const Point& getC() { return mC; }

    double getArea() {
        // Using Heron's formula
        double a = mA.getDistance(mB);
        double b = mB.getDistance(mC);
        double c = mC.getDistance(mA);
        double s = (a + b + c)/2.0;
        return sqrt( s * (s - a) * (s - b) * (s - c) );
    }

protected:
    Point mA,mB,mC;
};

//the complex polygon whose area is to be calculated
class Polygon {
public:
    Polygon() {}
    void addPoint(const Point& point) {
        mPoints.push_back(point);
    }

    double getArea() {
        double area = 0.0;
        for (int idxPoint=0; idxPoint<mPoints.size()-2; ++idxPoint) {
            Triangle triangle(mPoints[0], mPoints[idxPoint+1], mPoints[idxPoint+2]);
            area += triangle.getArea();
        }
        return area;
    }

protected:
    vector<Point> mPoints;
};


int main(int argc, char* argv[]) {
    Polygon polygon;
    string input;

    cout << "Enter number of points: ";
    getline(cin,input);

    if (input.size() == 0) { return 1; }
    int numberOfPoints = atoi(input.c_str());

    cout << "Point data expected as comma separated, like: 1.0,2.0" << endl;
    while(numberOfPoints > 0) {
        cout << "Enter point: ";
        if (input.size()) {
            getline(cin,input);
        }

        vector<string> coordinates = split(input,',');
        if (coordinates.size() > 1) {
            polygon.addPoint(Point(atof(coordinates[0].c_str()), atof(coordinates[1].c_str())));
            numberOfPoints--;
        }
    }

    cout << polygon.getArea() << endl;

    return 0;
}
