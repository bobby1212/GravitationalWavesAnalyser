#pragma once
#include "SharedDefines.h"

class ErrorHandler
{
public:
	ErrorHandler(wxWindow* parent);
	~ErrorHandler();
	void DisplayError(ERROR_ID errorId);
	void DisplayError(std::string customMessage);
private:
	wxWindow* parent;
	wxMessageDialog* errorDialog;
};

