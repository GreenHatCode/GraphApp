#include "mainFrame.h"

mainFrame::mainFrame(const wxString& title)
	:wxFrame(NULL, wxID_ANY, title)
{
	// menus and menuBar
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(wxID_NEW);
	fileMenu->Append(wxID_OPEN);
	fileMenu->Append(wxID_SAVE);
	fileMenu->Append(wxID_SAVEAS);
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_PRINT);
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "E&xit\tAlt+F4");

	wxMenu* editMenu = new wxMenu;
	editMenu->Append(wxID_CLEAR, "&Clear", "Clears drawing area");

	wxMenu* prefMenu = new wxMenu;
	prefMenu->Append(wxID_PREFERENCES);

	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_HELP);
	helpMenu->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(editMenu, "&Edit");
	menuBar->Append(prefMenu, "&Preferences");
	menuBar->Append(helpMenu, "&Help");



	SetMenuBar(menuBar);
	SetIcon(wxIcon(wxT("res/Pictogrammers-Material-Graph-outline.ico"), wxBITMAP_TYPE_ICO));
}