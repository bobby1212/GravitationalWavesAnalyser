#include "StlExporter.h"

StlExporter::StlExporter(ErrorHandler * _errorHandler) : errorHandler(_errorHandler) { }

bool StlExporter::ExportStl(std::string file, std::list<Triangle*> triangles)
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

		x = i->GetPoint(0)->x;
		y = i->GetPoint(0)->y;
		z = i->GetPoint(0)->z;
		out.write((char*)&x, sizeof(float));
		out.write((char*)&y, sizeof(float));
		out.write((char*)&z, sizeof(float));

		x = i->GetPoint(2)->x;
		y = i->GetPoint(2)->y;
		z = i->GetPoint(2)->z;
		out.write((char*)&x, sizeof(float));
		out.write((char*)&y, sizeof(float));
		out.write((char*)&z, sizeof(float));

		x = i->GetPoint(1)->x;
		y = i->GetPoint(1)->y;
		z = i->GetPoint(1)->z;
		out.write((char*)&x, sizeof(float));
		out.write((char*)&y, sizeof(float));
		out.write((char*)&z, sizeof(float));

		out.write((char*)&attr, sizeof(unsigned short));
	}

	return true;
}
