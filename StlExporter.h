#include "SharedDefines.h"
#include "ErrorHandler.h"
#include "poly2tri.h"

using namespace p2t;

class StlExporter
{
public:
	StlExporter(ErrorHandler* errorHandler);
	~StlExporter() { };

	bool ExportStl(std::string file, std::list<Triangle*> triangles);

private:
	ErrorHandler* errorHandler;
};