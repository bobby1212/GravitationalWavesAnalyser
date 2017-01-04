#include "GeometryDefines.h"

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

bool operator==(Edge e1, Edge e2)
{
	return e1.p1 == e2.p1 && e1.p2 == e2.p2 ? true : false;
}

float determinant(matrix* m)
{
	return
		(*m)[0][3] * (*m)[1][2] * (*m)[2][1] * (*m)[3][0] - (*m)[0][2] * (*m)[1][3] * (*m)[2][1] * (*m)[3][0] -
		(*m)[0][3] * (*m)[1][1] * (*m)[2][2] * (*m)[3][0] + (*m)[0][1] * (*m)[1][3] * (*m)[2][2] * (*m)[3][0] +
		(*m)[0][2] * (*m)[1][1] * (*m)[2][3] * (*m)[3][0] - (*m)[0][1] * (*m)[1][2] * (*m)[2][3] * (*m)[3][0] -
		(*m)[0][3] * (*m)[1][2] * (*m)[2][0] * (*m)[3][1] + (*m)[0][2] * (*m)[1][3] * (*m)[2][0] * (*m)[3][1] +
		(*m)[0][3] * (*m)[1][0] * (*m)[2][2] * (*m)[3][1] - (*m)[0][0] * (*m)[1][3] * (*m)[2][2] * (*m)[3][1] -
		(*m)[0][2] * (*m)[1][0] * (*m)[2][3] * (*m)[3][1] + (*m)[0][0] * (*m)[1][2] * (*m)[2][3] * (*m)[3][1] +
		(*m)[0][3] * (*m)[1][1] * (*m)[2][0] * (*m)[3][2] - (*m)[0][1] * (*m)[1][3] * (*m)[2][0] * (*m)[3][2] -
		(*m)[0][3] * (*m)[1][0] * (*m)[2][1] * (*m)[3][2] + (*m)[0][0] * (*m)[1][3] * (*m)[2][1] * (*m)[3][2] +
		(*m)[0][1] * (*m)[1][0] * (*m)[2][3] * (*m)[3][2] - (*m)[0][0] * (*m)[1][1] * (*m)[2][3] * (*m)[3][2] -
		(*m)[0][2] * (*m)[1][1] * (*m)[2][0] * (*m)[3][3] + (*m)[0][1] * (*m)[1][2] * (*m)[2][0] * (*m)[3][3] +
		(*m)[0][2] * (*m)[1][0] * (*m)[2][1] * (*m)[3][3] - (*m)[0][0] * (*m)[1][2] * (*m)[2][1] * (*m)[3][3] -
		(*m)[0][1] * (*m)[1][0] * (*m)[2][2] * (*m)[3][3] + (*m)[0][0] * (*m)[1][1] * (*m)[2][2] * (*m)[3][3];
}

bool CircumcircleContains(pTriangle T, Point p, std::vector<Point>* points, matrix* newMatrix)
{

	(*newMatrix)[0][0] = pow((*points)[T->p1].x, 2) + pow((*points)[T->p1].y, 2);
	(*newMatrix)[1][0] = (*points)[T->p1].x;
	(*newMatrix)[2][0] = (*points)[T->p1].y;
	(*newMatrix)[3][0] = 1;
	(*newMatrix)[0][1] = pow((*points)[T->p2].x, 2) + pow((*points)[T->p2].y, 2);
	(*newMatrix)[1][1] = (*points)[T->p2].x;
	(*newMatrix)[2][1] = (*points)[T->p2].y;
	(*newMatrix)[3][1] = 1;
	(*newMatrix)[0][2] = pow((*points)[T->p3].x, 2) + pow((*points)[T->p3].y, 2);
	(*newMatrix)[1][2] = (*points)[T->p3].x;
	(*newMatrix)[2][2] = (*points)[T->p3].y;
	(*newMatrix)[3][2] = 1;
	(*newMatrix)[0][3] = pow(p.x, 2) + pow(p.y, 2);
	(*newMatrix)[1][3] = p.x;
	(*newMatrix)[2][3] = p.y;
	(*newMatrix)[3][3] = 1;

	return determinant(newMatrix) <= 0 ? true : false;
}
