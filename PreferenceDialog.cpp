#include "PreferenceDialog.h"

enum {
	ID_SEARCH,
	ID_PREFERENCE_TABS,
	ID_PANEL,
	ID_DUPL_WARNING_CHECK,
	ID_TIP_CHEKC,
	ID_COLOUR_SCHEME
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
	curr_tab_idx = pref_tabs->GetSelection();
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

	SetUpTabPanel();// setups the inital tab for wxpanel, the inital tab is 'General'
}

PreferenceDialog::~PreferenceDialog()
{
}

void PreferenceDialog::SetUpTabPanel()
{
	// setups the inital tab for wxpanel, the inital tab is 'General'
	// general panel layout
	wxBoxSizer* top_sizer1 = new wxBoxSizer(wxVERTICAL);
	wxCheckBox* check1 = new wxCheckBox(main_panel, ID_DUPL_WARNING_CHECK, wxT("Show warning when a new node with existing index is added."));
	top_sizer1->Add(check1, 0, wxALL, 5);
	wxCheckBox* check2 = new wxCheckBox(main_panel, ID_TIP_CHEKC, wxT("Show tip of the day at start."));
	top_sizer1->Add(check2, 0, wxALL, 5);
	main_panel->SetSizerAndFit(top_sizer1);

}

void PreferenceDialog::SetPreferenceTab(wxUpdateUIEvent& evt)
{
	// changes the controls on wxpanel according to selected item in the list
	wxListBox* tabs = (wxListBox*)FindWindow(ID_PREFERENCE_TABS);

	if (curr_tab_idx != tabs->GetSelection())
	{
		// change the tab panel
		curr_tab_idx = tabs->GetSelection();
		main_panel->Freeze();
		main_panel->GetSizer()->Clear(true);
		wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);
		main_panel->SetSizer(top_sizer);


		if (curr_tab_idx == 0)
		{
			// general tab panel
			
			wxCheckBox* dupl_warning_check = new wxCheckBox(main_panel, ID_DUPL_WARNING_CHECK, wxT("Show warning when a new node with existing index is added."));
			top_sizer->Add(dupl_warning_check, 0, wxALL, 5);
			wxCheckBox* tooptip_check = new wxCheckBox(main_panel, ID_TIP_CHEKC, wxT("Show tip of the day at start."));
			top_sizer->Add(tooptip_check, 0, wxALL, 5);
		}
		else if (curr_tab_idx == 1)
		{
			// appearance tab panel
			
			wxBoxSizer* colour_scheme_sizer = new wxBoxSizer(wxHORIZONTAL);

			wxStaticText* color_scheme_label = new wxStaticText(main_panel, wxID_ANY, _("Colour scheme:"), wxDefaultPosition, wxSize(-1, -1), 0);

			colour_scheme_sizer->Add(color_scheme_label, 0, wxALL, 5);

			wxArrayString colour_shceme_choiceArr;
			colour_shceme_choiceArr.Add(_("Coloured"));
			colour_shceme_choiceArr.Add(_("Black/White"));
			wxChoice* colour_shceme_choice = new wxChoice(main_panel, ID_COLOUR_SCHEME, wxDefaultPosition, wxSize(-1, -1), colour_shceme_choiceArr, 0);
			colour_shceme_choice->SetSelection(0);

			colour_scheme_sizer->Add(colour_shceme_choice, 0, wxALL, 2);
			
			
			top_sizer->Add(colour_scheme_sizer, 0, wxALL, 5);
		}
		else
		{
			wxMessageBox(wxT("Error in the file PreferenceDialog.cpp, method SetPreferenceTab."));
		}



		main_panel->Layout();
		main_panel->Thaw();
		main_panel->Refresh();
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
