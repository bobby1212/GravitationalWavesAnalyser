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
	void parseASCIIFile();
    void parseBinFile();
	void reducePoints(int nmbPoints);
	double GetMaxX() { return maxX; }
	double GetMaxY() { return maxY; }
	double GetMaxZ() { return maxZ; }
	double GetMinX() { return minX; }
	double GetMinY() { return minY; }
	double GetMinZ() { return minZ; }
	std::vector<Point>* GetPoints() { return &points; }
    void SetPoints(std::vector<Point>* _points) { points = *_points; }
    int GetPointsCount() { return points.size(); }
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

	std::vector<Point> points;

	wxWindow* parent;
	ErrorHandler* errorHandler;

};

