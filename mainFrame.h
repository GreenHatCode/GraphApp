#pragma once
#include "wx\wx.h"
#include "wx/tipdlg.h"
#include "wx/file.h"
#include "DrawingPanel.h"
#include "PreferenceDialog.h"
#include "PreferenceDialog.h"
#include "AppPreferences.h"
#include "QuickPrint.h"
#include "ProcessGraphDialog.h"

// toolbar images
#include "res/cursor24.xpm"
#include "res/delete.xpm"
#include "res/node24.xpm"
#include "res/edge24.xpm"
#include "res/process24color.xpm"
#include "res/help.xpm"


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
    AppPreferences m_app_preferences{ "files/global.ini" };

    // menu bar functions
    void OnNew(wxCommandEvent& evt);
    void OnOpen(wxCommandEvent& evt);
    void OnSave(wxCommandEvent& evt);
    void OnSaveAs(wxCommandEvent& evt);
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

