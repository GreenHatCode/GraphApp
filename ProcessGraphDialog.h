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

    bool GetCalculateEarlyEventDate();
    bool GetCalculateLateEventDate();
    bool GetCalculateEvenTimeReserne();
    bool GetDrawCriticalPath();
    int GetOutputDestination();


private:
    // calculate
    bool m_calculate_t_early = false;
    bool m_calculate_t_late = false;
    bool m_calculate_R = false;

    // draw
    bool m_draw_critical_path = false;

    // output destination
    int m_output_destination = 0; // 0 - Drawing area, 1 - Separate window, 2 - .txt file 

    void OnOK(wxCommandEvent& evt);

    bool TransferDataFromWindow();
    bool TransferDataToWindow();




};

