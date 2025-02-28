#include "ProcessGraph.h"

ProcessGraph::ProcessGraph(Graph* ptr, OutputDestination output_destination_type)
{
	m_graph_ptr = ptr;
	m_output_destination_type = output_destination_type;
}

bool ProcessGraph::DoProcess()
{
	if (m_graph_ptr->Empty())return false;







	//OutPutResults();

	return true;
}

void ProcessGraph::SetCalculateEarlyEventDate(bool value)
{
	m_calculate_t_early = value;
}

void ProcessGraph::SetCalculateLateEventDate(bool value)
{
	m_calculate_t_late = value;
}

void ProcessGraph::SetCalculateEvenTimeReserne(bool value)
{
	m_calculate_R = value;
}

void ProcessGraph::SetDrawCriticalPath(bool value)
{
	m_search_critical_path = value;
}
