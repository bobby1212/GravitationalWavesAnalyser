#pragma once
#include "SharedDefines.h"
#include "GeometryDefines.h"
#include "ErrorHandler.h"
#include <time.h>

class Render : public wxGLCanvas
{
public:
	Render(wxFrame* parent, int* args, int height, int width, int positionX);
	~Render();
	void setPoints(std::vector<Point>*);
	void setTriangles(std::vector<pTriangle>*);
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
    void removeDuplicates(double radius, wxGauge* gauge);
    void setMinRadius(double _radius) { minRadius = _radius; }
    void setMaxRadius(double _radius) { maxRadius = _radius; }

    //Functions needed by the remove duplicates system
    void removeDuplicatesThread(double radius, std::vector<Point>* points, std::vector<Point>::iterator begin, std::vector<Point>::iterator end, std::vector<Point>* duplicatePoints);
    void updateRemoveDuplicatesGauge(wxGauge* gauge,bool& running);

	//Input handlers
	void OnKeyDown(wxKeyEvent& event);
private:
	ErrorHandler* errorHandler;
	std::vector<Point>* points;
	std::vector<pTriangle>* triangles;
	bool renderTriangles;
	bool renderPoints;

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

