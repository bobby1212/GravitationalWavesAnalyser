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
    Filename extension: .hm

    80 Byte: Header
    4 Byte int: Max. Radius

    //Matrix
    4 Byte int: x
    4 Byte int: y
    4 Byte float: z

    Matrix begin at x=0,y=0
    */

    char* header = new char[80]{ "Header" };
    output.write(header, 80);
    delete[]header;
    int temp = maxRadius;
    output.write((char*)&temp, sizeof(int));

    float tempFloat = 0.0f;
    double radius = 0.0f;

    int xRes = 100;
    int yRes = 100;

    for (auto i : *points)
    {
        int radius = distance(Point(), i);
        if (radius < maxRadius)
        {
            int xPos = (int)i.x;
            int yPos = (int)i.y;
            output.write((char*)&xPos, sizeof(int));
            output.write((char*)&yPos, sizeof(int));
            output.write((char*)&i.z, sizeof(float));
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
