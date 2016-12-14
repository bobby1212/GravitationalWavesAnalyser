#pragma once
#include "SharedDefines.h"

class Triangle;

typedef std::shared_ptr<Triangle> pTriangle;
typedef std::vector<std::vector<double>> matrix;

struct Point
{
	double x;
	double y;
	double z;

	Point() : x(0), y(0), z(0) {}
	Point(double x, double y) : x(x), y(y), z(0) {}
	Point(double x, double y, double z) : x(x), y(y), z(z) {}

	void normalize()
	{
		x = x / x;
		y = y / y;
		z = z / z;
	}
};

struct Edge
{
	int p1, p2;
	pTriangle triangle;

	Edge(int _p1, int _p2, pTriangle _triangle)
	{
		p1 = _p1;
		p2 = _p2;
		triangle = _triangle;
	};
};

class Triangle
{
public:
	int p1, p2, p3;
	pTriangle n1, n2, n3;

	Triangle(int p1, int p2, int p3) : p1(p1), p2(p2), p3(p3)
	{
		n1 = nullptr;
		n2 = nullptr;
		n3 = nullptr;
	}

	void setEdge(Edge* e, pTriangle t, std::vector<Point>* points)
	{
		if ((p1 == e->p1 && p2 == e->p2) || (p1 == e->p2 && p2 == e->p1))
			n1 = t;
		if ((p2 == e->p1 && p3 == e->p2) || (p2 == e->p2 && p3 == e->p1))
			n2 = t;
		if ((p3 == e->p1 && p1 == e->p2) || (p1 == e->p2 && p3 == e->p1) || (p1 == e->p1 && p3 == e->p2))
			n3 = t;

		return;
	}
};

bool operator==(Point p1, Point p2);
bool operator==(Edge e1, Edge e2);
double distance(Point p1, Point p2);
double determinant(matrix* m);
bool CircumcircleContains(pTriangle T, Point p, std::vector<Point>* points, matrix* newMatrix);
