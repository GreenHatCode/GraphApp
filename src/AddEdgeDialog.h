#pragma once
#include "wx/wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinctrl.h>

/* Desctiption:

*/

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

    int GetEdgeWeight();
    int GetNodeFromIndex();
    int GetNodeToIndex();

private:
    const std::vector<int> m_node_indices_list;
    wxArrayString m_nodes_from_choiceArr;
    wxArrayString m_nodes_to_choiceArr;

    // edge params setted by the user
    int edge_weight = 0;
    int node_from_index = 0;
    int node_to_index = 0;


    bool TransferDataFromWindow();
    bool TransferDataToWindow();
    void InitializeNodesLists(); // fills up drop-down lists during the dialog creation

};