#pragma once
#include "wx/wx.h"
#include "wx/clipbrd.h"

// This class represents a dialog to output text. 
// The dialog allows the user to copy the text in it.

class OutputProcessingResultsDialog: 
	public wxDialog
{
public:
	OutputProcessingResultsDialog(
        wxWindow* parent, 
        wxWindowID id,
        const wxString& title,
        const wxString& message,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE,
        const wxString& name = wxASCII_STR(wxDialogNameStr));

private: 
    void OnOK(wxCommandEvent& evt);
    void OnCopy(wxCommandEvent& evt);

    DECLARE_EVENT_TABLE();
};

