#include "NodeStructureInfoDialog.h"

BEGIN_EVENT_TABLE(NodeStructureInfoDialog, wxDialog)
    EVT_BUTTON(wxID_OK, NodeStructureInfoDialog::OnOK)
END_EVENT_TABLE()

NodeStructureInfoDialog::NodeStructureInfoDialog(
    wxWindow *parent, 
    wxWindowID id, 
    const wxString &title, 
    const wxPoint &pos, 
    const wxSize &size, 
    long style, const 
    wxString &name)
    :wxDialog(parent, id, title, pos, size, style, name)
{
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizerAndFit(topSizer);
    
    wxStaticBitmap* m_staticBitmap = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("res/node_info.bmp"), wxBITMAP_TYPE_BMP), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);
    
    topSizer->Add(m_staticBitmap, 0, wxALL, 5);
    
    wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    
    topSizer->Add(buttonsSizer, 1, wxALL|wxALIGN_RIGHT, 5);
    
    wxButton* ok_button = new wxButton(this, wxID_OK, _("OK"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);
    
    buttonsSizer->Add(ok_button, 0, wxALL, 5);
    
    SetTitle(wxT("Node structure information"));
    SetSize(wxSize(758, 622));

}

void NodeStructureInfoDialog::OnOK(wxCommandEvent& evt)
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