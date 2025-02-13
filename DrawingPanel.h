#pragma once
#include "wx/wx.h"
#include "Graph.h"
#include "wx/numdlg.h"

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
    enum ColourScheme {
        COLOURED,
        MONOCHROME
    };
    
    
    DrawingPanel(wxWindow* parent, wxWindowID winid);
    void OnClear(); // clears drawing area
    void SetDrawingRegime(DrawingRegimes regime);
    void SetColourScheme(ColourScheme scheme);
    void PrintDrawing(wxDC& dc);
private:
    Graph graph;
    DrawingRegimes drawing_regime = STANDARD_CURSOR;
    Node* selected_begin_node = nullptr;
    ColourScheme colour_scheme = COLOURED;

    void OnLeftDClick(wxMouseEvent& evt); // general drawing
    void OnPaint(wxPaintEvent& evt); // calls after Refresh()
    void DrawNode(const Node* node); // adds and draw a new node
    void DrawEdge(const Edge* edge);
    void OnMove(wxMouseEvent& evt);
    
    

    DECLARE_EVENT_TABLE();
};

