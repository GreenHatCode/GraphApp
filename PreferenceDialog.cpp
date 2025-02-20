#include "PreferenceDialog.h"

enum {
	ID_SEARCH,
	ID_PREFERENCE_TABS,
	ID_PANEL,
	ID_DUPL_WARNING_CHECK,
	ID_TIP_CHECK,
	ID_COLOUR_SCHEME
};

BEGIN_EVENT_TABLE(PreferenceDialog, wxDialog)
	EVT_UPDATE_UI(wxID_APPLY, PreferenceDialog::UpdateApplyButton)
	EVT_SEARCH(ID_SEARCH, PreferenceDialog::SearchTab)
	EVT_LISTBOX(ID_PREFERENCE_TABS, PreferenceDialog::SetPreferenceTab)
	EVT_BUTTON(wxID_APPLY, PreferenceDialog::OnApply)
	EVT_BUTTON(wxID_OK, PreferenceDialog::OnOK)
END_EVENT_TABLE()

PreferenceDialog::PreferenceDialog(
	wxWindow* parent, 
	wxWindowID id, 
	const wxString& title, 
	const AppPreferences& preferences_data,
	const wxPoint& pos, 
	const wxSize& size, 
	long style, 
	const wxString& name
)
	:m_preferences_data{preferences_data}, m_preferences_copy{preferences_data},
	wxDialog(parent, id, title, pos, size, style, name)
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
	m_curr_tab_idx = pref_tabs->GetSelection();
	pref_tabs_sizer->Add(pref_tabs, 0, wxALL | wxEXPAND, 5);

	m_main_panel = new wxPanel(this, ID_PANEL);
	m_main_panel->SetBackgroundColour(*wxGREEN); // remove at finish
	m_main_panel->SetMinSize(wxSize(300, 250));
	
	box_sizer->Add(pref_tabs_sizer);
	box_sizer->Add(m_main_panel, 1, wxALL | wxEXPAND, 5);

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
	TransferDataToWindow(); // transfers data to controls
}

PreferenceDialog::~PreferenceDialog()
{
}

void PreferenceDialog::SetPreferencesData(AppPreferences& value)
{
	m_preferences_data = value;
}

AppPreferences PreferenceDialog::GetPreferencesData()
{
	return m_preferences_data;
}

void PreferenceDialog::SetUpTabPanel()
{
	// setups the inital tab for wxpanel, the inital tab is 'General'
	// general panel layout
	wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);
	wxCheckBox* dupl_warning_check = new wxCheckBox(m_main_panel, ID_DUPL_WARNING_CHECK, wxT("Show warning when a new node with existing index is added."));
	top_sizer->Add(dupl_warning_check, 0, wxALL, 5);
	wxCheckBox* tip_check = new wxCheckBox(m_main_panel, ID_TIP_CHECK, wxT("Show tip of the day at start."));
	top_sizer->Add(tip_check, 0, wxALL, 5);
	m_main_panel->SetSizerAndFit(top_sizer);

}

void PreferenceDialog::UpdateApplyButton(wxUpdateUIEvent& evt)
{
	// update the state of the apply button 
	// if the user changes the state of any control
	if (IsPreferencesChanged())
	{
		evt.Enable(true);
	}
	else
	{
		evt.Enable(false);
	}
}

void PreferenceDialog::SetPreferenceTab(wxCommandEvent& evt)
{
	// changes the controls on wxpanel according to selected item in the list
	wxListBox* tabs = (wxListBox*)FindWindow(ID_PREFERENCE_TABS);

	if (m_curr_tab_idx != tabs->GetSelection())
	{
		// change the tab panel
		m_curr_tab_idx = tabs->GetSelection();
		m_main_panel->Freeze();
		m_main_panel->GetSizer()->Clear(true);
		wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);
		m_main_panel->SetSizer(top_sizer);

		switch (m_curr_tab_idx)
		{
		case 0:
		{
			// general tab panel

			wxCheckBox* dupl_warning_check = new wxCheckBox(m_main_panel, ID_DUPL_WARNING_CHECK, wxT("Show warning when a new node with existing index is added."));
			top_sizer->Add(dupl_warning_check, 0, wxALL, 5);
			wxCheckBox* tip_check = new wxCheckBox(m_main_panel, ID_TIP_CHECK, wxT("Show tip of the day at start."));
			top_sizer->Add(tip_check, 0, wxALL, 5);
		}
			break;
		case 1:
		{
			// appearance tab panel

			wxBoxSizer* colour_scheme_sizer = new wxBoxSizer(wxHORIZONTAL);
			wxStaticText* color_scheme_label = new wxStaticText(m_main_panel, wxID_ANY, _("Colour scheme:"), wxDefaultPosition, wxSize(-1, -1), 0);
			colour_scheme_sizer->Add(color_scheme_label, 0, wxALL, 5);

			wxArrayString colour_shceme_choiceArr;
			colour_shceme_choiceArr.Add(_("Coloured"));
			colour_shceme_choiceArr.Add(_("Black/White"));
			wxChoice* colour_shceme_choice = new wxChoice(m_main_panel, ID_COLOUR_SCHEME, wxDefaultPosition, wxSize(-1, -1), colour_shceme_choiceArr, 0);
			colour_shceme_choice->SetSelection(0);
			colour_scheme_sizer->Add(colour_shceme_choice, 0, wxALL, 2);

			top_sizer->Add(colour_scheme_sizer, 0, wxALL, 5);
		}
			break;

		default:
			wxLogError(wxT("Error in the file PreferenceDialog.cpp, method SetPreferenceTab."));
			break;
		}


		m_main_panel->Layout();
		m_main_panel->Thaw();
		m_main_panel->Refresh();
		TransferDataToWindow();
	}
}

void PreferenceDialog::OnOK(wxCommandEvent& evt)
{
	if (Validate() && TransferDataFromWindow())
	{
		if (!m_preferences_copy.SaveDataToFile())wxLogError("Can't save data to file global.ini");
		else
		{
			m_preferences_data = m_preferences_copy;

			if (IsModal())
			{
				EndModal(wxID_OK); // if modal
			}
			else
			{
				SetReturnCode(wxID_OK);
				this->Show(false); // if modeless
			}
		}
	}
	else wxMessageBox(wxT("You didn't pass the validation or the data wasn't transfered from window."));
}

void PreferenceDialog::OnApply(wxCommandEvent& evt)
{
	if (!m_preferences_copy.SaveDataToFile())wxLogError("Can't save data to file global.ini");
	else
	{
		m_preferences_data = m_preferences_copy;
	}
}

void PreferenceDialog::SearchTab(wxCommandEvent& evt)
{
	wxListBox* pref_tabs = (wxListBox* )FindWindow(ID_PREFERENCE_TABS);
	int item_index = pref_tabs->FindString(evt.GetString());
	if (item_index != wxNOT_FOUND)
	{
		pref_tabs->SetSelection(item_index);
	}

}

bool PreferenceDialog::IsPreferencesChanged()
{
	switch (m_curr_tab_idx)
	{
	case 0: // general tab panel
	{
		wxCheckBox* dupl_warning_check = (wxCheckBox*)FindWindow(ID_DUPL_WARNING_CHECK);
		wxCheckBox* tip_check = (wxCheckBox*)FindWindow(ID_TIP_CHECK);

		m_preferences_copy.SetDuplicationWarning(dupl_warning_check->GetValue());
		m_preferences_copy.SetShowTooltip(tip_check->GetValue());

	}
	break;
	case 1: // appearance tab panel
	{
		wxChoice* colour_shceme_choice = (wxChoice*)FindWindow(ID_COLOUR_SCHEME);

		m_preferences_copy.SetColourScheme((ColourSchemes)colour_shceme_choice->GetSelection());

	}
	break;
	default:
	{
		wxLogError("There is no IsPreferencesChanged implementation for tab index = %i", m_curr_tab_idx);
		return false;
	}
	break;
	}

	if (m_preferences_data != m_preferences_copy)
	{
		return true;
	}
	return false;
}

bool PreferenceDialog::TransferDataToWindow()
{
	switch (m_curr_tab_idx)
	{
	case 0: // general tab panel
	{
		wxCheckBox* dupl_warning_check = (wxCheckBox*)FindWindow(ID_DUPL_WARNING_CHECK);
		wxCheckBox* tip_check = (wxCheckBox*)FindWindow(ID_TIP_CHECK);

		dupl_warning_check->SetValue(m_preferences_copy.GetDuplicationWarning());
		tip_check->SetValue(m_preferences_copy.GetShowTooltip());
	}
		break;
	case 1: // appearance tab panel
	{
		wxChoice* colour_shceme_choice = (wxChoice*)FindWindow(ID_COLOUR_SCHEME);
		colour_shceme_choice->SetSelection(m_preferences_copy.GetColourScheme());
	}
		break;
	default:
	{
		wxLogError("There is no TransferDataToWindow implementation for tab index = %i", m_curr_tab_idx);
	}
		break;
	}

	return true;
}
