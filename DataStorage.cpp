#include "DataStorage.h"

DataStorage::DataStorage(ErrorHandler* _errorHandler, BasicFrame* _parent) : errorHandler(_errorHandler), parent(_parent)
{
	points.clear();
	triangles.clear();
}

DataStorage::~DataStorage()
{
	Reset();
}

std::map<int, std::vector<Point>>* DataStorage::GetPoints()
{
	return &points;
}

std::vector<Point>* DataStorage::GetPoints(int iteration, bool single)
{
	if (points.find(iteration) == points.end())
	{
		parent->SetStatusText("Points for iteration " + std::to_string(iteration) + " don't exist. They are loading...");
		if (pointsExt.find(iteration) == pointsExt.end())
		{
			errorHandler->DisplayError("There are no points for this iteration!");
			return nullptr;
		}
		if (LoadPoints(iteration))
		{
			parent->SetStatusText("Points loaded.");
			return &points[iteration];
		}
		else
		{
			errorHandler->DisplayError("Error at loading points!");
			return nullptr;
		}
	}

	if (single)
	{
		PointBinaryTreeSort sort;	
		std::list<Point>* sortedPoints = sort.SortPointsXAxis(&points[iteration]);

		for (std::list<Point>::iterator itr = sortedPoints->begin(); itr != --sortedPoints->end();)
		{
			float x1 = itr->x;
			float y1 = itr->y;
			float x2 = (++itr)->x;
			float y2 = itr->y;

			if (x1 == x2 && y1 == y2)
			{
				itr = sortedPoints->erase(itr);
				--itr;
			}
		}

		points[iteration].clear();
		for (auto &i : *sortedPoints)
		{
			points[iteration].push_back(i);
		}

		//std::random_shuffle(points[iteration].begin(), points[iteration].end()); //Neccessery? I don't think so...
	}

	return &points[iteration];
}

std::map<int, std::list<Triangle*>> DataStorage::GetTriangles()
{
	return triangles;
}

std::list<Triangle*> DataStorage::GetTriangles(int iteration)
{
	if(triangles.find(iteration) == triangles.end())
		return std::list<Triangle*>();

	return triangles[iteration];
}

void DataStorage::Reset()
{
	points.clear();
	pointsExt.clear();

	for (auto &i : triangles)
	{
		for (auto &t : i.second)
			delete t;
		i.second.clear();
	}
	triangles.clear();
}

void DataStorage::LoadPoints(std::string& filename)
{
	if (!OpenFilestream(filename))
	{
		errorHandler->DisplayError("Error at opening input filestream!");
		return;
	}

	int actualItr = 0;
	int nmbPoints = 0;
	long long actualPosition;

	//Get size of file
	input.seekg(0, std::ios::end);
	long long size = input.tellg();

	//Pass header
	input.seekg(80, std::ios::beg);
	actualPosition = 80;

	while (true)
	{
		int check = input.tellg();
		input.read((char*)&nmbPoints, sizeof(int));
		input.read((char*)&actualItr, sizeof(int));

		if (actualItr > 10)
			break;

		if (actualItr < 0 || nmbPoints <= 0)
			continue;

		int pointsSize = nmbPoints * 3 * 4;
		
		pointsExt[actualItr].push_back(std::make_pair(input.tellg(), (long long)input.tellg() + pointsSize));

		actualPosition = (long long)input.tellg() + pointsSize;

		if (actualPosition >= size)
			break;

		input.seekg(actualPosition);
	}

	LoadPoints(0);
}

void DataStorage::AddTriangles(std::list<Triangle*>& _triangles, int iteration)
{
	triangles[iteration] = _triangles;
}

void DataStorage::CalcMinMax(int iteration)
{
	float tempMin = 100000.0f;
	float tempMax = -100000.0f;
	//TODO: Check if points are already loaded
	for (auto &i : points[iteration])
	{
		if (i.x > tempMax)
			tempMax = i.x;

		if (i.x < tempMin)
			tempMin = i.x;
	}

	min[iteration] = tempMin;
	max[iteration] = tempMax;
}

int DataStorage::GetIterationCount()
{
	return pointsExt.size();
}

int DataStorage::GetPointsCount(int iteration)
{
	return points[iteration].size();
}

float DataStorage::GetMin(int iteration)
{
	//TODO: Check if index exists
	return min[iteration];
}

float DataStorage::GetMax(int iteration)
{
	//TODO: Check if index exists
	return max[iteration];
}

bool DataStorage::LoadPoints(int iteration)
{
	if (pointsExt.find(iteration) == pointsExt.end())
	{
		errorHandler->DisplayError("No points exist for this iteration!");
		return false;
	}

	if (points.find(iteration) != points.end())
		points[iteration].clear();

	if (!input.is_open())
		return false;

	byte* buffer = new byte;
	Point tempPoint = Point();
	float tempFloat = 0.0f;

	for (auto &i : pointsExt[iteration])
	{
		long long startPosition = i.first;
		long long endPosition = i.second;
		input.seekg(startPosition, std::ios::beg);
		long long actualPosition = input.tellg();

		while (actualPosition != i.second)
		{
			input.read((char*)&tempFloat, sizeof(float));
			tempPoint.x = tempFloat;

			input.read((char*)&tempFloat, sizeof(float));
			tempPoint.y = tempFloat;

			input.read((char*)&tempFloat, sizeof(float));
			tempPoint.z = tempFloat;

			points[iteration].push_back(tempPoint);

			actualPosition = input.tellg();
		}
	}

	return true;
}

bool DataStorage::OpenFilestream(std::string & filename)
{
	input.open(filename, std::ios::in | std::ios::binary);
	
	if (input.is_open())
		return true;

	return false;
}


