#include "BasicFrame.h"



BasicFrame::BasicFrame(const wxChar * title, int xpos, int ypos, int width, int height) : wxFrame((wxFrame*)NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
{
    CreateMenu();
    CreatePanels();
    statusBar = new wxStatusBar(this);
    SetStatusBar(statusBar);
    errorHandler = new ErrorHandler(this);
}

BasicFrame::~BasicFrame()
{
}

bool BasicFrame::CreatePanels()
{
    //Main Panel
    sizer = new wxBoxSizer(wxHORIZONTAL);
    panelOptions = new wxPanel(this, ID_PANEL_OPTIONS, wxPoint(0, 0), wxSize(width / 3, height));
    int args[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0 };
    panelRender = new Render(this, args, height, width / 3 * 2, width / 3);
    sizer->Add(panelOptions, 1, wxEXPAND);
    sizer->Add(panelRender, 1, wxEXPAND);

    //Options Panel
    optionsSizer = new wxBoxSizer(wxVERTICAL);

    heightDivisorSizer = new wxBoxSizer(wxHORIZONTAL);
    heightDivisorText = new wxStaticText(panelOptions, wxID_ANY, "Height Divisor:");
    heightDivisor = new wxTextCtrl(panelOptions, ID_OPTION_HEIGHTDIVISOR, "10000", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    divisorSizer = new wxBoxSizer(wxHORIZONTAL);
    divisorText = new wxStaticText(panelOptions, wxID_ANY, "Divisor:");
    divisor = new wxTextCtrl(panelOptions, ID_OPTION_DIVISOR, "362", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    nmbPointSizer = new wxBoxSizer(wxHORIZONTAL);
    nmbPointsText = new wxStaticText(panelOptions, wxID_ANY, "Number of points:");
    nmbPoints = new wxStaticBox(panelOptions, ID_INFO_NMB_POINTS, "0", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    maxHeightSizer = new wxBoxSizer(wxHORIZONTAL);
    maxHeightText = new wxStaticText(panelOptions, wxID_ANY, "Maximum height:");
    maxHeight = new wxTextCtrl(panelOptions, ID_OPTION_MAX_HEIGHT, "100000", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    minHeightSizer = new wxBoxSizer(wxHORIZONTAL);
    minHeightText = new wxStaticText(panelOptions, wxID_ANY, "Minimum height:");
    minHeight = new wxTextCtrl(panelOptions, ID_OPTION_MIN_HEIGHT, "-100000", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    removeDuplicatesSizer = new wxBoxSizer(wxHORIZONTAL);
    removeDuplicatesButton = new wxButton(panelOptions, ID_OPTION_REMOVE_DUPLICATES, "Remove duplicates");
    removeDuplicatesVariance = new wxTextCtrl(panelOptions, ID_OPTION_REMOVE_DUPLICATES_VARIANCE, "1.0", wxDefaultPosition, wxDefaultSize, wxTE_CENTER);

    triangulateSizer = new wxBoxSizer(wxHORIZONTAL);
    triangulateButton = new wxButton(panelOptions, ID_OPTION_TRIANGULATE, "Triangulate");
    triangulateGauge = new wxGauge(panelOptions, wxID_ANY, 100, wxDefaultPosition, wxSize(100, 25), wxGA_HORIZONTAL | wxGA_SMOOTH);

    generatePointsSizer = new wxBoxSizer(wxHORIZONTAL);
    generatePointsButton = new wxButton(panelOptions, ID_OPTION_GENERATE_POINTS, "Generate Points");
    generatePointsCount = new wxTextCtrl(panelOptions,ID_OPTION_GENERATE_POINTS_COUNT,"100", wxDefaultPosition, wxDefaultSize, wxTE_CENTER);

    radiusOptionSizer = new wxBoxSizer(wxHORIZONTAL);
    radiusOption = new wxStaticText(panelOptions, wxID_ANY, "Max. and min. radius");
    maxRadius = new wxTextCtrl(panelOptions,ID_OPTION_MAX_RADIUS, "10000", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);
    minRadius = new wxTextCtrl(panelOptions, ID_OPTION_MIN_RADIUS, "10000", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

	iterationSlider = new wxSlider(panelOptions, ID_OPTION_ITERATION, 0, 0, 1, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_MIN_MAX_LABELS | wxSL_AUTOTICKS | wxSL_VALUE_LABEL);

    //Set the sizers
    nmbPointSizer->Add(nmbPointsText, wxEXPAND);
    nmbPointSizer->Add(nmbPoints, wxALIGN_CENTER | wxEXPAND);

    divisorSizer->Add(divisorText,wxEXPAND);
    divisorSizer->Add(divisor,wxALIGN_CENTER | wxEXPAND);

    heightDivisorSizer->Add(heightDivisorText,wxEXPAND);
    heightDivisorSizer->Add(heightDivisor,wxALIGN_CENTER | wxEXPAND);

    maxHeightSizer->Add(maxHeightText, wxEXPAND);
    maxHeightSizer->Add(maxHeight, wxALIGN_CENTER | wxEXPAND);

    minHeightSizer->Add(minHeightText, wxEXPAND);
    minHeightSizer->Add(minHeight, wxALIGN_CENTER | wxEXPAND);

    removeDuplicatesSizer->Add(removeDuplicatesButton, wxEXPAND);
    removeDuplicatesSizer->Add(removeDuplicatesVariance, wxEXPAND);

    triangulateSizer->Add(triangulateButton, wxEXPAND);
    triangulateSizer->Add(triangulateGauge, wxEXPAND);

    generatePointsSizer->Add(generatePointsButton, wxEXPAND);
    generatePointsSizer->Add(generatePointsCount, wxEXPAND);

    radiusOptionSizer->Add(radiusOption, wxEXPAND);
    radiusOptionSizer->Add(maxRadius, wxEXPAND);
    radiusOptionSizer->Add(minRadius, wxEXPAND);

    optionsSizer->Add(divisorSizer,0, wxEXPAND);
    optionsSizer->Add(heightDivisorSizer,0, wxEXPAND);
    optionsSizer->Add(nmbPointSizer, 0, wxEXPAND);
    optionsSizer->Add(maxHeightSizer, 0, wxEXPAND);
    optionsSizer->Add(minHeightSizer, 0, wxEXPAND);
    optionsSizer->Add(removeDuplicatesSizer, 0, wxEXPAND);
    optionsSizer->Add(triangulateSizer, 0, wxEXPAND);
    optionsSizer->Add(generatePointsSizer, 0, wxEXPAND);
    optionsSizer->Add(radiusOptionSizer, 0, wxEXPAND);
	optionsSizer->Add(iterationSlider, 0, wxEXPAND);

    panelOptions->SetSizer(optionsSizer);
    panelOptions->SetAutoLayout(true);
    this->SetSizer(sizer);
    this->SetAutoLayout(true);
    this->Show(true);

    return true;
}

bool BasicFrame::CreateMenu()
{
    menuBar = new wxMenuBar();
    fileMenu = new wxMenu();
    editMenu = new wxMenu();
    exportMenu = new wxMenu();
    infoMenu = new wxMenu();

    fileMenu->Append(ID_FILE_OPEN, "Datei öffnen");
    fileMenu->Append(ID_FILE_EXIT, "Beenden");

    editMenu->Append(ID_EDIT_NOTHING, "Platzhalter");

    exportMenu->Append(ID_EXPORT_HEIGHTMAP, "Export heightmap");
	exportMenu->Append(ID_EXPORT_STL, "Export Stl");
	exportMenu->Append(ID_EXPORT_STL_ALL_ITERATIONS, "Export Stl with all iterations");

    infoMenu->Append(ID_INFO_ABOUT, "About");

    menuBar->Append(fileMenu,"Datei");
    menuBar->Append(editMenu,"Bearbeiten");
    menuBar->Append(exportMenu, "Export");
    menuBar->Append(infoMenu,"Info");
    SetMenuBar(menuBar);
    return true;
}

//Event handling
BEGIN_EVENT_TABLE(BasicFrame, wxFrame)
EVT_TEXT_ENTER(ID_OPTION_HEIGHTDIVISOR, BasicFrame::setHeightDivisor)
EVT_TEXT_ENTER(ID_OPTION_DIVISOR, BasicFrame::setDivisor)
EVT_TEXT_ENTER(ID_OPTION_MAX_HEIGHT, BasicFrame::setMaxHeight)
EVT_TEXT_ENTER(ID_OPTION_MIN_HEIGHT, BasicFrame::setMinHeight)
EVT_BUTTON(ID_OPTION_REMOVE_DUPLICATES, BasicFrame::removeDuplicates)
EVT_BUTTON(ID_OPTION_TRIANGULATE, BasicFrame::triangulatePoints)
EVT_BUTTON(ID_OPTION_GENERATE_POINTS, BasicFrame::generatePoints)
EVT_TEXT_ENTER(ID_OPTION_MIN_RADIUS, BasicFrame::setMinRadius)
EVT_TEXT_ENTER(ID_OPTION_MAX_RADIUS, BasicFrame::setMaxRadius)
EVT_SCROLL_CHANGED(BasicFrame::SetIteration)
EVT_MENU(ID_FILE_OPEN, BasicFrame::OnFileOpen)
EVT_MENU(ID_EXPORT_HEIGHTMAP, BasicFrame::OnExportHeightmap)
EVT_MENU(ID_EXPORT_STL, BasicFrame::OnExportStl)
EVT_MENU(ID_EXPORT_STL_ALL_ITERATIONS, BasicFrame::OnExportStlAllItr)

END_EVENT_TABLE()
//Render events
BEGIN_EVENT_TABLE(Render, wxGLCanvas)
EVT_PAINT(Render::render)
EVT_KEY_DOWN(Render::OnKeyDown)
END_EVENT_TABLE()


//TODO: Switch between .bin and .asc files dynamic
void BasicFrame::OnFileOpen(wxCommandEvent &event)
{
    wxFileDialog* dialog = new wxFileDialog(this, "Datei auswählen", "", "");
    if (dialog->ShowModal() == wxID_CANCEL)
        return;

    parser = new Parser(this);
    parser->openBin(std::string(dialog->GetPath()));
    parser->parseBinFile();
	UpdateIterationRange();
    panelRender->setPoints(parser->GetPoints());
    
    //Set nmb of point in text box
    nmbPoints->SetLabel(std::to_string(parser->GetPointsCount(0)));

    panelRender->activateRenderPoints(true);
    Refresh();
}

void BasicFrame::OnExportHeightmap(wxCommandEvent & event)
{
    if (parser)
    {
        HeightmapExporter exporter(parser->GetPoints(0));
        if (!exporter.exportHeightmap("out.hm", panelRender->GetMaxHeight(), panelRender->getMinHeight(), panelRender->getMinRadius(), panelRender->getMaxRadius()))
            errorHandler->DisplayError("Error at exporting file");
        else
            SetStatusText("Export successful");
    }
    else
        errorHandler->DisplayError("Couldn't export file because no points are loaded");
    return;
}

void BasicFrame::OnExportStl(wxCommandEvent & event)
{
	if (parser)
	{
		StlExporter exporter(errorHandler);
		if (exporter.ExportStl("out.stl", panelRender->GetTriangles(iterationSlider->GetValue())))
			SetStatusText("Export successful");
		else
			SetStatusText("Error at exporting file!");
	}
}

void BasicFrame::OnExportStlAllItr(wxCommandEvent & event)
{
	if (parser)
	{
		StlExporter exporter(errorHandler);
		for (int i = iterationSlider->GetMin(); i < iterationSlider->GetMax(); ++i)
		{
			exporter.ExportStl("wave" + std::to_string(i) + ".stl", panelRender->GetTriangles(i));
		}
	}
}

void BasicFrame::setHeightDivisor(wxCommandEvent &e)
{
    try
    {
        panelRender->setHeightDivisor(boost::lexical_cast<double>(e.GetString()));
        SetStatusText("Height Divisor changed");
        panelRender->Refresh();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
}

void BasicFrame::setDivisor(wxCommandEvent &e)
{
    try
    {
        SetStatusText("Divisor changed");
        panelRender->setDivisor(boost::lexical_cast<double>(e.GetString()));
        panelRender->Refresh();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
}

void BasicFrame::setMaxHeight(wxCommandEvent & e)
{
    try
    {
        SetStatusText("Max Height changed");
        panelRender->setMaxHeight(boost::lexical_cast<double>(e.GetString()));
        panelRender->Refresh();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
    catch (...)
    {
        errorHandler->DisplayError(ERROR_UNKNOWN);
    }
}

void BasicFrame::setMinHeight(wxCommandEvent & e)
{
    try
    {
        SetStatusText("Min Height changed");
        panelRender->setMinHeight(boost::lexical_cast<double>(e.GetString()));
        panelRender->Refresh();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
    catch (...)
    {
        errorHandler->DisplayError(ERROR_UNKNOWN);
    }
}

void BasicFrame::removeDuplicates(wxCommandEvent& event) 
{ 
    try
    {
        std::thread t1(&Render::removeDuplicates, panelRender, 0.5f, nmbPoints, parser, boost::lexical_cast<float>(removeDuplicatesVariance->GetValue()));
        t1.detach();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
    return;
}

void BasicFrame::triangulatePoints(wxCommandEvent & event)
{

    Triangulation tri(errorHandler);

	tri.Triangulate(parser->GetPoints(iterationSlider->GetValue()), parser->GetMinX(), parser->GetMaxX());

	panelRender->AddTriangulation(tri.GetTriangles(),iterationSlider->GetValue());
}

void BasicFrame::generatePoints(wxCommandEvent & event)
{
    try
    {
        parser = new Parser(this);

        parser->generatePoints(boost::lexical_cast<int>(generatePointsCount->GetValue()),clock());
		panelRender->Reset();
		panelRender->setPoints(parser->GetPoints());
        panelRender->calcValues();
        panelRender->Refresh();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
    catch (...)
    {
        errorHandler->DisplayError(ERROR_UNKNOWN);
    }
}

void BasicFrame::setMinRadius(wxCommandEvent & event)
{
    try
    {
        panelRender->setMinRadius(boost::lexical_cast<double>(event.GetString()));
        panelRender->calcValues();
        Refresh();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
}

void BasicFrame::setMaxRadius(wxCommandEvent & event)
{
    try
    {
        panelRender->setMaxRadius(boost::lexical_cast<double>(event.GetString()));
        panelRender->calcValues();
        Refresh();
    }
    catch (boost::bad_lexical_cast)
    {
        errorHandler->DisplayError(ERROR_NAN);
    }
}

void BasicFrame::SetIteration(wxScrollEvent & event)
{
	switch (event.GetId())
	{
	case ID_OPTION_ITERATION:
		panelRender->SetIteration(event.GetPosition());
		panelRender->Refresh();
		break;
	}
}

void BasicFrame::UpdateIterationRange()
{
	if (parser)
	{
		iterationSlider->SetMax(parser->GetPoints()->size());
	}
}

void BasicFrame::updateNmbPoints(int _nmbPoints)
{
    nmbPoints->SetLabelText(std::to_string(_nmbPoints));
}

