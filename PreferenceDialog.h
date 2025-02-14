#pragma once
#include "wx/wx.h"
#include "wx/gbsizer.h"
#include "wx/srchctrl.h"

class PreferenceDialog :
    public wxDialog
{
public:
    PreferenceDialog(wxWindow* parent, wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER,
        const wxString& name = wxASCII_STR(wxDialogNameStr));

    ~PreferenceDialog();


private:



    void OnOK(wxCommandEvent& evt);
    void OnCancel(wxCommandEvent& evt);

    bool TransferDataFromWindow();
    bool TransferDataToWindow();


    DECLARE_EVENT_TABLE();
};

