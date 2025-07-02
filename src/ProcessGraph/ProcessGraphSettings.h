#pragma once
#include "wx/wx.h"

enum OutputDestination
{
    DRAWING_AREA,
    SEPARATE_WINDOW,
    TXT_FILE
};

class ProcessGraphSettings
{
public:
    ProcessGraphSettings();
    ~ProcessGraphSettings();

    void SetCalculateEarlyEventDate(bool value) { m_calculate_t_early = value; }
    void SetCalculateLateEventDate(bool value) { m_calculate_t_late = value; }
    void SetCalculateEvenTimeReserne(bool value) { m_calculate_R = value; }
    void SetDrawCriticalPath(bool value) { m_search_critical_path = value; }
    void SetComplexityFactor(bool value) { m_calculate_complexity_factor = value; }
    void SetOutputDestination(OutputDestination value)  { m_output_destination_type = value; }
   
    bool GetCalculateEarlyEventDate() { return m_calculate_t_early; }
    bool GetCalculateLateEventDate() { return m_calculate_t_late; }
    bool GetCalculateEvenTimeReserne() { return m_calculate_R; }
    bool GetDrawCriticalPath() { return m_search_critical_path; }
    bool GetComplexityFactor() { return m_calculate_complexity_factor; }
    OutputDestination GetOutputDestination() { return m_output_destination_type; }


private:
    bool m_calculate_t_early = false; // ID_EARLY_EVENT_DATE
    bool m_calculate_t_late = false; // ID_LATE_EVENT_DATE
    bool m_calculate_R = false; // ID_EVENT_TIME_RESERVE
    bool m_search_critical_path = false; // ID_CRITICAL_PATH
    bool m_calculate_complexity_factor = false; // ID_COMPLEXITY_FACTOR
    OutputDestination m_output_destination_type = OutputDestination::DRAWING_AREA;
};
