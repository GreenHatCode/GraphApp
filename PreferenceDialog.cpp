#include "PreferenceDialog.h"

enum {
	ID_SEARCH,
	ID_PREFERENCE_TABS,
	ID_PANEL
};



BEGIN_EVENT_TABLE(PreferenceDialog, wxDialog)

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

	wxBoxSizer* top_sizer = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer* pref_tabs_sizer = new wxBoxSizer(wxVERTICAL);
	
	wxSearchCtrl* search_ctrl = new wxSearchCtrl(this, ID_SEARCH, wxEmptyString, wxDefaultPosition, wxSize(175, -1));
	search_ctrl->SetDescriptiveText(wxT("Search options Ctrl + E"));
	pref_tabs_sizer->Add(search_ctrl, 0, wxALL | wxEXPAND, 5);


	wxArrayString choices;
	choices.Add(wxT("General"));
	choices.Add(wxT("Language"));
	wxListBox* pref_tabs = new wxListBox(this, ID_PREFERENCE_TABS, wxDefaultPosition, wxDefaultSize, choices);
	pref_tabs_sizer->Add(pref_tabs, 0, wxALL | wxEXPAND, 5);

	wxPanel* panel = new wxPanel(this, ID_PANEL);
	panel->SetBackgroundColour(*wxGREEN);
	panel->SetMinSize(wxSize(440, 250));



	top_sizer->Add(pref_tabs_sizer);
	top_sizer->Add(panel, 1, wxALL | wxEXPAND, 5);

	SetSizerAndFit(top_sizer);
}

PreferenceDialog::~PreferenceDialog()
{
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
