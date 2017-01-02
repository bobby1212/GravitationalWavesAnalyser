#include "Triangulation.h"



Triangulation::Triangulation(ErrorHandler* _errorHandler) : errorHandler(_errorHandler)
{
	timeBegin = clock();
	triangleMatrix.resize(4);
	for (int i : {0, 1, 2, 3})
		triangleMatrix[i].resize(4);
}

Triangulation::~Triangulation()
{
}

void Triangulation::SetPoints(Parser* parser)
{
    ppoints = parser->GetPoints(0);
	points.clear();
    points.push_back(Point(parser->GetMinX(), parser->GetMinY()));
    points.push_back(Point(parser->GetMaxX(), parser->GetMinY()));
    points.push_back(Point(parser->GetMaxX(), parser->GetMaxY()));
    points.push_back(Point(parser->GetMinX(), parser->GetMaxY()));
	triangles.clear();
    return;
}

void Triangulation::Triangulate(wxGauge* progressGauge,Render* render)
{
    //Make initial triangles
    auto T1 = std::make_shared<Triangle>(3, 1, 0);
    auto T2 = std::make_shared<Triangle>(3, 2, 1);
    //cout << "Initial triangles made" << endl;

    //cout << "Points: " << endl;
    //for (int i = 0; i < points.size(); i++)
        //cout << "Point Nr. " << i << " : " << points[i] << endl;

    //Add the neighbours
    T1->n1 = T2;
    T2->n3 = T1;
    //cout << "Neighbours added" << endl;

    triangles.push_back(T1);
    triangles.push_back(T2);

	progressGauge->SetRange(ppoints->size());
	int actualProgress = 0;

    //cout << "Progress: " << endl;
    for (auto &point : *ppoints)
	{
        //++i;
        //cerr << "\r" << (float)i / (float)ppoints->size() * 100.0f << "%";
        points.push_back(point);
        //cout << "New Point: " << point << endl;

        //Check wich triangles are illegal
        for (auto &T : triangles)
        {

            if (CircumcircleContains(T, point, &points, &triangleMatrix))
                illegal_triangles.push_back(T);
        }

        //cout << "Nmb illegal triangles: " << illegal_triangles.size() << endl;
        if (illegal_triangles.size() == 0)
        {
            //cerr << "No illegal triangles! Point: " << point << endl;
			errorHandler->DisplayError(ERROR_TRIANGULATION_NO_ILLEGAL_TRIANGLE);
            return;
        }
        //cout << "Illegal triangles:" << endl;
        //for (auto &i : illegal_triangles)
            //i->log(&points);
        //cout << endl;

        //Get Boundary
        auto T = illegal_triangles[0];
        int pos = 0;
        while (true)
        {
            //cout << "Number of boundaries: " << boundary.size() << endl;
            //cout << "Actual triangle: " << endl;
            //T->log(&points);
            //cout << endl;
            if (boundary.size() > 1)
                if (boundary.front() == boundary.back())
                {
                    break;
                }

            //cout << "Actual edge: " << endl;
            //Check whether an other triangle contains the same edge
            switch (pos)
            {
            case 0:
                //cout << "p1: " << points[T->p1] << " p2: " << points[T->p2] << endl;
                if (std::find(illegal_triangles.begin(),illegal_triangles.end(),T->n1) != illegal_triangles.end())
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
                    //cout << "New boundary: ";
                    //edge.log(&points);
                    if (edge.triangle)
                    {
                        //cout << "Triangle: ";
                        //edge.triangle->log(&points);
                    }
                    //cout << endl;
                    boundary.push_back(edge);
                    pos++;
                }
                break;

            case 1:
                //cout << "p1: " << points[T->p2] << " p2: " << points[T->p3] << endl;
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
                    //cout << "New boundary: ";
                    //edge.log(&points);
                    if (edge.triangle)
                    {
                        //cout << "Triangle: ";
                        //edge.triangle->log(&points);
                    }
                    //cout << endl;
                    boundary.push_back(edge);
                    pos++;
                }
                break;

            case 2:
                //cout << "p1: " << points[T->p3] << " p2: " << points[T->p1] << endl;
                //if (T->n3)
                    //T->n3->log(&points, true);
                //else
                    //cout << "n3 is empty!" << endl;
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
                    //cout << "New boundary: ";
                    //edge.log(&points);
                    if (edge.triangle)
                    {
                        //cout << "Triangle: ";
                        //edge.triangle->log(&points);
                    }
                    //cout << endl;
                    boundary.push_back(edge);
                    pos = 0;
                }
                break;
            }

        }
        boundary.pop_back();
        //End of 'Get Boundary'
        //cout << "Boundaries:" << endl;
        //for (auto &i : boundary)
            //i.log(&points);
        //cout << endl;


        //Erase illegal triangles out of the exsisting triangles
        for (auto &T : illegal_triangles)
            boost::remove_erase(triangles, T);
        //cout << "Illegal triangles removed" << endl;
        //cout << "Sizeof triangles: " << triangles->size() << endl;
        //cout << "Remaining triangles: " << endl;
        //for (auto &i : *triangles)
            //i->log(&points);

        //Fill up the hole
        std::vector<pTriangle> newTriangles;
        for (auto &edge : boundary)
        {
            int a = edge.p1;
            int b = edge.p2;

            //cout << "Actual edge: " << endl << "p1: " << points[a] << " p2: " << points[b] << endl;

            auto T = std::make_shared<Triangle>(points.size() - 1, a, b);

            if ((points[T->p1].x == points[T->p2].x && points[T->p1].x == points[T->p3].x) || (points[T->p1].y == points[T->p2].y && points[T->p1].y == points[T->p3].y))
            {
                //cerr << "Found!" << endl;
                //cerr << points[T->p1] << " " << points[T->p2] << " " << points[T->p3] << endl;
                //cout << "Found!" << endl;
                //cout << points[T->p1] << " " << points[T->p2] << " " << points[T->p3] << endl;
				errorHandler->DisplayError(ERROR_TRIANGULATION_EQUAL_POINTS);
				return;
            }

            if (!edge.triangle)
            {
                edge.triangle = nullptr;
                //cout << "Triangle on edge NULL" << endl;
            }
            else
            {
                //cout << "Triangle: ";
                //edge.triangle->log(&points);
                if (std::find(triangles.begin(),triangles.end(),edge.triangle) != triangles.end())
                {
                    //cout << "Triangle on edge!" << endl;
                }
                else
                {
                    //cout << "Edge triangle not found in triangles!" << endl;
                    edge.triangle = nullptr;
                }
            }
            T->n2 = edge.triangle;

            if (T->n2)
            {
                T->n2->setEdge(&edge, T, &points);
            }
            //else
                //cout << "No neighbour!" << endl;

            //cout << "New triangle: ";
            //T->log(&points, true);
            //cout << endl;

            newTriangles.push_back(T);
        }
        //cout << "Hole filled up" << endl;

        //Connect the new triangles
        int S = newTriangles.size();
        for (int i = 0; i < newTriangles.size(); i++)
        {
            newTriangles[i]->n1 = newTriangles[((i - 1) % S + S) % S]; //(i-1) % S should work equally
            newTriangles[i]->n3 = newTriangles[(i + 1) % S];
        }
        //cout << "Connections added" << endl;
        //cout << "New triangles with connections: " << endl;
        for (auto &i : newTriangles)
        {
            //i->log(&points, true);
            double orientation = 0.5*((points)[i->p1].x * (points)[i->p2].y - (points)[i->p2].x * (points)[i->p1].y + (points)[i->p2].x * (points)[i->p3].y - (points)[i->p3].x * (points)[i->p2].y + (points)[i->p3].x * (points)[i->p1].y - (points)[i->p1].x * (points)[i->p3].y);
            //cout << "Orientation: " << orientation << endl;
        }

        //cout << "Existing triangles with connections: " << endl;
        //for (auto &i : *triangles)
            //i->log(&points, true);

        //Add the new triangles
        triangles.reserve(triangles.size() + distance(newTriangles.begin(), newTriangles.end()));//Why not + newTriangles.size() ??? Let's try
        triangles.insert(triangles.end(), newTriangles.begin(), newTriangles.end()); //Why first reserve???

        illegal_triangles.clear();
        boundary.clear();

		progressGauge->SetValue(++actualProgress);
    }

	ppoints->insert(ppoints->begin(), points[3]);
	ppoints->insert(ppoints->begin(), points[2]);
	ppoints->insert(ppoints->begin(), points[1]);
	ppoints->insert(ppoints->begin(), points[0]);

	render->setTriangles(triangles);
	render->Refresh();

    return;
}
