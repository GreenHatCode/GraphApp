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
	fileMenu->Append(wxID_EXIT, "E&xit\tAlt+F4"); // todo: exits from app

	wxMenu* editMenu = new wxMenu;
	editMenu->Append(wxID_CLEAR, "&Clear", "Clears drawing area"); // todo: clears the drawing area

	wxMenu* prefMenu = new wxMenu;
	prefMenu->Append(wxID_PREFERENCES); // todo: add: changing language, colour scheme

	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_HELP); // todo: add help window
	helpMenu->Append(wxID_ABOUT); // todo: add ref to github page

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(editMenu, "&Edit");
	menuBar->Append(prefMenu, "&Preferences");
	menuBar->Append(helpMenu, "&Help");

	// toolbar
	wxToolBar* toolBar = CreateToolBar(wxTB_FLAT);
	toolBar->SetToolBitmapSize(wxSize(24, 24));
	toolBar->AddRadioTool(ID_MODE_NORMAL, "", wxBitmap(cursor_xpm), wxBitmapBundle(), "Normal mode");
	toolBar->AddRadioTool(ID_MODE_ADD_NODE, "", wxBitmap(node_xpm), wxBitmapBundle(), "Add new node");
	toolBar->AddRadioTool(ID_MODE_ADD_EDGE, "", wxBitmap(edge_xpm), wxBitmapBundle(), "Add new edge");
	toolBar->AddRadioTool(ID_MODE_DELETE, "", wxBitmap(delete_xpm), wxBitmapBundle(), "Delete nodes and edges");
	toolBar->Realize();
	toolBar->AddSeparator();
	toolBar->AddTool(wxID_ANY, "", wxBitmap(process_color_xpm), "Calculate the graph");
	toolBar->Realize();




	SetToolBar(toolBar);
	SetMenuBar(menuBar);
	SetIcon(wxIcon(wxT("res/Pictogrammers-Material-Graph-outline.ico"), wxBITMAP_TYPE_ICO));
}

void mainFrame::OnQuit(wxCommandEvent& evt)
{
	Close(true);
}
