#pragma once
#include "wx/wx.h"
#include "ProcessGraph/ProcessGraphSettings.h"

// dialog description
// This dialog is used to select what the app will do with graph
//
//
// How to add a new option?
// 1) add control creation in the constructor
// 2) add a variable to store control data
// 3) add a get method for this variable
// 4) add the necessary code to TransferDataFromWindow and TransferDataToWindow
//

class ProcessGraphDialog :
    public wxDialog
{
public:
    ProcessGraphDialog(wxWindow* parent, wxWindowID id,
        const wxString& title,
        ProcessGraphSettings& process_settings,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE,
        const wxString& name = wxASCII_STR(wxDialogNameStr));

    ~ProcessGraphDialog();
private:
    ProcessGraphSettings& m_process_settings;
    void OnOK(wxCommandEvent& evt);
    void OnSelectAll(wxCommandEvent& evt); // select/unselect all controls

    bool TransferDataFromWindow();
    bool TransferDataToWindow();

    DECLARE_EVENT_TABLE();
};

