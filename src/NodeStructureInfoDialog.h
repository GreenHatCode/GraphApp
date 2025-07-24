#pragma once
#include "wx/wx.h"
#include "wx/clipbrd.h"

// This class represents a dialog to show an image with node structure info. 

class NodeStructureInfoDialog: 
	public wxDialog
{
public:
	NodeStructureInfoDialog(
        wxWindow* parent, 
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE,
        const wxString& name = wxASCII_STR(wxDialogNameStr));

private: 
    void OnOK(wxCommandEvent& evt);

    DECLARE_EVENT_TABLE();
};