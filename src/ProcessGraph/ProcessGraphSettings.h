#pragma once
#include "wx/wx.h"
#include "ProcessGraph/ProcessGraphDialog.h"

class ProcessGraphSettings
{
public:
    ProcessGraphSettings();
    ~ProcessGraphSettings();

    void SetCalculateEarlyEventDate(bool value);
    void SetCalculateLateEventDate(bool value);
    void SetCalculateEvenTimeReserne(bool value);
    void SetDrawCriticalPath(bool value);
    void SetOutputMessage(wxString message);
    void SetOutputDestination(OutputDestination destination);

    bool GetCalculateEarlyEventDate();
    bool GetCalculateLateEventDate();
    bool GetCalculateEvenTimeReserne();
    bool GetDrawCriticalPath();
    wxString GetOutputMessage();
    OutputDestination GetOutputDestination();


private:
    OutputDestination m_output_destination_type = OutputDestination::DRAWING_AREA;
    wxString output_message;
    bool m_calculate_t_early = false; // ID_EARLY_EVENT_DATE
    bool m_calculate_t_late = false; // ID_LATE_EVENT_DATE
    bool m_calculate_R = false; // ID_EVENT_TIME_RESERVE
    bool m_search_critical_path = false; // ID_CRITICAL_PATH

};
