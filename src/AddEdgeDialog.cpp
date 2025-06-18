#include "AddEdgeDialog.h"

enum {
    ID_NODE_FROM,
    ID_NODE_TO,
    ID_EDGE_WEIGHT
};

BEGIN_EVENT_TABLE(AddEdgeDialog, wxDialog)
    EVT_BUTTON(wxID_OK, AddEdgeDialog::OnOK)
END_EVENT_TABLE()

AddEdgeDialog::AddEdgeDialog(
    wxWindow* parent, 
    wxWindowID id, 
    const wxString& title,
    const std::vector<int>& node_indices_list, 
    const wxPoint& pos, 
    const wxSize& size, 
    long style, 
    const wxString& name
)
    :m_node_indices_list{node_indices_list} ,wxDialog(parent, id, title, pos, size, style, name)
{
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(topSizer);
    
    wxStaticText* instruction_static_text = new wxStaticText(this, wxID_ANY, _("Static Text Label"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);
    
    topSizer->Add(instruction_static_text, 0, wxALL, 5);
    
    wxBoxSizer* edge_nodes_sizer = new wxBoxSizer(wxHORIZONTAL);
    
    topSizer->Add(edge_nodes_sizer, 1, wxALL|wxALIGN_CENTER, 1);
    
    
    wxChoice* nodes_from_choice = new wxChoice(this, ID_NODE_FROM, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), m_nodes_from_choiceArr, 0);
    
    edge_nodes_sizer->Add(nodes_from_choice, 0, wxALL, 5);
    
    wxStaticBitmap* row_bitmap = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("res/row_bitmap.bmp"), wxBITMAP_TYPE_BMP), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0 );
    
    edge_nodes_sizer->Add(row_bitmap, 0, wxALL, 5);
    
    wxChoice* nodes_to_choice = new wxChoice(this, ID_NODE_TO, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), m_nodes_to_choiceArr, 0);
    
    edge_nodes_sizer->Add(nodes_to_choice, 0, wxALL, 5);
    
    wxBoxSizer* edge_weight_sizer = new wxBoxSizer(wxHORIZONTAL);
    
    topSizer->Add(edge_weight_sizer, 1, wxALL|wxALIGN_CENTER, 1);
    
    wxSpinCtrl* edge_weight_spinCtrl = new wxSpinCtrl(this, ID_EDGE_WEIGHT, wxT("0"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), wxSP_ARROW_KEYS);
    edge_weight_spinCtrl->SetRange(-9999, 99999);
    edge_weight_spinCtrl->SetValue(0);
    
    edge_weight_sizer->Add(edge_weight_spinCtrl, 0, wxALL|wxALIGN_CENTER, 5);
    edge_weight_spinCtrl->SetMinSize(wxSize(100,-1));
    
    wxBoxSizer *buttons_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* add_edge_button = new wxButton(this, wxID_OK, _("Add edge"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);
    wxButton* cancel_button = new wxButton(this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);

    buttons_sizer->Add(add_edge_button, 0, wxALL|wxEXPAND, 5);
    buttons_sizer->Add(cancel_button, 0, wxALL|wxEXPAND, 5);

    topSizer->Add(buttons_sizer, 1, wxALL|wxALIGN_RIGHT, 1);
    SetName(wxT("AddEdgeDialog"));
    SetSize(500, 200);

    InitializeNodesLists();
    if(!TransferDataToWindow())
        wxLogError(wxT("Nodes not provided"));
}

AddEdgeDialog::~AddEdgeDialog()
{
}

void AddEdgeDialog::OnOK(wxCommandEvent& evt)
{
    if (Validate() && TransferDataFromWindow())
	{
        if (IsModal())
        {
            EndModal(wxID_OK);
        }
        else
        {
            SetReturnCode(wxID_OK);
            this->Show(false);
        }
	}
	else wxMessageBox(wxT("You didn't pass the validation or the data wasn't transfered from window."));
}

bool AddEdgeDialog::TransferDataFromWindow()
{
    wxChoice* node_from_choice = (wxChoice*)FindWindow(ID_NODE_FROM);
    wxChoice* node_to_choice = (wxChoice*)FindWindow(ID_NODE_TO);
    wxSpinCtrl* edge_weight_ctrl = (wxSpinCtrl*)FindWindow(ID_EDGE_WEIGHT);

    if (node_from_choice->GetSelection() < 0 || node_to_choice->GetSelection() < 0) return false;
    if (!m_nodes_from_choiceArr[node_from_choice->GetSelection()].ToInt(&node_from_index)) return false;
    if (!m_nodes_to_choiceArr[node_to_choice->GetSelection()].ToInt(&node_to_index)) return false;
    edge_weight = edge_weight_ctrl->GetValue();

    return true;
}

bool AddEdgeDialog::TransferDataToWindow()
{
    wxChoice* node_from_choice = (wxChoice*)FindWindow(ID_NODE_FROM);
    wxChoice* node_to_choice = (wxChoice*)FindWindow(ID_NODE_TO);

    if (m_nodes_from_choiceArr.IsEmpty() || m_nodes_to_choiceArr.IsEmpty()) return false;
    
    node_from_choice->Set(m_nodes_from_choiceArr);
    node_to_choice->Set(m_nodes_to_choiceArr);


    return true;
}

void AddEdgeDialog::InitializeNodesLists()
{
    for (std::vector<int>::const_iterator iter = m_node_indices_list.begin(); iter != m_node_indices_list.end(); iter++)
    {
        m_nodes_from_choiceArr.Add(wxString::Format("%d", *iter));
    }
    m_nodes_to_choiceArr = m_nodes_from_choiceArr;
}
