#pragma once
#include "SharedDefines.h"
#include "GeometryDefines.h"
#include "ErrorHandler.h"

class Parser
{
public:
	Parser(wxWindow* parent);
	~Parser();
	void openASCII(std::string file);
    void openBin(std::string file);
    void parseBinFile();
	double GetMaxX() { return maxX; }
	double GetMaxY() { return maxY; }
	double GetMaxZ() { return maxZ; }
	double GetMinX() { return minX; }
	double GetMinY() { return minY; }
	double GetMinZ() { return minZ; }
	std::map<int, std::vector<Point>>* GetPoints() { return &pointStore; }
	std::vector<Point>* GetPoints(int itr) { return &pointStore[itr]; }
    void SetPoints(int actualItr, std::vector<Point>* _points) { pointStore[actualItr] = *_points; }
	int GetPointsCount(int itr) { return pointStore[itr].size(); }
    void generatePoints(int count, int seed);
private:
	std::string file;
	boost::iostreams::mapped_file fileStream;
    std::ifstream inputStreamBinary;
	std::string streamBuffer;
	std::string buffer;
	bool continueLoop;

	Point origin;
	Point tempPoint;
	double minX, maxX, minY, maxY, minZ, maxZ;
	double rangeMin, rangeMax;

	std::map<int,std::vector<Point>> pointStore;

	wxWindow* parent;
	ErrorHandler* errorHandler;

};

