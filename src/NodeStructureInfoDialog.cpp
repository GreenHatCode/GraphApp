#include "NodeStructureInfoDialog.h"

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