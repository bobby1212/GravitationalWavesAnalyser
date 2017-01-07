#pragma once
#include "SharedDefines.h"
#include "poly2tri.h"
#include "ErrorHandler.h"
#include <time.h>
#include "PointBinaryTreeSort.h"
#include "Parser.h"

using namespace p2t;

class Render : public wxGLCanvas
{
public:
	Render(wxFrame* parent, int* args, int height, int width, int positionX);
	~Render();
	void Reset();
	void setPoints(std::map<int, std::vector<Point>>*);
	void AddTriangulation(std::list<Triangle*> triangles, int iteration);
	void Init();
	void render(wxPaintEvent& evt);
	void activateRenderTriangles(bool);
	void activateRenderPoints(bool);
    //Recalculates the render values based on rendered points (Called from setPoints and from handler(Not implemented yet))
    void calcValues();

    //Option functions (Called by handlers)
	void setHeightDivisor(double _heightDivisor) { heightDivisor = _heightDivisor; }
	void setDivisor(double _divisor) { divisor = _divisor; }
    void setMaxHeight(double _newHeight) { maxHeight = _newHeight; }
    void setMinHeight(double _newHeight) { minHeight = _newHeight; }
    void removeDuplicates(double radius,wxStaticBox* nmbPointsText, Parser* parser, float variance);
    void setMinRadius(double _radius) { minRadius = _radius; }
    void setMaxRadius(double _radius) { maxRadius = _radius; }
	void SetIteration(int itr) { actualItr = itr; }

	//Input handlers
	void OnKeyDown(wxKeyEvent& event);

    //Private member get functions;
    double getMaxHeight() { return maxHeight; }
    double getMinHeight() { return minHeight; }
    double getMaxRadius() { return maxRadius; }
    double getMinRadius() { return minRadius; }
	std::map<int, std::list<Triangle*>>& GetTriangles() { return trianglesStore; }
	std::list<Triangle*>& GetTriangles(int iteration) { return trianglesStore[iteration]; }

private:
	ErrorHandler* errorHandler;
	std::map<int, std::vector<Point>>* points;
	std::map<int, std::list<Triangle*>> trianglesStore;
	bool renderTriangles;
	bool renderPoints;
	int actualItr;

	DECLARE_EVENT_TABLE()

	double rotationSpeed;
	double translationSpeed;

	time_t deltaTime;

	double minX;
	double maxX;
	double minY;
	double maxY;
	double divisor;
	double heightDivisor;
	double maxZ;
	double minZ;
	double offsetX;
	double offsetY;
	double offsetZ;
	double translationX;
	double translationY;
	double translationZ;
	double rotationX;
	double rotationY;
    double maxHeight;
    double minHeight;
    double minRadius;
    double maxRadius;

	wxGLContext* glContext;
    wxFrame* parent;

    //Members used by removeDuplicate System
    long long progressCounter;
    std::mutex progressCounterMutex;
    std::vector<Point> duplicatePoints;
    long long totalSize;
};
