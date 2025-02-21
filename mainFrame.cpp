#include "mainFrame.h"

enum {
	ID_MODE_NORMAL, // standard cursor
	ID_MODE_ADD_NODE, // the user can add new node
	ID_MODE_ADD_EDGE, // the user can add new edge
	ID_MODE_DELETE, // the use can delete either node or edge
	ID_PROCESS_GRAPH // the app process the graph
};

BEGIN_EVENT_TABLE(mainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, mainFrame::OnQuit)
	EVT_MENU(wxID_HELP, mainFrame::OnHelp)
	EVT_MENU(wxID_CLEAR, mainFrame::OnClear)
	EVT_MENU(wxID_PRINT, mainFrame::OnPrint)
	EVT_MENU(wxID_PREFERENCES, mainFrame::OnPreferences)
	EVT_TOOL_RANGE(ID_MODE_NORMAL, ID_MODE_DELETE, mainFrame::SetEditingRegime)
END_EVENT_TABLE()



mainFrame::mainFrame(const wxString& title)
	:wxFrame(NULL, wxID_ANY, title)
{
	// menus and menuBar
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(wxID_NEW); // todo: creates new project file
	fileMenu->Append(wxID_OPEN); // todo: openss new project file
	fileMenu->Append(wxID_SAVE); // todo: saves project file
	fileMenu->Append(wxID_SAVEAS); // todo: saves project file in specific location
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_PRINT); // todo: implement QuickPrint
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt+F4"));

	wxMenu* editMenu = new wxMenu;
	editMenu->Append(wxID_CLEAR, wxT("&Clear"), wxT("Clears drawing area")); // todo: clears the drawing area

	wxMenu* prefMenu = new wxMenu;
	prefMenu->Append(wxID_PREFERENCES); // todo: add: changing language, colour scheme

	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_HELP);
	helpMenu->Append(wxID_ABOUT); // todo: add ref to github page

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(fileMenu, wxT("&File"));
	menuBar->Append(editMenu, wxT("&Edit"));
	menuBar->Append(prefMenu, wxT("&Preferences"));
	menuBar->Append(helpMenu, wxT("&Help"));

	// toolbar
	wxToolBar* toolBar = CreateToolBar(wxTB_FLAT);
	toolBar->SetToolBitmapSize(wxSize(24, 24));
	toolBar->AddRadioTool(ID_MODE_NORMAL, "", wxBitmap(cursor_xpm), wxBitmapBundle(), wxT("Normal mode"));
	toolBar->AddRadioTool(ID_MODE_ADD_NODE, "", wxBitmap(node_xpm), wxBitmapBundle(), wxT("Add new node"));
	toolBar->AddRadioTool(ID_MODE_ADD_EDGE, "", wxBitmap(edge_xpm), wxBitmapBundle(), wxT("Add new edge"));
	toolBar->AddRadioTool(ID_MODE_DELETE, "", wxBitmap(delete_xpm), wxBitmapBundle(), wxT("Delete nodes and edges"));
	toolBar->Realize();
	toolBar->AddSeparator();
	toolBar->AddTool(wxID_ANY, "", wxBitmap(process_color_xpm), wxT("Calculate the graph"));
	toolBar->Realize();

	// creating controls
	drawingPanel = new DrawingPanel(this, wxID_ANY);

	// setting sizer
	wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);
	top_sizer->Add(drawingPanel, 1, wxALL | wxEXPAND);








	SetSizerAndFit(top_sizer);
	SetToolBar(toolBar);
	SetMenuBar(menuBar);
	SetIcon(wxIcon(wxT("res/Pictogrammers-Material-Graph-outline.ico"), wxBITMAP_TYPE_ICO));

	SetPreferences();
}

void mainFrame::OnPrint(wxCommandEvent& evt)
{
}

void mainFrame::OnQuit(wxCommandEvent& evt)
{
	Close(true);
}

void mainFrame::OnClear(wxCommandEvent& evt)
{
	drawingPanel->OnClear();
}

void mainFrame::OnPreferences(wxCommandEvent& evt)
{
	PreferenceDialog* dlg = new PreferenceDialog(this, wxID_ANY, wxT("Preferences"), m_app_preferences);
	if (dlg->ShowModal() == wxID_OK)
	{
		m_app_preferences = dlg->GetPreferencesData();
	}
	else
	{
		// the user could use apply button to save setting, so we need to load file again
		m_app_preferences.LoadDataFromFile();
	}
	dlg->Destroy();

}

void mainFrame::OnHelp(wxCommandEvent& evt)
{
	// Shows tool tips
	ShowToolTip();
}

void mainFrame::SetEditingRegime(wxCommandEvent& evt)
{
		switch (evt.GetId())
		{
		case ID_MODE_NORMAL: // normal cursor
			drawingPanel->SetDrawingRegime(DrawingPanel::STANDARD_CURSOR);
			break;
		case ID_MODE_ADD_NODE: // add new node
			drawingPanel->SetDrawingRegime(DrawingPanel::ADD_NODE);
			break;
		case ID_MODE_ADD_EDGE: // add new edge
			drawingPanel->SetDrawingRegime(DrawingPanel::ADD_EDGE);
			break;
		case ID_MODE_DELETE: // delete node or edge
			drawingPanel->SetDrawingRegime(DrawingPanel::DELETE_NODE_OR_EDGE);
			break;

		default:
			wxMessageBox("undefined regime file mainFrame.cpp");
			break;
		}
}

bool mainFrame::ShowToolTip()
{
	wxTipProvider* tipProvider = wxCreateFileTipProvider(wxT("files/tool_tips.txt"), 0);
	bool showAtStartup = wxShowTip(this, tipProvider, true);
	delete tipProvider;
	return showAtStartup;
}

void mainFrame::SetPreferences()
{
	// setting preferences for drawing area
	drawingPanel->SetColourScheme(m_app_preferences.GetColourScheme());




}

void mainFrame::ShowStartupTip()
{
	if (m_app_preferences.GetShowTooltip())
	{
		if (!ShowToolTip()) // user refused to seeing startup tool tip
		{
			m_app_preferences.SetShowTooltip(false);
			m_app_preferences.SaveDataToFile();
		}
	}

}
