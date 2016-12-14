#pragma once
#include "SharedDefines.h"
#include "Render.h"
#include "Parser.h"
#include "ErrorHandler.h"
#include "HeightmapExporter.h"

class BasicFrame : public wxFrame
{
public:
	BasicFrame(const wxChar *title, int xpos, int ypos, int width, int height);
	~BasicFrame();

	//Event handler
	void OnFileOpen(wxCommandEvent& event);
    void OnExportHeightmap(wxCommandEvent& event);
	void setHeightDivisor(wxCommandEvent& event);
	void setDivisor(wxCommandEvent& event);
    void setMaxHeight(wxCommandEvent& event);
    void setMinHeight(wxCommandEvent& event);
    void removeDuplicates(wxCommandEvent& event);

	ErrorHandler* GetErrorHandler() { return errorHandler; }
private:
	wxBoxSizer* sizer;
	wxPanel* panelOptions;
	Render* panelRender;
	bool CreatePanels();

	DECLARE_EVENT_TABLE()

	wxStatusBar* statusBar;

	//Menu
	wxMenuBar* menuBar;
	wxMenu* fileMenu;
	wxMenu* editMenu;
    wxMenu* exportMenu;
	wxMenu* infoMenu;
	bool CreateMenu();

	//Option Panel
	wxBoxSizer* optionsSizer;
	wxBoxSizer* heightDivisorSizer;
	wxBoxSizer* divisorSizer;
    wxBoxSizer* nmbPointSizer;
    wxBoxSizer* maxHeightSizer;
    wxBoxSizer* minHeightSizer;

	wxStaticText* heightDivisorText;
	wxStaticText* divisorText;
    wxStaticText* nmbPointsText;
    wxStaticText* maxHeightText;
    wxStaticText* minHeightText;

	wxTextCtrl* heightDivisor;
	wxTextCtrl* divisor;
    wxStaticBox* nmbPoints;
    wxTextCtrl* maxHeight;
    wxTextCtrl* minHeight;

    wxSizer* removeDuplicatesSizer;
    wxButton* removeDuplicatesButton;
    wxGauge* removeDuplicateGauge;

	int height, width;
	Parser* parser;
	ErrorHandler* errorHandler;
};

