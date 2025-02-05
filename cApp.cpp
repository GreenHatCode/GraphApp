#include "cApp.h"
#include "mainFrame.h"

DECLARE_APP(cApp);
wxIMPLEMENT_APP(cApp);


bool cApp::OnInit()
{
	mainFrame* frame = new mainFrame(wxT("App template"));
	frame->SetSize(600, 400);

	frame->Show(true);
	return true;
}
