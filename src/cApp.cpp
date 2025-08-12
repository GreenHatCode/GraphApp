#include "cApp.h"
#include "mainFrame.h"

DECLARE_APP(cApp);
wxIMPLEMENT_APP(cApp);


bool cApp::OnInit()
{
	mainFrame* frame = new mainFrame(wxT("Graph App"));
	frame->SetSize(600, 400);

	// open graph file if the app started by clicking on the file in the explorer
	wxArrayString args = wxApp::argv.GetArguments();
	if (args.size() > 1)
	{
		frame->OpenGraphFile(args[1]);
	}


	frame->Show(true);
	frame->ShowStartupTip();
	return true;
}
