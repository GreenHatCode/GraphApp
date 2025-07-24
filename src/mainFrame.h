#pragma once
#include "wx/wx.h"
#include "wx/tipdlg.h"
#include "wx/file.h"
#include "DrawingPanel.h"
#include "AppPreferences/PreferenceDialog.h"
#include "AppPreferences/AppPreferences.h"
#include "QuickPrint.h"
#include "wx/wfstream.h"
#include "GraphFile.h"
#include "AddEdgeDialog.h"
#include <wx/utils.h> 
#include "NodeStructureInfoDialog.h"

// toolbar images
#include "toolbar_icons/cursor24.xpm"
#include "toolbar_icons/delete.xpm"
#include "toolbar_icons/node24.xpm"
#include "toolbar_icons/edge24.xpm"
#include "toolbar_icons/process24color.xpm"
#include "toolbar_icons/help.xpm"

// This class represents the main window of the application

class mainFrame :
    public wxFrame
{
public:
    mainFrame(const wxString& title);
    void ShowStartupTip(); // shows startup tip window unless disabled in files/global.ini

private:
    // settings variables
    bool m_showTipAtStartup = true;
    DrawingPanel* drawingPanel;
    AppPreferences m_app_preferences{ "res/files/global.ini" };
    GraphFile* m_graph_file;

    // menu bar functions
    // file menu
    void OnNew(wxCommandEvent& evt); // clears all data
    void OnOpen(wxCommandEvent& evt); // loads graph from file
    void OnSave(wxCommandEvent& evt); // save graph to current save file
    void OnSaveAs(wxCommandEvent& evt); // save graph to a new file
    void OnPrint(wxCommandEvent& evt);
    void OnQuit(wxCommandEvent& evt);
    
    // edit menu
    void OnClear(wxCommandEvent& evt);
    void OnClearCalculationParameters(wxCommandEvent& evt);
    void OnInvokeAddEdgeDialog(wxCommandEvent& evt);
    
    // preferences menu
    void OnPreferences(wxCommandEvent& evt);
    
    // help menu
    void OnHelp(wxCommandEvent& evt); // shows tool tip
    void OnAbout(wxCommandEvent& evt); // redirect to app github page
    void OnNodeStructureInfo(wxCommandEvent& evt); // shows image with node structure

    // build menu
    void OnRunAdjacencyMatrixAlgorithm(wxCommandEvent& evt);
    void OnRunIncidenceMatrixAlgorithm(wxCommandEvent& evt);
    void OnRunKirchhoffMatrixAlgorithm(wxCommandEvent& evt);
    void OnRunDijkstraAlgorithm(wxCommandEvent& evt);
    void OnRunBellmanFordAlgorithm(wxCommandEvent& evt);

    // toolbar
    void OnProcessGraph(wxCommandEvent& evt);
    void SetEditingRegime(wxCommandEvent& evt);


    bool ShowToolTip();
    void SetPreferences();

    DECLARE_EVENT_TABLE();
};

