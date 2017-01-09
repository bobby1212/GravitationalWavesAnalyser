#include "Triangulation.h"



Triangulation::Triangulation(ErrorHandler* _errorHandler)
{
	
}

Triangulation::~Triangulation()
{
}

void Triangulation::Triangulate(std::vector<Point>* points, float min, float max)
{
	std::vector<Point*> polyline;

	polyline.push_back(new Point(min, min));
	polyline.push_back(new Point(min, max));
	polyline.push_back(new Point(max, max));
	polyline.push_back(new Point(max, min));

	for (auto &i : *points)
		polyline.push_back(new Point(i.x, i.y, i.z,true));

	p2t::CDT* cdt = new p2t::CDT(polyline);

	cdt->Triangulate();

	trianglesMap = cdt->GetMap();

	std::list<Triangle*>::iterator itr = trianglesMap.begin();

	return;
}
