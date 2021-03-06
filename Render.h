#pragma once
#include "SharedDefines.h"
#include "poly2tri/poly2tri.h"
#include "ErrorHandler.h"
#include <time.h>
#include "Parser.h"
#include "Triangulation.h"
#include "DataStorage.h"

using namespace p2t;

class DataStorage;
class Parser;

class Render : public wxGLCanvas
{
public:
	Render(wxFrame* parent, DataStorage* _dataStorage, int* args, int height, int width, int positionX);
	~Render();
	void Init();
	void render(wxPaintEvent& evt);
	void activateRenderTriangles(bool);
	void activateRenderPoints(bool);

    //Option functions (Called by handlers)
	void setheightMultiplicator(float _heightMultiplicator) { heightMultiplicator = _heightMultiplicator; }
	void setDivisor(float _divisor) { divisor = _divisor; }
    void setMaxHeight(float _newHeight) { maxHeight = _newHeight; }
    void setMinHeight(float _newHeight) { minHeight = _newHeight; }
    void setMinRadius(float _radius) { minRadius = _radius; }
    void setMaxRadius(float _radius) { maxRadius = _radius; }
	void SetIteration(int iteration);

	//Input handlers
	void OnKeyDown(wxKeyEvent& event);

    //Private member get functions;
    float getMaxRadius() { return maxRadius; }
    float getMinRadius() { return minRadius; }

private:
	ErrorHandler* errorHandler;
	DataStorage* dataStorage;
	bool renderTriangles;
	bool renderPoints;
	int actualItr;

	DECLARE_EVENT_TABLE()

	float rotationSpeed;
	float translationSpeed;

	time_t deltaTime;

	float minX;
	float maxX;
	float minY;
	float maxY;
	float divisor;
	float heightMultiplicator;
	float maxZ;
	float minZ;
	float translationX;
	float translationY;
	float translationZ;
	float rotationX;
	float rotationY;
    float maxHeight;
    float minHeight;
    float minRadius;
    float maxRadius;

	wxGLContext* glContext;
    wxFrame* parent;

    //Members used by removeDuplicate System
    long long progressCounter;
    std::mutex progressCounterMutex;
    std::vector<Point> duplicatePoints;
    long long totalSize;

	float mapValue(float& value, float& oMin, float& oMax);
};
