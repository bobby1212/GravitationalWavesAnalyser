#include "HeightmapExporter.h"

HeightmapExporter::HeightmapExporter(std::vector<Point>* _points)
{
    if(_points)
        points = _points;
    highest = -100000.0f;
    lowest = 100000.0f;
}

HeightmapExporter::~HeightmapExporter()
{
}

bool HeightmapExporter::exportHeightmap(std::string fileName, double maxHeight,double minHeight,double minRadius,double maxRadius)
{
    if (!points)
        return false;

    if (points->size() == 0)
        return false;

    std::ofstream output;

    output.open(fileName.c_str(), std::ios::binary | std::ios::out | std::ios::trunc);
    if (!output.is_open())
        return false;

    lowest = minHeight;
    highest = maxHeight;

    /*
    File format:
    Filename extension: .bin

    80 Byte: Header

    //Vertex
    4 Byte float: x
    4 Byte float: y
    4 Byte float: z
    */

    char* header = new char[80]{ "Header" };
    output.write(header, 80);
    delete[]header;

    float tempFloat = 0.0f;
    double radius = 0.0f;

    for (auto i : *points)
    {
        radius = distance(Point(0, 0, 0), i);
        if (i.z < maxHeight && i.z > minHeight && radius < maxRadius && radius > minRadius)
        {
            tempFloat = i.x;
            output.write((char*)&tempFloat, sizeof(float));

            tempFloat = i.y;
            output.write((char*)&tempFloat, sizeof(float));

            tempFloat = map(i.z);
            output.write((char*)&tempFloat, sizeof(float));
        }
    }

    return true;
}

float HeightmapExporter::map(float value)
{
    //If your number X falls between A and B, and you would like Y to fall between C and D, you can apply the following linear transform:
    //Linear transformation: Y = (X-A)/(B-A) * (D-C) + C
    return (value-highest)/(lowest-value) * (0.0f-1.0f) + 0.0f;
}
