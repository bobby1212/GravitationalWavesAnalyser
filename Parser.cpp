#include "Parser.h"

Parser::Parser(wxWindow* parent) :
	origin(Point(0, 0)),
	minX(10000.0f),
	maxX(-10000.0f),
	minY(10000.0f),
	maxY(-10000.0f),
	minZ(10000.0f),
	maxZ(-10000.0f)
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

    while (inputStreamBinary.peek() != EOF)
    {
		inputStreamBinary.read((char*)&nmbPoints, sizeof(int));
		inputStreamBinary.read((char*)&actualItr, sizeof(int));
		for (; nmbPoints != 0; nmbPoints--)
		{
			tempPoint = Point();
			tempFloat = 0.0f;
			inputStreamBinary.read((char*)&tempFloat, sizeof(float));
			tempPoint.x = tempFloat;

			tempFloat = 0.0f;
			inputStreamBinary.read((char*)&tempFloat, sizeof(float));
			tempPoint.y = tempFloat;

			tempFloat = 0.0f;
			inputStreamBinary.read((char*)&tempFloat, sizeof(float));
			tempPoint.z = tempFloat;

			pointStore[actualItr].push_back(tempPoint);
		}
    }
    return;
}

void Parser::generatePoints(int count,int seed)
{
    minX = -10;
    maxX = 10;
    minY = -10;
    maxY = 10;
    base_generator_type generator(seed);
    boost::uniform_real<> uni_dist(minX, maxX);
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
}

