#include "SharedDefines.h"
#include "ErrorHandler.h"
#include "GeometryDefines.h"

class StlExporter
{
public:
	StlExporter(ErrorHandler* errorHandler);
	~StlExporter() { };

	bool ExportStl(std::string file, std::vector<pTriangle> triangles, std::vector<Point>* points);

private:
	ErrorHandler* errorHandler;
};