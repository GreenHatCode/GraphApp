#include "ProcessGraph.h"

ProcessGraph::ProcessGraph(Graph* ptr, OutputDestination output_destination_type)
{
	m_graph_ptr = ptr;
	m_output_destination_type = output_destination_type;
}

bool ProcessGraph::DoProcess()
{
	if (m_graph_ptr->Empty())return false;

	// module 1, DM lab4
	// EARLY_EVENT_DATE
	// algorithm
	//
	// 1) find all edges that incomes in the node
	// 2) find the edge with max weight among these edges. This is our T_early
	// If the node has'n any incoming edges, T_early = 0

	// EARLY_EVENT_DATE
	std::vector<int>T_early(m_graph_ptr->GetNodeAmount()); // result array
	for (size_t i = 0; i < T_early.size(); i++)
	{
		int max_T_early = 0;
		for (int k = i - 1; k >= 0; k--)
		{
			Edge* curr_incoming_edge = m_graph_ptr->GetEdge(m_graph_ptr->GetNode(k), m_graph_ptr->GetNode(i));
			if (curr_incoming_edge == nullptr)continue;

			int tmp = curr_incoming_edge->weight + T_early[k];
			if (max_T_early < tmp) max_T_early = tmp;
		}

		T_early[i] = max_T_early;
	}








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
