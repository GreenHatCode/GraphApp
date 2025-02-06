#pragma once
#include "wx\wx.h"
#include "wx/tipdlg.h"


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

private:

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




    DECLARE_EVENT_TABLE();
};

