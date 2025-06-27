#include "ProcessGraph/OutputProcessingResultsDialog.h"

enum 
{
    ID_TEXT
};

BEGIN_EVENT_TABLE(OutputProcessingResultsDialog, wxDialog)
    EVT_BUTTON(wxID_COPY, OutputProcessingResultsDialog::OnCopy)
END_EVENT_TABLE()

OutputProcessingResultsDialog::OutputProcessingResultsDialog(
    wxWindow* parent, 
    wxWindowID id, 
    const wxString& title,
    const wxString& message,
    const wxPoint& pos,
    const wxSize& size, 
    long style, 
    const wxString& name)
    :wxDialog(parent, id, title, pos, size, style, name)
{
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

    wxTextCtrl* m_textCtrl80 = new wxTextCtrl(this, ID_TEXT, message, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxTE_READONLY | wxTE_MULTILINE);

    topSizer->Add(m_textCtrl80, 3, wxALL | wxEXPAND, 5);

    wxBoxSizer* buttons_sizer = new wxBoxSizer(wxHORIZONTAL);

    topSizer->Add(buttons_sizer, 0, wxALL | wxEXPAND, 5);

    wxButton* m_button_ok = new wxButton(this, wxID_OK, _("OK"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    buttons_sizer->Add(m_button_ok, 0, wxALL, 5);

    wxButton* m_button_copy = new wxButton(this, wxID_COPY, _("Copy"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    buttons_sizer->Add(m_button_copy, 0, wxALL, 5);

    SetSizerAndFit(topSizer);
    SetSize(wxSize(500, 370));
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

void OutputProcessingResultsDialog::OnCopy(wxCommandEvent& evt)
{
    wxTextCtrl* textCtrl = (wxTextCtrl*)FindWindow(ID_TEXT);
    wxClipboard* clip = new wxClipboard();
    if (clip->Open())
    {
        clip->Clear();
        clip->SetData(new wxTextDataObject(textCtrl->GetValue()));
        clip->Flush();
        clip->Close();
    }
    else wxMessageBox("The clipboard copy failed", "Error", wxICON_ERROR | wxCENTRE);
    delete clip;
}
