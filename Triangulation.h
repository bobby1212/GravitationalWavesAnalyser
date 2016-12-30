#pragma once
#include "SharedDefines.h"
#include "GeometryDefines.h"
#include "Parser.h"

class Triangulation
{
public:
	Triangulation();
	~Triangulation();
	void SetPoints(Parser*);
	bool Triangulate();
	std::vector<pTriangle> GetTriangles() { return triangles; }
private:
	clock_t timeBegin;
	std::vector<Point> points;
    std::vector<Point>* ppoints;
	std::vector<pTriangle> illegal_triangles;
	std::vector<Edge> boundary;
	matrix triangleMatrix;
	pTriangle T1;
	pTriangle T2;
	std::vector<pTriangle> triangles;
};
