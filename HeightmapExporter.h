#pragma once
#include "SharedDefines.h"
#include "poly2tri.h"

using namespace p2t;

class HeightmapExporter
{
public:
    HeightmapExporter(std::vector<Point>*);
    ~HeightmapExporter();

    bool exportHeightmap(std::string fileName, double maxHeight, double minHeight, double minRadius, double maxRadius);

private:
    std::vector<Point>* points;

    float highest;
    float lowest;

    float map(float value);
};

