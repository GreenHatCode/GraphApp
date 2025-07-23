#pragma once
#include "wx/wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinctrl.h>

// This dialog is used to get data from the user
// to create a new edge without drawing it on
// the drawing panel

class AddEdgeDialog:
    public wxDialog
{
public:
    AddEdgeDialog(wxWindow* parent, wxWindowID id,
        const wxString& title,
        const std::vector<int>& node_indices_list,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE,
        const wxString& name = wxASCII_STR(wxDialogNameStr));

    ~AddEdgeDialog();

    int GetEdgeWeight() { return edge_weight; };
    int GetNodeFromIndex() { return node_from_index; };
    int GetNodeToIndex() { return node_to_index; };

private:
    const std::vector<int> m_node_indices_list;
    wxArrayString m_node_indices_string_list;

    // edge params setted by the user
    int edge_weight = 0;
    int node_from_index = 0;
    int node_to_index = 0;

    void OnOK(wxCommandEvent& evt);
    void UpdateDrowDownLists(wxCommandEvent& evt);
    bool TransferDataFromWindow();
    bool TransferDataToWindow();
    void InitializeNodesList(); // convert int indices to arraystring

    DECLARE_EVENT_TABLE();
};