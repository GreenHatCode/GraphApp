#include "PreferenceDialog.h"

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
	wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);

	wxPanel* panel = new wxPanel(this, wxID_ANY);
	panel->SetBackgroundColour(*wxGREEN);
	panel->SetMinSize(wxSize(440, 250));

	top_sizer->Add(panel, 1, wxALL|wxEXPAND, 5);


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
