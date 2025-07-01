#pragma once
#include "wx/wx.h"
#include "Graph.h"
#include "wx/numdlg.h"
#include "AppPreferences/AppPreferences.h"
#include "ProcessGraph/ProcessGraph.h"

#include <wx/dcbuffer.h>

class DrawingPanel :
    public wxPanel
{
public:
    enum DrawingRegimes {
        STANDARD_CURSOR,
        ADD_NODE,
        ADD_EDGE,
        DELETE_NODE_OR_EDGE
    };
    
    
    DrawingPanel(wxWindow* parent, wxWindowID winid);
    ~DrawingPanel();
    void OnClear(); // clears drawing area
    void SetDrawingRegime(DrawingRegimes regime);
    void Print(wxDC& dc, int pageNum, wxSize dc_size);
    Graph* GetGraph();
    void SetGraph(Graph* graph_ptr);
    void AddNewEdge(int node_from_index, int node_to_index, int weight);
    bool ProcessCurrentGraph();

    // preferences set methods
    void SetColourScheme(ColourSchemes scheme);
    void ShowNodeDuplicationWarning(bool show);
    
private:
    Graph* m_graph = nullptr;
    DrawingRegimes m_drawing_regime = STANDARD_CURSOR;
    Node* m_selected_begin_node = nullptr;
    ColourSchemes m_colour_scheme = ColourSchemes::COLOURED;
    ProcessGraph* m_graph_processor = nullptr;

    // settings
    // show warning message if the user tries to add node with existing index
    bool m_dupl_warning = true;

    // temp variables
    wxPoint m_context_menu_click_coords;

    void AddNewNode(const wxPoint& node_coords);
    void AddNewEdge(const Node* node_from, const Node* node_to);

    void OnRightUp(wxMouseEvent& evt); // context menu
    void OnLeftUp(wxMouseEvent& evt); // add/delete node or edge
    void OnPaint(wxPaintEvent& evt); // calls after Refresh()
    void DrawNode(const Node* node); // adds and draw a new node
    void DrawEdge(const Edge* edge);
    void OnMove(wxMouseEvent& evt);
    
    // context menu buttons handlers
    void OnEditNode(wxCommandEvent& evt);
    void OnDeleteNode(wxCommandEvent& evt);
    void OnEditEdge(wxCommandEvent& evt);
    void OnTurnAroundEdge(wxCommandEvent& evt);
    void OnDeleteEdge(wxCommandEvent& evt);
    void OnAddNewNode(wxCommandEvent& evt);
    
    DECLARE_EVENT_TABLE();
};

