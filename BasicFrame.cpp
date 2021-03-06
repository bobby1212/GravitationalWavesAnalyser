#include "BasicFrame.h"



BasicFrame::BasicFrame(const wxChar * title, int xpos, int ypos, int width, int height) : wxFrame((wxFrame*)NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
{
	errorHandler = new ErrorHandler(this);
	dataStorage = new DataStorage(errorHandler, this);
    CreateMenu();
    CreatePanels();
    statusBar = new wxStatusBar(this);
    SetStatusBar(statusBar);

	SetStatusText("Gr��e p2t::Point: " + std::to_string(sizeof(Point)));
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
    panelRender = new Render(this, dataStorage, args, height, width / 3 * 2, width / 3);
    sizer->Add(panelOptions, 1, wxEXPAND);
    sizer->Add(panelRender, 1, wxEXPAND);

    //Options Panel
    optionsSizer = new wxBoxSizer(wxVERTICAL);

    heightMultiplicatorSizer = new wxBoxSizer(wxHORIZONTAL);
    heightMultiplicatorText = new wxStaticText(panelOptions, wxID_ANY, "Height Divisor:");
    heightMultiplicator = new wxTextCtrl(panelOptions, ID_OPTION_heightMultiplicator, "10000", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    divisorSizer = new wxBoxSizer(wxHORIZONTAL);
    divisorText = new wxStaticText(panelOptions, wxID_ANY, "Divisor:");
    divisor = new wxTextCtrl(panelOptions, ID_OPTION_DIVISOR, "700", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    nmbPointSizer = new wxBoxSizer(wxHORIZONTAL);
    nmbPointsText = new wxStaticText(panelOptions, wxID_ANY, "Number of points:");
    nmbPoints = new wxStaticBox(panelOptions, ID_INFO_NMB_POINTS, "0", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    maxHeightSizer = new wxBoxSizer(wxHORIZONTAL);
    maxHeightText = new wxStaticText(panelOptions, wxID_ANY, "Maximum height:");
    maxHeight = new wxTextCtrl(panelOptions, ID_OPTION_MAX_HEIGHT, "0.25", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

    minHeightSizer = new wxBoxSizer(wxHORIZONTAL);
    minHeightText = new wxStaticText(panelOptions, wxID_ANY, "Minimum height:");
    minHeight = new wxTextCtrl(panelOptions, ID_OPTION_MIN_HEIGHT, "-0.25", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);
    removeDuplicatesSizer = new wxBoxSizer(wxHORIZONTAL);
    removeDuplicatesButton = new wxButton(panelOptions, ID_OPTION_REMOVE_DUPLICATES, "Remove duplicates");
    removeDuplicatesVariance = new wxTextCtrl(panelOptions, ID_OPTION_REMOVE_DUPLICATES_VARIANCE, "1.0", wxDefaultPosition, wxDefaultSize, wxTE_CENTER);

    triangulateSizer = new wxBoxSizer(wxHORIZONTAL);
    triangulateButton = new wxButton(panelOptions, ID_OPTION_TRIANGULATE, "Triangulate");
    triangulateGauge = new wxGauge(panelOptions, wxID_ANY, 100, wxDefaultPosition, wxSize(100, 25), wxGA_HORIZONTAL | wxGA_SMOOTH);

    radiusOptionSizer = new wxBoxSizer(wxHORIZONTAL);
    radiusOption = new wxStaticText(panelOptions, wxID_ANY, "Max. and min. radius");
    maxRadius = new wxTextCtrl(panelOptions,ID_OPTION_MAX_RADIUS, "600", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);
    minRadius = new wxTextCtrl(panelOptions, ID_OPTION_MIN_RADIUS, "12", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTRE);

	iterationSlider = new wxSlider(panelOptions, ID_OPTION_ITERATION, 0, 0, 1, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_MIN_MAX_LABELS | wxSL_AUTOTICKS | wxSL_VALUE_LABEL);

    //Set the sizers
    nmbPointSizer->Add(nmbPointsText, wxEXPAND);
    nmbPointSizer->Add(nmbPoints, wxALIGN_CENTER | wxEXPAND);

    divisorSizer->Add(divisorText,wxEXPAND);
    divisorSizer->Add(divisor,wxALIGN_CENTER | wxEXPAND);

    maxHeightSizer->Add(maxHeightText, wxEXPAND);
    maxHeightSizer->Add(maxHeight, wxALIGN_CENTER | wxEXPAND);

    minHeightSizer->Add(minHeightText, wxEXPAND);
    minHeightSizer->Add(minHeight, wxALIGN_CENTER | wxEXPAND);

    heightMultiplicatorSizer->Add(heightMultiplicatorText,wxEXPAND);
    heightMultiplicatorSizer->Add(heightMultiplicator,wxALIGN_CENTER | wxEXPAND);

    removeDuplicatesSizer->Add(removeDuplicatesButton, wxEXPAND);
    removeDuplicatesSizer->Add(removeDuplicatesVariance, wxEXPAND);

    triangulateSizer->Add(triangulateButton, wxEXPAND);
    triangulateSizer->Add(triangulateGauge, wxEXPAND);

    radiusOptionSizer->Add(radiusOption, wxEXPAND);
    radiusOptionSizer->Add(maxRadius, wxEXPAND);
    radiusOptionSizer->Add(minRadius, wxEXPAND);

    optionsSizer->Add(divisorSizer,0, wxEXPAND);
    optionsSizer->Add(heightMultiplicatorSizer,0, wxEXPAND);
    optionsSizer->Add(nmbPointSizer, 0, wxEXPAND);
    optionsSizer->Add(maxHeightSizer, 0, wxEXPAND);
    optionsSizer->Add(minHeightSizer, 0, wxEXPAND);
    optionsSizer->Add(removeDuplicatesSizer, 0, wxEXPAND);
    optionsSizer->Add(triangulateSizer, 0, wxEXPAND);
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

    fileMenu->Append(ID_FILE_OPEN, "Datei �ffnen");
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
EVT_TEXT_ENTER(ID_OPTION_heightMultiplicator, BasicFrame::setheightMultiplicator)
EVT_TEXT_ENTER(ID_OPTION_DIVISOR, BasicFrame::setDivisor)
EVT_TEXT_ENTER(ID_OPTION_MAX_HEIGHT, BasicFrame::setMaxHeight)
EVT_TEXT_ENTER(ID_OPTION_MIN_HEIGHT, BasicFrame::setMinHeight)
EVT_BUTTON(ID_OPTION_REMOVE_DUPLICATES, BasicFrame::removeDuplicates)
EVT_BUTTON(ID_OPTION_TRIANGULATE, BasicFrame::triangulatePoints)
EVT_TEXT_ENTER(ID_OPTION_MIN_RADIUS, BasicFrame::setMinRadius)
EVT_TEXT_ENTER(ID_OPTION_MAX_RADIUS, BasicFrame::setMaxRadius)
EVT_SCROLL_CHANGED(BasicFrame::SetIteration)
EVT_MENU(ID_FILE_OPEN, BasicFrame::OnFileOpen)
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
    wxFileDialog* dialog = new wxFileDialog(this, "Datei ausw�hlen", "", "");
    if (dialog->ShowModal() == wxID_CANCEL)
        return;

	dataStorage->LoadPoints(std::string(dialog->GetPath()));
	UpdateIterationRange();
	panelRender->SetIteration(START_ITERATION);
    
    //Set nmb of point in text box
    nmbPoints->SetLabel(std::to_string(dataStorage->GetPointsCount(START_ITERATION)));

    panelRender->activateRenderPoints(true);
    Refresh();
}

void BasicFrame::OnExportStl(wxCommandEvent & event)
{
	if (dataStorage)
	{
		StlExporter exporter(errorHandler);
		if (exporter.ExportStl("out.stl", dataStorage->GetTriangles(iterationSlider->GetValue())))
			SetStatusText("Export successful");
		else
			SetStatusText("Error at exporting file!");
	}
}

void BasicFrame::OnExportStlAllItr(wxCommandEvent & event)
{
	if (dataStorage)
	{
		StlExporter exporter(errorHandler);
		for (int i = iterationSlider->GetMin(); i < iterationSlider->GetMax(); ++i)
		{
			exporter.ExportStl("wave" + std::to_string(i) + ".stl", dataStorage->GetTriangles(i));
		}
	}
}

void BasicFrame::setheightMultiplicator(wxCommandEvent &e)
{
    try
    {
        panelRender->setheightMultiplicator(boost::lexical_cast<float>(e.GetString()));
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
        panelRender->setDivisor(boost::lexical_cast<float>(e.GetString()));
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
        panelRender->setMaxHeight(boost::lexical_cast<float>(e.GetString()));
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
        panelRender->setMinHeight(boost::lexical_cast<float>(e.GetString()));
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
		SetStatusText("Remove duplicates...");
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

	tri.Triangulate(dataStorage->GetPoints(iterationSlider->GetValue(),true), dataStorage->GetMin(iterationSlider->GetValue()), dataStorage->GetMax(iterationSlider->GetValue()),panelRender->getMinRadius(),panelRender->getMaxRadius());

	dataStorage->AddTriangles(tri.GetTriangles(),iterationSlider->GetValue());
	Refresh();
}

void BasicFrame::setMinRadius(wxCommandEvent & event)
{
    try
    {
        panelRender->setMinRadius(boost::lexical_cast<float>(event.GetString()));
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
        panelRender->setMaxRadius(boost::lexical_cast<float>(event.GetString()));
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
	if (dataStorage)
	{
		iterationSlider->SetMin(START_ITERATION);
		iterationSlider->SetMax(dataStorage->GetIterationCount() + START_ITERATION);
	}
}

void BasicFrame::updateNmbPoints(int _nmbPoints)
{
    nmbPoints->SetLabelText(std::to_string(_nmbPoints));
}

