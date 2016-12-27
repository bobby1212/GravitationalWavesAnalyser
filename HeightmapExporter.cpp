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
    4 Byte float: Heightest point
    4 Byte float: Lowest point

    //Matrix
    4 Byte int: x
    4 Byte int: y
    4 Byte float: z

    Matrix begin at x=0,y=0
    */

    char* header = new char[80]{ "Header" };
    output.write(header, 80);
    delete[]header;
    maxRadius = 50;
    int temp = maxRadius;
    output.write((char*)&temp, sizeof(int));

    float tempFloat = 0.0f;
    double radius = 0.0f;

    int xRes = 100;
    int yRes = 100;
    float heighestPoint = -10000.0f;
    float lowestPoint = 10000.0f;

    std::vector<std::vector<float>> matrix;
    matrix.resize(xRes);
    for (auto &i : matrix)
    {
        i.resize(yRes,0);
    }

    for (auto i : *points)
    {
        int radius = distance(Point(), i);
        if (radius < maxRadius && radius > minRadius)
        {
            int xPos = (int)i.x + maxRadius;
            int yPos = (int)i.y + maxRadius;
            if (matrix[xPos][yPos] == 0)
            {
                matrix[xPos][yPos] = i.z;
                if (i.z > heighestPoint)
                    heighestPoint = i.z;
                if (i.z < lowestPoint)
                    lowestPoint = i.z;
            }
        }
    }

    output.write((char*)&heighestPoint, sizeof(float));
    output.write((char*)&lowestPoint, sizeof(float));

    for (int x = 0; x < xRes; x++)
    {
        for (int y = 0; y < yRes; y++)
        {
            output.write((char*)&x, sizeof(int));
            output.write((char*)&y, sizeof(int));
            output.write((char*)&matrix[x][y], sizeof(float));
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
