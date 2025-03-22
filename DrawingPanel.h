#pragma once
#include "wx/wx.h"
#include "Graph.h"
#include "wx/numdlg.h"
#include "AppPreferences.h"

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
    void OnClear(); // clears drawing area
    void SetDrawingRegime(DrawingRegimes regime);
    void SetColourScheme(ColourSchemes scheme);
    void ShowNodeDuplicationWarning(bool show);
    void Print(wxDC& dc, int pageNum, wxSize dc_size);
    Graph* GetGraph();
    void SetGraph(Graph* graph_ptr);
private:
    Graph* m_graph;
    DrawingRegimes m_drawing_regime = STANDARD_CURSOR;
    Node* m_selected_begin_node = nullptr;
    ColourSchemes m_colour_scheme = ColourSchemes::COLOURED;

    // settings

    // show warning message if the user tries to add node with existing index
    bool m_dupl_warning = true;



    void OnLeftDClick(wxMouseEvent& evt); // general drawing
    void OnPaint(wxPaintEvent& evt); // calls after Refresh()
    void DrawNode(const Node* node); // adds and draw a new node
    void DrawEdge(const Edge* edge);
    void OnMove(wxMouseEvent& evt);
    
    

    DECLARE_EVENT_TABLE();
};

