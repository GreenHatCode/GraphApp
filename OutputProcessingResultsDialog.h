#pragma once
#include "wx/wx.h"


class OutputProcessingResultsDialog: 
	public wxDialog
{
public:
	OutputProcessingResultsDialog(wxWindow* parent, wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE,
        const wxString& name = wxASCII_STR(wxDialogNameStr));
    ~OutputProcessingResultsDialog();

    void SetOutputMessage(const wxString& message);
    void OnOK(wxCommandEvent& evt);

};

