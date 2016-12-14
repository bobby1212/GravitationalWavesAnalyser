#include "ErrorHandler.h"



ErrorHandler::ErrorHandler(wxWindow* _parent)
{
	parent = _parent;
}


ErrorHandler::~ErrorHandler()
{
}

void ErrorHandler::DisplayError(std::string customMessage)
{
	errorDialog = new wxMessageDialog(parent, customMessage, "Error",wxICON_ERROR);
	errorDialog->ShowModal();
}

void ErrorHandler::DisplayError(ERROR_ID error_id)
{
	std::string errorMessage("");
	switch (error_id)
	{
	case ERROR_NAN:
		errorMessage += "The entered string is not a number!";
		break;
	case ERROR_ONE_POINT:
		errorMessage += "Only one point to render!";
		break;
    case ERROR_UNKNOWN:
        errorMessage += "An unknow error occured!";
        break;
	default:
		errorMessage += "Mo message";
		break;
	}
	errorDialog = new wxMessageDialog(parent, errorMessage, "Error", wxICON_ERROR);
	errorDialog->ShowModal();
}
