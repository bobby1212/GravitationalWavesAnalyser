#pragma once
#include "SharedDefines.h"
#include "ErrorHandler.h"
#include "BasicFrame.h"

using namespace p2t;

class BasicFrame;
class ErrorHandler;

class DataStorage
{
public:
	DataStorage() {};
	DataStorage(ErrorHandler* errorHandler, BasicFrame* parent);
	~DataStorage();

	std::map<int, std::vector<Point>>* GetPoints();
	std::vector<Point>* GetPoints(int iteration);
	std::map<int, std::list<Triangle*>> GetTriangles();
	std::list<Triangle*> GetTriangles(int iteration);
	void Reset(); //Resets the object and deletes all points and triangles
	void LoadPoints(std::string& filename); //Loads all points into pointsExt
	void AddTriangles(std::list<Triangle*>& triangles, int iteration);
	void CalcMinMax(int iteration);
	int GetIterationCount();
	int GetPointsCount(int iteration);
	float GetMin(int iteration);
	float GetMax(int iteration);
private:
	ErrorHandler* errorHandler;
	BasicFrame* parent;
	std::ifstream input;

	std::map<int, std::vector<Point>> points;
	std::map<int, std::list<std::pair<long long, long long>>> pointsExt; //First: Start byte in binary file ; Second: End byte in binary file
	std::map<int, std::list<Triangle*>> triangles;
	//TODO: Informativ naming
	std::map<int, float> min;
	std::map<int, float> max;

	bool LoadPoints(int iteration);
	bool OpenFilestream(std::string& filename);
};