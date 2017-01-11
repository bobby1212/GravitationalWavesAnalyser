#include "Triangulation.h"



Triangulation::Triangulation(ErrorHandler* _errorHandler)
{
	
}

Triangulation::~Triangulation()
{
}

void Triangulation::Triangulate(std::vector<Point>* points, float min, float max, float minRadius, float maxRadius)
{
	std::vector<Point*> polyline;
	std::vector<Point*> hole;

	polyline.push_back(new Point(min - 100, min - 100));
	polyline.push_back(new Point(min - 100, max + 100));
	polyline.push_back(new Point(max + 100, max + 100));
	polyline.push_back(new Point(max + 100, min - 100));

	Point origin = Point(0.0f,0.0f);
	float radius = 0.0f;
	int c = 0;
	for (auto &i : *points)
	{
		++c;
		if (c % 5 != 0)
			continue;
		
		radius = distance(origin, i);
		/*if (radius < minRadius)
			hole.push_back(new Point(i.x, i.y, i.z));*/

		if(radius < maxRadius && radius > minRadius)
			polyline.push_back(new Point(i.x, i.y, i.z));
	}

	p2t::CDT* cdt = new p2t::CDT(polyline);

	//If minRadius is more than zero add a hole
	if (minRadius > 0)
	{
		cdt->AddHole(hole);
	}

	cdt->Triangulate();

	trianglesMap = cdt->GetMap();

	return;
}
