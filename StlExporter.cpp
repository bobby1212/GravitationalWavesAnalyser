#include "StlExporter.h"

StlExporter::StlExporter(ErrorHandler * _errorHandler) : errorHandler(_errorHandler) { }

bool StlExporter::ExportStl(std::string file, std::vector<pTriangle> triangles, std::vector<Point>* points)
{
	std::ofstream out;

	out.open(file, std::ios::out | std::ios::binary | std::ios::trunc);

	if (!out.is_open())
	{
		errorHandler->DisplayError("Can't open output file!");
		return false;
	}

	//Write header
	char* header = new char[80]{ "Created by GravitationalWavesInspector" };
	out.write(header, 80);
	delete[]header;

	//Write number of triangles
	unsigned long int nmbTriangles = triangles.size();
	out.write((char*)&nmbTriangles, sizeof(int));

	float normal = 0.0f;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	unsigned short attr = 0;

	for (auto &i : triangles)
	{
		//Normals = 0.0 0.0 0.0
		out.write((char*)&normal, sizeof(float));
		out.write((char*)&normal, sizeof(float));
		out.write((char*)&normal, sizeof(float));

		x = (*points)[i->p1].x;
		y = (*points)[i->p1].y;
		z = (*points)[i->p1].z;
		out.write((char*)&x, sizeof(float));
		out.write((char*)&y, sizeof(float));
		out.write((char*)&z, sizeof(float));

		x = (*points)[i->p3].x;
		y = (*points)[i->p3].y;
		z = (*points)[i->p3].z;
		out.write((char*)&x, sizeof(float));
		out.write((char*)&y, sizeof(float));
		out.write((char*)&z, sizeof(float));

		x = (*points)[i->p2].x;
		y = (*points)[i->p2].y;
		z = (*points)[i->p2].z;
		out.write((char*)&x, sizeof(float));
		out.write((char*)&y, sizeof(float));
		out.write((char*)&z, sizeof(float));

		out.write((char*)&attr, sizeof(unsigned short));
	}

	return true;
}
