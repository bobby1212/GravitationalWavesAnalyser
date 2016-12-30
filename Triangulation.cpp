#include "Triangulation.h"



Triangulation::Triangulation()
{
	timeBegin = clock();
	triangleMatrix.resize(4);
	for (int i : {0, 1, 2, 3})
		triangleMatrix[i].resize(4);
}

Triangulation::Triangulation(Parser* parser)
{
	timeBegin = clock();
	triangleMatrix.resize(4);
	for (int i : {0, 1, 2, 3})
		triangleMatrix[i].resize(4);

	points->push_back(Point(parser->GetMinX(), parser->GetMinY()));
	points->push_back(Point(parser->GetMaxX(), parser->GetMinY()));
	points->push_back(Point(parser->GetMaxX(), parser->GetMaxY()));
	points->push_back(Point(parser->GetMinX(), parser->GetMaxY()));

    points->insert(points->end(), parser->GetPoints()->begin(), parser->GetPoints()->end());
}


Triangulation::~Triangulation()
{
}

void Triangulation::SetPoints(Parser* parser)
{
    points = parser->GetPoints();

    points->insert(points->begin(), Point(parser->GetMinX(), parser->GetMaxY()));
    points->insert(points->begin(), Point(parser->GetMaxX(), parser->GetMaxY()));
    points->insert(points->begin(), Point(parser->GetMaxX(), parser->GetMinY()));
    points->insert(points->begin(), Point(parser->GetMinX(), parser->GetMinY()));

    return;
}

bool Triangulation::Triangulate()
{
	//Make initial triangles
	T1 = std::make_shared<Triangle>(3, 1, 0);
	T2 = std::make_shared<Triangle>(3, 2, 1);

	//Add the neighbours
	T1->n1 = T2;
	T2->n3 = T1;

	triangles.push_back(T1);
	triangles.push_back(T2);

    int size = points->size();
    Point p1 = (*points)[0];
    Point p2 = (*points)[1];
    Point p3 = (*points)[2];
    Point p4 = (*points)[3];

	for (auto &point : *points)
	{

        if (point == (*points)[0] || point == (*points)[1] || point == (*points)[2] || point == (*points)[3])
            continue;

		//Check wich triangles are illegal
		for (auto &T : triangles)
		{

			if (CircumcircleContains(T, point, points, &triangleMatrix))
				illegal_triangles.push_back(T);
		}

		if (illegal_triangles.size() == 0)
			return false;

		//Get Boundary
		auto T = illegal_triangles[0];
		int pos = 0;
		while (true)
		{
			if (boundary.size() > 1)
				if (boundary.front() == boundary.back())
					break;

			//Check whether an other triangle contains the same edge
			switch (pos)
			{
			case 0:
				if (std::find(illegal_triangles.begin(), illegal_triangles.end(),T->n1) != illegal_triangles.end())
				{
					if (T->n1->n1 == T)
						pos = 1;
					else if (T->n1->n2 == T)
						pos = 2;
					else if (T->n1->n3 == T)
						pos = 0;

					T = T->n1;
				}
				else //Found an edge that is on the boundary
				{
					Edge edge(T->p1, T->p2, T->n1);
					boundary.push_back(edge);
					pos++;
				}
				break;

			case 1:

				if (std::find(illegal_triangles.begin(), illegal_triangles.end(), T->n2) != illegal_triangles.end())
				{
					if (T->n2->n1 == T)
						pos = 1;
					else if (T->n2->n2 == T)
						pos = 2;
					else if (T->n2->n3 == T)
						pos = 0;
					T = T->n2;
				}
				else
				{
					Edge edge(T->p2, T->p3, T->n2);
					boundary.push_back(edge);
					pos++;
				}
				break;

			case 2:
				if (std::find(illegal_triangles.begin(), illegal_triangles.end(), T->n3) != illegal_triangles.end())
				{
					if (T->n3->n1 == T)
						pos = 1;
					else if (T->n3->n2 == T)
						pos = 2;
					else if (T->n3->n3 == T)
						pos = 0;

					T = T->n3;
				}
				else
				{
					Edge edge(T->p3, T->p1, T->n3);
					boundary.push_back(edge);
					pos = 0;
				}
				break;
			}

		}
		boundary.pop_back();
		//End of 'Get Boundary'

		//Erase illegal triangles out of the exsisting triangles
		for (auto &T : illegal_triangles)
			boost::remove_erase(triangles, T);

		//Fill up the hole
		std::vector<pTriangle> newTriangles;
		for (auto &edge : boundary)
		{
			int a = edge.p1;
			int b = edge.p2;



			auto T = std::make_shared<Triangle>(points->size() - 1, a, b);

			if (((*points)[T->p1].x == (*points)[T->p2].x && (*points)[T->p1].x == (*points)[T->p3].x) || ((*points)[T->p1].y == (*points)[T->p2].y && (*points)[T->p1].y == (*points)[T->p3].y))
				return false;

			if (!edge.triangle)
				edge.triangle = nullptr;
			else
				if (std::find(illegal_triangles.begin(), illegal_triangles.end(), edge.triangle) == illegal_triangles.end())
					edge.triangle = nullptr;
			T->n2 = edge.triangle;

			if (T->n2)
				T->n2->setEdge(&edge, T, points);

			newTriangles.push_back(T);
		}


		//Connect the new triangles
		int S = newTriangles.size();
		for (int i = 0; i < newTriangles.size(); i++)
		{
			newTriangles[i]->n1 = newTriangles[((i - 1) % S + S) % S]; //(i-1) % S should work equally
			newTriangles[i]->n3 = newTriangles[(i + 1) % S];
		}

		//Add the new triangles
		triangles.reserve(triangles.size() + distance(newTriangles.begin(), newTriangles.end()));
		triangles.insert(triangles.end(), newTriangles.begin(), newTriangles.end());

		illegal_triangles.clear();
		boundary.clear();
	}

	return true;
}
