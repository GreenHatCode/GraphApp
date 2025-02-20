#pragma once
#include "wx/wx.h"
#include "wx/gbsizer.h"
#include "wx/srchctrl.h"
#include "mini/ini.h"

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

    // controls data
    bool dupl_warning = true;
    bool show_tip = true;
    int colour_scheme_type = 0;



    void SetUpTabPanel(); // setups the inital tab for wxpanel, the inital tab is 'General'
    void SetPreferenceTab(wxCommandEvent& evt); // changes the controls on wxpanel according to selected item in the list
    void UpdateApplyButton(wxUpdateUIEvent& evt);


    void OnOK(wxCommandEvent& evt);
    void OnCancel(wxCommandEvent& evt);
    void OnApply(wxCommandEvent& evt); // saves settings without exiting the dialog
    void SearchTab(wxCommandEvent& evt); // searches the tab in listbox

    bool IsControlsStateChanged(); // checks the states of all controls in the current tab  

    bool TransferDataFromWindow();
    bool TransferDataToWindow();
    bool SaveDataToFile();
    bool LoadDataFromFile();

    DECLARE_EVENT_TABLE();
};

