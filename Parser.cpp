#include "Parser.h"

Parser::Parser(wxWindow* parent) :
	origin(Point(0, 0))
{
	errorHandler = new ErrorHandler(parent);
}

Parser::~Parser()
{
}

void Parser::openBin(std::string file)
{
    inputStreamBinary.open(file, std::ios::in | std::ios::binary);
    if (!inputStreamBinary.is_open())
        errorHandler->DisplayError("Binary input file couldn't be opend!");
    return;
}

void Parser::parseBinFile()
{
    char* header = new char[80];
    inputStreamBinary.read(header, 80);
    float tempFloat = 0.0f;
	int actualItr = 0;
	int nmbPoints = 0;
	byte* buffer = new byte;
	Point tempPoint = Point();

    while (inputStreamBinary.peek() != EOF)
    {
		inputStreamBinary.read((char*)&nmbPoints, sizeof(int));
		inputStreamBinary.read((char*)&actualItr, sizeof(int));

		int size = nmbPoints * 3 * 4;
		if (size)
		{
			buffer = new byte[size]; //Per point 3 values which are 4 bytes
			inputStreamBinary.read((char*)buffer, size);
		}

		for (int i = 0; nmbPoints != 0; nmbPoints--)
		{
			memcpy(&tempFloat, buffer + i * 12, 4);
			tempPoint.x = tempFloat;

			memcpy(&tempFloat, buffer + i * 12 + 4, 4);
			tempPoint.y = tempFloat;

			memcpy(&tempFloat, buffer + i * 12 + 8, 4);
			tempPoint.z = tempFloat;

			++i;

			if (tempFloat == 0.0f)
				continue;

			pointStore[actualItr].push_back(tempPoint);
		}

		delete buffer;
    }

	/*for (std::map<int, std::vector<Point>>::iterator itr = pointStore.begin(); itr != pointStore.end(); itr++)
		FindMinMax(itr->first);*/

    return;
}

void Parser::generatePoints(int count,int seed)
{
    min[0] = -10;
    max[0] = 10;
    base_generator_type generator(seed);
    boost::uniform_real<> uni_dist(min[0], max[0]);
    boost::variate_generator<base_generator_type&, boost::uniform_real<>> uni(generator, uni_dist);
    boost::uniform_real<> uni_dist_height(0, 2);
    boost::variate_generator<base_generator_type&, boost::uniform_real<>> uni_height(generator, uni_dist_height);
    
	pointStore.clear();

    while (pointStore[0].size() != count)
    {
        double x = uni();
        double y = uni();
        Point newPoint;
        newPoint.x = x;
        newPoint.y = y;
        newPoint.z = uni_height();
        while (std::find(pointStore[0].begin(), pointStore[0].end(),newPoint) != pointStore[0].end())
        {
            newPoint.x = uni();
            newPoint.y = uni();
        }
		pointStore[0].push_back(newPoint);
    }

	FindMinMax(0);
}

void Parser::FindMinMax(int iteration)
{
	min[iteration] = 100000.0f;
	max[iteration] = -1000000.0f;
	for (auto &i : pointStore[iteration])
	{
		if (i.x > max[iteration])
			max[iteration] = i.x;
		if (i.x < min[iteration])
			min[iteration] = i.x;
	}
}

