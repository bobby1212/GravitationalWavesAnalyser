#include "Render.h"



Render::Render(wxFrame* _parent, int* args, int height, int width, int positionX) :
    wxGLCanvas(_parent, wxID_ANY, args, wxPoint(positionX, 0), wxSize(width, height), wxFULL_REPAINT_ON_RESIZE)
{
    errorHandler = new ErrorHandler(this);
    parent = _parent;
    renderTriangles = true;
    renderPoints = true;
    glContext = new wxGLContext(this);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Init();
    //basicParent = _basicParent;

    rotationSpeed = 1.05f;
    translationSpeed = 0.05f;

    deltaTime = 0;

    minX = 10000.0f;
    maxX = -10000.0f;
    minY = 10000.0f;
    maxY = -10000.0f;
    divisor = 362;
    heightDivisor = 1000000;
    maxZ = -10000.0f;
    minZ = 10000.0f;
    offsetX = 0.0f;
    offsetY = 0.0f;
    offsetZ = 0.0f;
    translationX = 0.0f;
    translationY = 0.0f;
    translationZ = 0.0f;
    rotationX = 0.0f;
    rotationY = 0.0f;
    maxHeight = 100000.0f;
    minHeight = -10000.0f;
    minRadius = 0.0f;
    maxRadius = 10000.0f;
}

Render::~Render()
{
    delete glContext;
}

void Render::setPoints(std::vector<Point>* _points)
{
    points = _points;
    calcValues();
}

void Render::setTriangles(std::vector<pTriangle>* _triangles)
{
    triangles = _triangles;
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
    if (renderPoints && points)
    {
        if (points->size() == 1)
            errorHandler->DisplayError(ERROR_ONE_POINT);

        float radius = 0.0f;
        
        glBegin(GL_POINTS);
        for (auto &i : *points)
        {
            /*
            Little problem here:
            The height of the gravitationwaves in the asc file ist the z-Value but here it must be the y-Value
            */
            //Render conditions (Normally set in option panel)
            radius = distance(Point(0, 0, 0), i);
            if (i.z-offsetZ < maxHeight && i.z-offsetZ > minHeight && radius < maxRadius && radius > minRadius)
                glVertex3f((i.x + offsetX) / divisor, (i.y + offsetY) / divisor, (i.z - offsetZ) / heightDivisor);
        }
        glEnd();
    }
    /*if (renderTriangles)
    {
        glLineWidth(2.5f);
        glColor3f(1.0f, 1.0f, 1.0f);
        Point normal;
        for (auto &i : *triangles)
        {
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_TRIANGLES);
            glVertex3f(((*points)[i->p1].x + offsetX) / divisor, ((*points)[i->p1].y + offsetY) / divisor, ((*points)[i->p1].z - offsetZ) / heightDivisor);
            glVertex3f(((*points)[i->p2].x + offsetX) / divisor, ((*points)[i->p2].y + offsetY) / divisor, ((*points)[i->p2].z - offsetZ) / heightDivisor);
            glVertex3f(((*points)[i->p3].x + offsetX) / divisor, ((*points)[i->p3].y + offsetY) / divisor, ((*points)[i->p3].z - offsetZ) / heightDivisor);
            glEnd();
            glColor3f(0.0f, 1.0f, 0.0f);
            glBegin(GL_LINES);
            glVertex3f(((*points)[i->p1].x + offsetX) / divisor, ((*points)[i->p1].y + offsetY) / divisor, ((*points)[i->p1].z - offsetZ) / heightDivisor);
            glVertex3f(((*points)[i->p2].x + offsetX) / divisor, ((*points)[i->p2].y + offsetY) / divisor, ((*points)[i->p2].z - offsetZ) / heightDivisor);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(((*points)[i->p2].x + offsetX) / divisor, ((*points)[i->p2].y + offsetY) / divisor, ((*points)[i->p2].z - offsetZ) / heightDivisor);
            glVertex3f(((*points)[i->p3].x + offsetX) / divisor, ((*points)[i->p3].y + offsetY) / divisor, ((*points)[i->p3].z - offsetZ) / heightDivisor);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(((*points)[i->p3].x + offsetX) / divisor, ((*points)[i->p3].y + offsetY) / divisor, ((*points)[i->p3].z - offsetZ) / heightDivisor);
            glVertex3f(((*points)[i->p1].x + offsetX) / divisor, ((*points)[i->p1].y + offsetY) / divisor, ((*points)[i->p1].z - offsetZ) / heightDivisor);
            glEnd();
        }
    }*/

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

void Render::calcValues()
{
    float radius = 0.0f;
    for (auto &i : *points)
    {
        radius = distance(Point(0, 0, 0), i);
        if (i.z - offsetZ < maxHeight && i.z - offsetZ > minHeight && radius < maxRadius && radius > minRadius)
        {
            if (i.x > maxX)
                maxX = i.x;
            if (i.x < minX)
                minX = i.x;
            if (i.y > maxY)
                maxY = i.y;
            if (i.y < minY)
                minY = i.y;
            if (i.z > maxZ)
                maxZ = i.z;
            if (i.z < minZ)
                minZ = i.z;
        }
    }

    divisor = fabs(minX - maxX);
    heightDivisor = fabs(minZ - maxZ);
    parent->SetStatusText("New render values calculated! maxX: " + std::to_string(maxX) + " minX: " + std::to_string(minX) + " divisor: " + std::to_string(divisor) + " heightDivisor: " + std::to_string(heightDivisor));
    //TODO: Update option panel values
}

void Render::removeDuplicates(double radius, wxStaticBox* nmbPointsText,Parser* parser,float variance)
{
    if (!points)
        return;
    if (points->size() == 0)
    {
        errorHandler->DisplayError("There are no points to remove!");
        return;
    }

    //First sort the points
    //x Axis:
    PointBinaryTreeSort sort;
    std::list<Point*> sortedPoints = sort.SortPointsXAxis(points);
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
    parser->SetPoints(&singlePoints);

    return;
}
