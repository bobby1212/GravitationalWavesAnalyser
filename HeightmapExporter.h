#pragma once
#include "SharedDefines.h"
#include "poly2tri/poly2tri.h"

using namespace p2t;

class HeightmapExporter
{
public:
    HeightmapExporter(std::vector<Point>*);
    ~HeightmapExporter();

    bool exportHeightmap(std::string fileName, float maxHeight, float minHeight, float minRadius, float maxRadius);

private:
    std::vector<Point>* points;

    float highest;
    float lowest;

    float map(float value);
};

