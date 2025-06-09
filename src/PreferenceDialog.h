#pragma once
#include "wx/wx.h"
#include "wx/gbsizer.h"
#include "wx/srchctrl.h"
#include "AppPreferences.h"

// This dialog is used to edit the application settings. 
//
// How to add a new parameter:
// 1) execute the instruction in the AppPreferences.h file.
// 
// 2) add a new control to an existing tab or create a new tab. 
// If you create a new tab, add it to the navigation menu, it is created in the constructor (pref_tabs)
// To handle a new tab, add code to SetPreferenceTab() - constructs and displays tabs.
// 
// 3) Add handling for this control (get and set data). 
// Add code to IsPreferencesChanged() and TransferDataToWindow()
// 

class PreferenceDialog :
    public wxDialog
{
public:
    PreferenceDialog(wxWindow* parent, wxWindowID id,
        const wxString& title,
        const AppPreferences& preferences_data,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER,
        const wxString& name = wxASCII_STR(wxDialogNameStr));

    ~PreferenceDialog();

    // preferences get and set methods
    void SetPreferencesData(AppPreferences& value);
    AppPreferences GetPreferencesData();



private:
    wxPanel* m_main_panel = NULL;
    int m_curr_tab_idx = 0;

    AppPreferences m_preferences_data;
    AppPreferences m_preferences_copy;

    void SetUpTabPanel(); // setups the inital tab for wxpanel, the inital tab is 'General'
    void SetPreferenceTab(wxCommandEvent& evt); // changes the controls on wxpanel according to selected item in the list
    void UpdateApplyButton(wxUpdateUIEvent& evt);


    void OnOK(wxCommandEvent& evt);
    void OnApply(wxCommandEvent& evt); // saves settings without exiting the dialog
    void SearchTab(wxCommandEvent& evt); // searches the tab in listbox

    bool IsPreferencesChanged(); // checks the states of all controls in the current tab  

    bool TransferDataToWindow();


    DECLARE_EVENT_TABLE();
};

