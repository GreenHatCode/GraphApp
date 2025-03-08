#include "OutputProcessingResultsDialog.h"

enum 
{
    ID_TEXT
};

OutputProcessingResultsDialog::OutputProcessingResultsDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

    wxTextCtrl* m_textCtrl80 = new wxTextCtrl(this, ID_TEXT, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxTE_READONLY | wxTE_MULTILINE);

    topSizer->Add(m_textCtrl80, 3, wxALL | wxEXPAND, 5);

    wxBoxSizer* buttons_sizer = new wxBoxSizer(wxHORIZONTAL);

    topSizer->Add(buttons_sizer, 0, wxALL | wxEXPAND | wxALIGN_RIGHT, 5);

    wxButton* m_button_ok = new wxButton(this, wxID_OK, _("OK"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    buttons_sizer->Add(m_button_ok, 0, wxALL, 5);

    wxButton* m_button_copy = new wxButton(this, wxID_COPY, _("Copy"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    buttons_sizer->Add(m_button_copy, 0, wxALL, 5);

    SetName(wxT("ProcessingResultsDialog"));
    SetMinClientSize(wxSize(500, 370));
    SetSize(wxDLG_UNIT(this, wxSize(500, 370)));
    SetSizerAndFit(topSizer);
}

void OutputProcessingResultsDialog::SetOutputMessage(const wxString& message)
{
    wxTextCtrl* textCtrl = (wxTextCtrl*)FindWindow(ID_TEXT);
    textCtrl->SetValue(message);
}

void OutputProcessingResultsDialog::OnOK(wxCommandEvent& evt)
{
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
