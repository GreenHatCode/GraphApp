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
    wxPanel* main_panel = NULL;
    int curr_tab_idx = 0;


    void SetUpTabPanel(); // setups the inital tab for wxpanel, the inital tab is 'General'
    void SetPreferenceTab(wxUpdateUIEvent& evt); // changes the controls on wxpanel according to selected item in the list



    void OnOK(wxCommandEvent& evt);
    void OnCancel(wxCommandEvent& evt);

    bool TransferDataFromWindow();
    bool TransferDataToWindow();


    DECLARE_EVENT_TABLE();
};

