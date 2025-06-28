#pragma once
#include "wx/wx.h"
#include "wx/clipbrd.h"

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

    void OnOK(wxCommandEvent& evt);
    void OnCopy(wxCommandEvent& evt);

    DECLARE_EVENT_TABLE();
};

