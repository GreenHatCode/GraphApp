#include "cApp.h"
#include "mainFrame.h"

DECLARE_APP(cApp);
wxIMPLEMENT_APP(cApp);


bool cApp::OnInit()
{
	mainFrame* frame = new mainFrame(wxT("Graph App"));
	frame->SetSize(600, 400);

	frame->Show(true);
	frame->ShowStartupTip();
	return true;
}
