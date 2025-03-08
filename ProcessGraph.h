#pragma once
#include "Graph.h"
#include "ProcessGraphDialog.h"
#include <map>

// the class is used to process graph, calculate nodes' params etc.

class ProcessGraph
{
public:
	ProcessGraph(Graph* ptr, OutputDestination output_destination_type = OutputDestination::DRAWING_AREA);
	bool DoProcess(); // executes graph porcessig, returns false if processing is failed
    bool Validate(); // searches for mistakes in graph construction

    void SetCalculateEarlyEventDate(bool value);
    void SetCalculateLateEventDate(bool value);
    void SetCalculateEvenTimeReserne(bool value);
    void SetDrawCriticalPath(bool value);
    wxString GetOutputMessage();

private:
	Graph* m_graph_ptr = nullptr;
    OutputDestination m_output_destination_type = OutputDestination::DRAWING_AREA;
    wxString output_message;

    // calculatoion data
    std::vector<int> m_T_early; 
    std::vector<int> m_T_late; 
    std::vector<int> m_Time_reserve;
    std::vector<Node*> m_crit_path; // stores nodes that create a critical path

    // module 1, DM lab4
    bool m_calculate_t_early = false; // ID_EARLY_EVENT_DATE
    bool m_calculate_t_late = false; // ID_LATE_EVENT_DATE
    bool m_calculate_R = false; // ID_EVENT_TIME_RESERVE
    bool m_search_critical_path = false; // ID_CRITICAL_PATH

    void CalculateEarlyEventDate();
    void CalculateLateEventDate();
    void CalculateTimeReserve();
    void SearchCritPath();

    // module 2, SA lab 1,2






    void OutputResults(); // modifies graph nodes and edges with calculation results

};

