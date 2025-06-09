#pragma once
#include "wx/wx.h"
#include "wx/tipdlg.h"
#include "wx/file.h"
#include "DrawingPanel.h"
#include "PreferenceDialog.h"
#include "PreferenceDialog.h"
#include "AppPreferences.h"
#include "QuickPrint.h"
#include "ProcessGraphDialog.h"
#include "ProcessGraph.h"
#include "OutputProcessingResultsDialog.h"
#include "wx/wfstream.h"
#include "GraphFile.h"
#include <wx/utils.h> 

// toolbar images
#include "toolbar_icons/cursor24.xpm"
#include "toolbar_icons/delete.xpm"
#include "toolbar_icons/node24.xpm"
#include "toolbar_icons/edge24.xpm"
#include "toolbar_icons/process24color.xpm"
#include "toolbar_icons/help.xpm"


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
    void OnNew(wxCommandEvent& evt); // clears all data
    void OnOpen(wxCommandEvent& evt); // loads graph from file
    void OnSave(wxCommandEvent& evt); // save graph to current save file
    void OnSaveAs(wxCommandEvent& evt); // save graph to a new file
    void OnPrint(wxCommandEvent& evt);
    void OnQuit(wxCommandEvent& evt);
    void OnClear(wxCommandEvent& evt);
    void OnPreferences(wxCommandEvent& evt);
    void OnHelp(wxCommandEvent& evt); // shows tool tip
    void OnAbout(wxCommandEvent& evt);
    void SetEditingRegime(wxCommandEvent& evt);
    void OnProcessGraph(wxCommandEvent& evt);

    bool ShowToolTip();
    void SetPreferences();

    DECLARE_EVENT_TABLE();
};

