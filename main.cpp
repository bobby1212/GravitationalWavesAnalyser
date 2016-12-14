#include "main.h"

IMPLEMENT_APP(MainApp);

bool MainApp::OnInit()
{
	BasicFrame *frame = new BasicFrame(wxT("Gravitationswellen"), -1, -1, 500, 500);
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}
