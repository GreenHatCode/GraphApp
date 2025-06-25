#include "mainFrame.h"

enum {
	ID_MODE_NORMAL, // standard cursor
	ID_MODE_ADD_NODE, // the user can add new node
	ID_MODE_ADD_EDGE, // the user can add new edge
	ID_MODE_DELETE, // the use can delete either node or edge
	ID_PROCESS_GRAPH, // the app process the graph
	ID_ADD_EDGE_DIALOG
};

BEGIN_EVENT_TABLE(mainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, mainFrame::OnQuit)
	EVT_MENU(wxID_HELP, mainFrame::OnHelp)
	EVT_MENU(wxID_CLEAR, mainFrame::OnClear)
	EVT_MENU(ID_ADD_EDGE_DIALOG, mainFrame::OnInvokeAddEdgeDialog)
	EVT_MENU(wxID_PRINT, mainFrame::OnPrint)
	EVT_MENU(wxID_NEW, mainFrame::OnNew)
	EVT_MENU(wxID_ABOUT, mainFrame::OnAbout)
	EVT_MENU(wxID_OPEN, mainFrame::OnOpen)
	EVT_MENU(wxID_SAVE, mainFrame::OnSave)
	EVT_MENU(wxID_SAVEAS, mainFrame::OnSaveAs)
	EVT_MENU(wxID_PREFERENCES, mainFrame::OnPreferences)
	EVT_TOOL(ID_PROCESS_GRAPH, mainFrame::OnProcessGraph)
	EVT_TOOL_RANGE(ID_MODE_NORMAL, ID_MODE_DELETE, mainFrame::SetEditingRegime)
END_EVENT_TABLE()



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
	fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt+F4"));

	wxMenu* editMenu = new wxMenu;
	editMenu->Append(wxID_CLEAR, wxT("&Clear"), wxT("Clears drawing area"));
	editMenu->Append(ID_ADD_EDGE_DIALOG, wxT("&Add edge"), wxT("Adds a new edge via dialog"));

	wxMenu* prefMenu = new wxMenu;
	prefMenu->Append(wxID_PREFERENCES);

	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_HELP);
	helpMenu->Append(wxID_ABOUT); // redirects to project github repository

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
	toolBar->AddTool(ID_PROCESS_GRAPH, "", wxBitmap(process_color_xpm), wxT("Calculate the graph"));
	toolBar->Realize();

	// creating controls
	drawingPanel = new DrawingPanel(this, wxID_ANY);

	// setting sizer
	wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);
	top_sizer->Add(drawingPanel, 1, wxALL | wxEXPAND);

	// file class
	m_graph_file = new GraphFile(wxT(""), drawingPanel->GetGraph());





	SetSizerAndFit(top_sizer);
	SetToolBar(toolBar);
	SetMenuBar(menuBar);

	SetIcon(wxIcon(wxT("res/favicon.ico"), wxBITMAP_TYPE_ICO));

	SetPreferences();
}

void mainFrame::OnNew(wxCommandEvent& evt)
{
	drawingPanel->GetGraph()->Clear();
	drawingPanel->Refresh();
	m_graph_file->SetCurrSaveFilename(wxT(""));
	this->SetTitle(wxT("Graph App"));
}

void mainFrame::OnOpen(wxCommandEvent& evt)
{
	wxFileDialog* load_file_dialog = new wxFileDialog(this, wxT("Load Graph"), "", "",
		wxT("Graph (*.graph)|*.graph"), wxFD_OPEN);
	if (load_file_dialog->ShowModal() == wxID_OK)
	{
		if (m_graph_file->LoadGraph(load_file_dialog->GetPath()) == nullptr)
		{
			wxLogError("Cannot load graph in file '%s'.", load_file_dialog->GetPath());
			return;
		}
		drawingPanel->SetGraph(m_graph_file->LoadGraph(load_file_dialog->GetPath()));
	}
}

void mainFrame::OnSave(wxCommandEvent& evt)
{
	if (!m_graph_file->SaveToFile())
	{
		// the user has not previously saved a graph to a file  
		OnSaveAs(evt);
	}
}

void mainFrame::OnSaveAs(wxCommandEvent& evt)
{
	// get a new save file location
	wxFileDialog* save_file_dialog = new wxFileDialog(this, wxT("Save Graph"), "", m_graph_file->GetCurrSaveFilename(),
		wxT("Graph (*.graph)|*.graph"), wxFD_SAVE);
	if (save_file_dialog->ShowModal() == wxID_OK)
	{
		if (!m_graph_file->SaveAsToFile(save_file_dialog->GetPath()))
		{
			wxLogError("Cannot save graph in file '%s'.", save_file_dialog->GetPath());
			return;
		}
	}
}

void mainFrame::OnPrint(wxCommandEvent& evt)
{
	std::function<void(wxDC& dc, int pageNum, wxSize dc_size)> print_method =
		std::bind(&DrawingPanel::Print, drawingPanel, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	QuickPrint* preview_print = new QuickPrint(1, wxT("Print preview"), 30, print_method); // Now all you need to do is pass a pointer to the print function to the class constructor

	// preforming page setup
	if (!preview_print->performPageSetup(true))
	{
		// the user cancelled
		return;
	}

	QuickPrint* finish_print = new QuickPrint(*preview_print); // making a copy of the object, the preview window will use it for printing

	// invoking preview window
	wxPrintData print_data = preview_print->getPrintData();
	wxPrintPreview* preview = new wxPrintPreview(preview_print, finish_print, &print_data);
	wxPreviewFrame* frame = new wxPreviewFrame(preview, this,
		"Print Preview",
		wxPoint(100, 100),
		wxSize(600, 650));
	frame->Centre(wxBOTH);
	frame->Initialize();
	frame->Show(true);

}

void mainFrame::OnQuit(wxCommandEvent& evt)
{
	Close(true);
}

void mainFrame::OnClear(wxCommandEvent& evt)
{
	drawingPanel->OnClear();
}

void mainFrame::OnInvokeAddEdgeDialog(wxCommandEvent &evt)
{
	AddEdgeDialog* dlg = new AddEdgeDialog(this, wxID_ANY, wxT("Add edge"), drawingPanel->GetGraph()->GetNodeIndices());
	if (dlg->ShowModal() == wxID_OK)
	{
		// add edge to the graph
		drawingPanel->AddNewEdge(dlg->GetNodeFromIndex(), dlg->GetNodeToIndex(), dlg->GetEdgeWeight());
	}
	dlg->Destroy();
	
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
	SetPreferences();
}

void mainFrame::OnHelp(wxCommandEvent& evt)
{
	// Shows tool tips
	ShowToolTip();
}

void mainFrame::OnAbout(wxCommandEvent& evt)
{
	wxLaunchDefaultBrowser(wxT("https://github.com/GreenHatCode/GraphApp"), wxBROWSER_NEW_WINDOW);
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

void mainFrame::OnProcessGraph(wxCommandEvent& evt)
{
	if(!drawingPanel->ProcessCurrentGraph()) wxLogError(wxT("Can't process the graph."));
}

bool mainFrame::ShowToolTip()
{
	wxTipProvider* tipProvider = wxCreateFileTipProvider(wxT("res/files/tool_tips.txt"), 0);
	bool showAtStartup = wxShowTip(this, tipProvider, true);
	delete tipProvider;
	return showAtStartup;
}

void mainFrame::SetPreferences()
{
	// setting preferences for drawing area
	drawingPanel->SetColourScheme(m_app_preferences.GetColourScheme());
	drawingPanel->ShowNodeDuplicationWarning(m_app_preferences.GetDuplicationWarning());



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
