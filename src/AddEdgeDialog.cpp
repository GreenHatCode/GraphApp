#include "AddEdgeDialog.h"


AddEdgeDialog::AddEdgeDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
    :wxDialog(parent, id, title, pos, size, style, name)
{
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(topSizer);
    
    wxStaticText* instruction_static_text = new wxStaticText(this, wxID_ANY, _("Static Text Label"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);
    
    topSizer->Add(instruction_static_text, 0, wxALL, 5);
    
    wxBoxSizer* edge_nodes_sizer = new wxBoxSizer(wxHORIZONTAL);
    
    topSizer->Add(edge_nodes_sizer, 1, wxALL|wxALIGN_CENTER, 1);
    
    wxArrayString nodes_from_choiceArr;
    wxChoice* nodes_from_choice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), nodes_from_choiceArr, 0);
    
    edge_nodes_sizer->Add(nodes_from_choice, 0, wxALL, 5);
    
    wxStaticBitmap* row_bitmap = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("res/row_bitmap.bmp"), wxBITMAP_TYPE_BMP), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0 );
    
    edge_nodes_sizer->Add(row_bitmap, 0, wxALL, 5);
    
    wxArrayString nodes_to_choiceArr;
    wxChoice* nodes_to_choice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), nodes_to_choiceArr, 0);
    
    edge_nodes_sizer->Add(nodes_to_choice, 0, wxALL, 5);
    
    wxBoxSizer* edge_weight_sizer = new wxBoxSizer(wxHORIZONTAL);
    
    topSizer->Add(edge_weight_sizer, 1, wxALL|wxALIGN_CENTER, 1);
    
    wxSpinCtrl* edge_weight_spinCtrl = new wxSpinCtrl(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), wxSP_ARROW_KEYS);
    edge_weight_spinCtrl->SetRange(-9999, 99999);
    edge_weight_spinCtrl->SetValue(0);
    
    edge_weight_sizer->Add(edge_weight_spinCtrl, 0, wxALL|wxALIGN_CENTER, 5);
    edge_weight_spinCtrl->SetMinSize(wxSize(100,-1));
    
    wxButton* add_edge_button = new wxButton(this, wxID_ANY, _("Add edge"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);
    
    topSizer->Add(add_edge_button, 0, wxALL|wxEXPAND, 5);
    
    SetName(wxT("AddEdgeDialog"));
    SetSize(500, 200);


}

AddEdgeDialog::~AddEdgeDialog()
{
}