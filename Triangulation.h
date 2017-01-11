#pragma once
#include "SharedDefines.h"
#include "poly2tri/poly2tri.h"
#include "Parser.h"
#include "Render.h"

using namespace p2t;

class Triangulation
{
public:
	Triangulation() { };
	Triangulation(ErrorHandler* errorHandler);
	~Triangulation();

	void Triangulate(std::vector<Point>* points, float min, float max, float minRadius, float maxRadius);

	std::list<Triangle*>& GetTriangles() { return trianglesMap; }
private:
	std::list<Triangle*> trianglesMap;
};
