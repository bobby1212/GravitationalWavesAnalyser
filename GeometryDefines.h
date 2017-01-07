#pragma once
#include "SharedDefines.h"
#include "poly2tri/poly2tri.h"

using namespace p2t;

float distance(Point& p1, Point& p2)
{
	Point a;
	a.x = p2.x - p1.x;
	a.y = p2.y - p1.y;
	double dist = sqrt(a.x*a.x + a.y*a.y);
	return dist;
}

bool operator==(Point p1, Point p2)
{
	return p1.x < p2.x + 0.1f && p1.x > p2.x - 0.1f && p1.y < p2.y + 0.1f && p1.y > p2.y - 0.1f ? true : false;
}
