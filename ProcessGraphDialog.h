#pragma once
#include "wx/wx.h"

// dialog description
// This dialog is used to select what the app will do with graph
//
//
//  How to add a new processing option?
//

class ProcessGraphDialog :
    public wxDialog
{
public:
    ProcessGraphDialog(wxWindow* parent, wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE,
        const wxString& name = wxASCII_STR(wxDialogNameStr));

    ~ProcessGraphDialog();

private:

};

