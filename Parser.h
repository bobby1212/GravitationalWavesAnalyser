#pragma once
#include "SharedDefines.h"
#include "poly2tri/poly2tri.h"
#include "ErrorHandler.h"

using namespace p2t;

class Parser
{
public:
	Parser(wxWindow* parent);
	~Parser();
    void openBin(std::string file);
    void parseBinFile();
	double GetMin(int iteration) { return min[iteration]; }
	double GetMax(int iteration) { return max[iteration]; }
	std::map<int, std::vector<Point>>* GetPoints() { return &pointStore; }
	std::vector<Point>* GetPoints(int itr) { return &pointStore[itr]; }
    void SetPoints(int actualItr, std::vector<Point>* _points) 
	{
		pointStore[actualItr].clear();
		pointStore[actualItr] = *_points; 
	}
	int GetPointsCount(int itr) { return pointStore[itr].size(); }
    void generatePoints(int count, int seed);

	void FindMinMax(int iteration);
private:
	std::string file;
    std::ifstream inputStreamBinary;

	Point origin;
	double rangeMin, rangeMax;

	std::map<int, double> min, max;
	std::map<int,std::vector<Point>> pointStore;

	wxWindow* parent;
	ErrorHandler* errorHandler;

};

