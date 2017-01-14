#include "Render.h"



Render::Render(wxFrame* _parent, DataStorage* _dataStorage, int* args, int height, int width, int positionX) :
    wxGLCanvas(_parent, wxID_ANY, args, wxPoint(positionX, 0), wxSize(width, height), wxFULL_REPAINT_ON_RESIZE) , dataStorage(_dataStorage)
{
    errorHandler = new ErrorHandler(this);
    parent = _parent;
    renderTriangles = true;
    renderPoints = true;
    glContext = new wxGLContext(this);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Init();
	actualItr = START_ITERATION;

    rotationSpeed = 1.15f;
    translationSpeed = 0.05f;

    deltaTime = 0;

    minX = 10000.0f;
    maxX = -10000.0f;
    minY = 10000.0f;
    maxY = -10000.0f;
    divisor = 700.0f;
    heightMultiplicator = 0.0001f;
    maxZ = -10000.0f;
    minZ = 10000.0f;
    translationX = 0.0f;
    translationY = 0.0f;
    translationZ = 0.0f;
    rotationX = 0.0f;
    rotationY = 0.0f;
    maxHeight = 0.25f;
    minHeight = -0.25f;
    minRadius = 12.0f;
    maxRadius = 600.0f;
}

Render::~Render()
{
    delete glContext;
}

void Render::Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glEnable(GL_TEXTURE_2D);   // textures
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(-1, -1, 2, 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //gluOrtho2D(topleft_x, bottomrigth_x, bottomrigth_y, topleft_y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Render::render(wxPaintEvent& evt)
{
	if (!dataStorage)
		return;

    deltaTime = clock() - deltaTime;

    wxGLCanvas::SetCurrent(*glContext);
    wxPaintDC(this);

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 10.0f);

    glRotated(rotationX, 1, 0, 0);
    glRotated(rotationY, 0, 0, 1);

    glTranslated(translationX, translationY, translationZ);

    glPointSize(2.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    if (renderPoints && dataStorage->GetPoints(actualItr))
    {
        if (dataStorage->GetPoints(actualItr)->size() == 1)
            errorHandler->DisplayError(ERROR_ONE_POINT);

        float radius = 0.0f;
        
        glBegin(GL_POINTS);
        for (auto &i : *dataStorage->GetPoints(actualItr))
        {
            /*
            Little problem here:
            The height of the gravitationwaves in the asc file is the z-Value but here it must be the y-Value
            */
            //Render conditions (Normally set in option panel)
            radius = distance(Point(0, 0, 0), i);
            if (i.z < maxHeight && i.z > minHeight && radius < maxRadius && radius > minRadius)
			{
				//Must be optimized
				float green = 0.0f;
				float blue = 0.0f;
				float red = 0.0f;
				if (i.z >= minHeight && i.z < (minHeight + maxHeight) / 2)
				{
					green = mapValue(i.z, minHeight, maxHeight);
					red = 1.0f - green;
					blue = 0.0f;
				}
				else if (i.z > (minHeight + maxHeight) / 2 && i.z <= maxHeight)
				{
					red = 0.0f;
					blue = mapValue(i.z, minHeight, maxHeight);
					green = 1.0f - blue;
				}
				else
				{
					red = 1.0f;
				}
				glColor3f(red, green, blue);
				glVertex3f(i.x / divisor, i.y / divisor, i.z * heightMultiplicator);
			}
        }
        glEnd();
    }
    if (dataStorage->GetTriangles(actualItr).size() > 0)
    {
        glLineWidth(2.5f);
        glColor3f(1.0f, 1.0f, 1.0f);
        for (auto &i : dataStorage->GetTriangles(actualItr))
        {
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_TRIANGLES);
            glVertex3f(i->GetPoint(0)->x / divisor, i->GetPoint(0)->y / divisor, i->GetPoint(0)->z  / heightMultiplicator);
            glVertex3f(i->GetPoint(1)->x / divisor, i->GetPoint(1)->y / divisor, i->GetPoint(1)->z  / heightMultiplicator);
            glVertex3f(i->GetPoint(2)->x / divisor, i->GetPoint(2)->y / divisor, i->GetPoint(2)->z  / heightMultiplicator);
            glEnd();
            glColor3f(0.0f, 1.0f, 0.0f);
            glBegin(GL_LINES);
            glVertex3f(i->GetPoint(0)->x / divisor, i->GetPoint(0)->y / divisor, i->GetPoint(0)->z  / heightMultiplicator);
            glVertex3f(i->GetPoint(1)->x / divisor, i->GetPoint(1)->y / divisor, i->GetPoint(1)->z  / heightMultiplicator);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(i->GetPoint(1)->x / divisor, i->GetPoint(1)->y / divisor, i->GetPoint(1)->z  / heightMultiplicator);
            glVertex3f(i->GetPoint(2)->x / divisor, i->GetPoint(2)->y / divisor, i->GetPoint(2)->z  / heightMultiplicator);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(i->GetPoint(2)->x / divisor, i->GetPoint(2)->y / divisor, i->GetPoint(2)->z  / heightMultiplicator);
            glVertex3f(i->GetPoint(0)->x / divisor, i->GetPoint(0)->y / divisor, i->GetPoint(0)->z  / heightMultiplicator);
            glEnd();
        }
    }

    glFlush();
    SwapBuffers();
}

void Render::activateRenderTriangles(bool _renderTriangles)
{
    renderTriangles = _renderTriangles;
}

void Render::activateRenderPoints(bool _renderPoints)
{
    renderPoints = _renderPoints;
}

void Render::OnKeyDown(wxKeyEvent & event)
{
    parent->SetStatusText(event.GetUnicodeKey());
    switch (event.GetUnicodeKey())
    {
    case 'D':
        translationX += translationSpeed;
        break;
    case 'A':
        translationX -= translationSpeed;
        break;
    case 'W':
        translationY += translationSpeed;
        break;
    case 'S':
        translationY -= translationSpeed;
        break;
    case 'Q':
        rotationX -= rotationSpeed;
        break;
    case 'E':
        rotationX += rotationSpeed;
        break;
    }
    Refresh();
}

float Render::mapValue(float & value, float & oMin, float & oMax)
{
	float oSpan = oMax - oMin;
	float dSpan = 1.0f;

	float valueScaled = (value - oMin) / oSpan;

	return 0.0f + (valueScaled * dSpan);
}

void Render::SetIteration(int iteration)
{
	actualItr = iteration;
	dataStorage->GetPoints(iteration);
}

/*void Render::removeDuplicates(float radius, wxStaticBox* nmbPointsText,Parser* parser,float variance)
{
    if (!dataStorage->GetPoints(actualItr))
        return;
    if (dataStorage->GetPoints(actualItr)->size() == 0)
    {
        errorHandler->DisplayError("There are no points to remove!");
        return;
    }

    //First sort the points
    //x Axis:
    PointBinaryTreeSort sort;
    std::list<Point*> sortedPoints = sort.SortPointsXAxis(dataStorage->GetPoints(actualItr));
    std::vector<Point> singlePoints;

    int size = sortedPoints.size();

    for (std::list<Point*>::iterator itr = sortedPoints.begin();itr != --sortedPoints.end();)
    {   

        float firstValueX = (*itr)->x;
        float firstValueY = (*itr)->y;
        float secondValueX = (*++itr)->x;
        float secondValueY = (*itr)->y;

        if (abs(firstValueX - secondValueX) < variance && abs(firstValueY - secondValueY) < variance)
        {
            itr = sortedPoints.erase(itr);
            --itr;
        }
    }

    
    size = sortedPoints.size();

    for (auto &i : sortedPoints)
        singlePoints.push_back(*i);

    parent->SetStatusText("Removed duplicated points!");
    nmbPointsText->SetLabel(std::to_string(singlePoints.size()));

    //Refresh();
    dataStorage->SetPoints(actualItr,&singlePoints);

    return;
}*/
