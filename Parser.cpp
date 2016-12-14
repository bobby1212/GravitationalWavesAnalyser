#include "Parser.h"

Parser::Parser(wxWindow* parent) :
	origin(Point(0, 0)),
	continueLoop(false),
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

void Parser::openASCII(std::string file)
{
	fileStream.open(file, boost::iostreams::mapped_file::readonly);

	if (fileStream.is_open())
		return;
}

void Parser::openBin(std::string file)
{
    inputStreamBinary.open(file, std::ios::in | std::ios::binary);
    if (!inputStreamBinary.is_open())
        errorHandler->DisplayError("Binary input file couldn't be opend!");
    return;
}

void Parser::parseASCIIFile()
{
	if (!fileStream.is_open())
		return;

	int i = 0;

	auto f = fileStream.const_data();
	auto l = f + fileStream.size();

	boost::char_separator<char> sep(" ");
	boost::char_separator<char> sepLine("\n");

	streamBuffer.assign(f);
	boost::tokenizer<boost::char_separator<char>> tokLine(streamBuffer, sepLine);

	for (boost::tokenizer<boost::char_separator<char>>::iterator lineItr = tokLine.begin(); lineItr != tokLine.end(); lineItr++)
	{
		i++;
		if (i % 5 != 0)
			continue;

		buffer.assign(*lineItr);

		if (buffer.size() == 0 || buffer[0] == '#' || buffer[0] == '\r')
			continue;

		while (buffer[buffer.size() - 1] == '\r')
			buffer.pop_back();
		

		boost::tokenizer<boost::char_separator<char>> tok(buffer, sep);
		boost::tokenizer<boost::char_separator<char>>::iterator itr = tok.begin();

		int size = itr->size();

		try
		{
			tempPoint.x = boost::lexical_cast<double>(*itr);
			tempPoint.y = boost::lexical_cast<double>(*++itr);
			tempPoint.z = boost::lexical_cast<double>(*++itr);
		}
		catch (boost::bad_lexical_cast &e)
		{
			errorHandler->DisplayError("Something's wrong with the input file!");
			return;
		}

		tempPoint.x = floorf(tempPoint.x * 100 + 0.0) / 100;
		tempPoint.y = floorf(tempPoint.y * 100 + 0.0) / 100;
		tempPoint.z = floorf(tempPoint.z * 100 + 0.0) / 100;

		for (auto &i : points)
		{
			if (i == tempPoint)
				continueLoop = true;
		}

		if (continueLoop)
			continue;

		points.push_back(tempPoint);
	}


	/*double dist = distance(origin, tempPoint);
	if (dist > 150 || dist < 15)
		continue;

	i<f (tempPoint.x > maxX)
		maxX = tempPoint.x;
	if (tempPoint.x < minX)
		minX = tempPoint.x;
	if (tempPoint.y > maxY)
		maxY = tempPoint.y;
	if (tempPoint.y < minY)
		minY = tempPoint.y;
	if (tempPoint.z > maxZ)
		maxZ = tempPoint.z;
	if (tempPoint.z < minZ)
		minZ = tempPoint.z;
	*/

	maxX += 10;
	maxY += 10;
	minX -= 10;
	minY -= 10;
}

void Parser::parseBinFile()
{
    char* header = new char[80];
    inputStreamBinary.read(header, 80);
    float tempFloat = 0.0f;

    while (inputStreamBinary.peek() != EOF)
    {
        tempPoint = Point();
        tempFloat = 0.0f;
        inputStreamBinary.read((char*)&tempFloat, sizeof(float));
        tempPoint.x = tempFloat;

        tempFloat = 0.0f;
        inputStreamBinary.read((char*)&tempFloat, sizeof(float));
        tempPoint.z = tempFloat;

        tempFloat = 0.0f;
        inputStreamBinary.read((char*)&tempFloat, sizeof(float));
        tempPoint.y = tempFloat;
        

        points.push_back(tempPoint);
    }
    tempFloat = 0.0f;
    return;
}

void Parser::reducePoints(int nmbPoints)
{
	boost::minstd_rand generator(time(0));
	while (points.size() > nmbPoints)
	{
		boost::uniform_int<> uni_dist(0, points.size() - 1);
		boost::variate_generator<boost::minstd_rand&, boost::uniform_int<>> uni(generator, uni_dist);
		points.erase(points.begin() + uni());
	}
}

