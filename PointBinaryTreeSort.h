#pragma once
#include "SharedDefines.h"
#include "GeometryDefines.h"

struct Tree
{
    Point* point;
    Tree* left;
    Tree* right;

    Tree()
    {
        point = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

class PointBinaryTreeSort
{
public:
    PointBinaryTreeSort();
    ~PointBinaryTreeSort();

    std::list<Point*> sortedPoints;

    std::list<Point*> SortPointsXAxis(std::vector<Point>* points);

    void insert(Tree** root, std::vector<Point>::iterator newValue);
    void addToList(Tree* node);
};

