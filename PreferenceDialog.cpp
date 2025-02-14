#include "PreferenceDialog.h"

enum {
	ID_SEARCH,
	ID_PREFERENCE_TABS,
	ID_PANEL,
	ID_CHECK1,
	ID_CHECK2
};



BEGIN_EVENT_TABLE(PreferenceDialog, wxDialog)
	EVT_UPDATE_UI(ID_PANEL, PreferenceDialog::SetPreferenceTab)
END_EVENT_TABLE()



PreferenceDialog::PreferenceDialog(
	wxWindow* parent, 
	wxWindowID id, 
	const wxString& title, 
	const wxPoint& pos, 
	const wxSize& size, 
	long style, 
	const wxString& name
)
	:wxDialog(parent, id, title, pos, size, style, name)
{
	// layout
	wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* box_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* pref_tabs_sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* buttons_sizer = new wxBoxSizer(wxHORIZONTAL);

	wxSearchCtrl* search_ctrl = new wxSearchCtrl(this, ID_SEARCH, wxEmptyString, wxDefaultPosition, wxSize(175, -1));
	search_ctrl->SetDescriptiveText(wxT("Search options Ctrl + E"));
	pref_tabs_sizer->Add(search_ctrl, 0, wxALL | wxEXPAND, 5);

	wxArrayString choices; // the list of possible preference tabs
	choices.Add(wxT("General"));
	choices.Add(wxT("Language"));
	wxListBox* pref_tabs = new wxListBox(this, ID_PREFERENCE_TABS, wxDefaultPosition, wxDefaultSize, choices);
	pref_tabs->SetSelection(0);
	pref_tabs_sizer->Add(pref_tabs, 0, wxALL | wxEXPAND, 5);

	main_panel = new wxPanel(this, ID_PANEL);
	main_panel->SetBackgroundColour(*wxGREEN); // remove at finish
	main_panel->SetMinSize(wxSize(300, 250));
	
	box_sizer->Add(pref_tabs_sizer);
	box_sizer->Add(main_panel, 1, wxALL | wxEXPAND, 5);

	wxButton* ok_button = new wxButton(this, wxID_OK);
	wxButton* cancel_button = new wxButton(this, wxID_CANCEL);
	wxButton* apply_button = new wxButton(this, wxID_APPLY); // applies changes without closing the dialog

	buttons_sizer->Add(ok_button, 0, wxALL, 5);
	buttons_sizer->Add(cancel_button, 0, wxALL, 5);
	buttons_sizer->Add(apply_button, 0, wxALL, 5);

	top_sizer->Add(box_sizer, 1, wxALL | wxEXPAND, 5);
	top_sizer->Add(buttons_sizer, 0, wxALL|wxALIGN_RIGHT, 5);

	SetSizerAndFit(top_sizer);

	SetUpTabPanels(); // creates a panel for each element in the list
}

PreferenceDialog::~PreferenceDialog()
{
}

void PreferenceDialog::SetUpTabPanels()
{
	// creates a panel for each element in the list

	//создать наследника от панели и разнести в него конструкторы для каждой вкладки


	// general panel layout
	wxBoxSizer* top_sizer1 = new wxBoxSizer(wxVERTICAL);
	wxCheckBox* check1 = new wxCheckBox(main_panel, ID_CHECK1, wxT("Show warning when a new node with existing index is added."));
	top_sizer1->Add(check1, 0, wxALL, 5);
	wxCheckBox* check2 = new wxCheckBox(main_panel, ID_CHECK2, wxT("Show tip of the day at start."));
	top_sizer1->Add(check2, 0, wxALL, 5);
	main_panel->SetSizerAndFit(top_sizer1);

}

void PreferenceDialog::SetPreferenceTab(wxUpdateUIEvent& evt)
{
	// changes the controls on wxpanel according to selected item in the list
	wxListBox* tabs = (wxListBox*)FindWindow(ID_PREFERENCE_TABS);

	switch (tabs->GetSelection())
	{
	case 0: // general preferences
	{
		wxCheckBox* check1 = (wxCheckBox*)main_panel->FindItem(ID_CHECK1);
		check1->Show();
		Layout();
	}
	break;
	case 1: // language preferences
	{
		wxCheckBox* check1 = (wxCheckBox*)main_panel->FindItem(ID_CHECK1);
		check1->Hide();
		Layout();
	}
	break;

	default:
		wxMessageBox(wxT("Error in the file PreferenceDialog.cpp, method SetPreferenceTab."));
		break;
	}

}

void PreferenceDialog::OnOK(wxCommandEvent& evt)
{
}

void PreferenceDialog::OnCancel(wxCommandEvent& evt)
{
}

bool PreferenceDialog::TransferDataFromWindow()
{
	return false;
}

bool PreferenceDialog::TransferDataToWindow()
{
	return false;
}
