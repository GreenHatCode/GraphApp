#pragma once
#include "Graph.h"
#include "ProcessGraphDialog.h"

// the class is used to process graph, calculate nodes' params etc.

class ProcessGraph
{
public:
	ProcessGraph(Graph* ptr, OutputDestination output_destination_type = OutputDestination::DRAWING_AREA);
	bool DoProcess(); // executes graph porcessig, returns false if processing is failed

    void SetCalculateEarlyEventDate(bool value);
    void SetCalculateLateEventDate(bool value);
    void SetCalculateEvenTimeReserne(bool value);
    void SetDrawCriticalPath(bool value);

private:
	Graph* m_graph_ptr = nullptr;
    OutputDestination m_output_destination_type = OutputDestination::DRAWING_AREA;


    // module 1, DM lab4
    bool m_calculate_t_early = false; // ID_EARLY_EVENT_DATE
    bool m_calculate_t_late = false; // ID_LATE_EVENT_DATE
    bool m_calculate_R = false; // ID_EVENT_TIME_RESERVE
    bool m_search_critical_path = false; // ID_CRITICAL_PATH

    // module 2, SA lab 1,2

};

