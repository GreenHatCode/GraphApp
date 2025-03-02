#include "ProcessGraph.h"

ProcessGraph::ProcessGraph(Graph* ptr, OutputDestination output_destination_type)
{
	m_graph_ptr = ptr;
	m_output_destination_type = output_destination_type;
}

bool ProcessGraph::DoProcess()
{
	if (m_graph_ptr->Empty())return false;
	if (!Validate())return false;

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

	// LATE_EVENT_DATE
	std::vector<int>T_late(m_graph_ptr->GetNodeAmount()); // result array
	T_late[m_graph_ptr->GetNodeAmount() - 1] = T_early[m_graph_ptr->GetNodeAmount() - 1];
	for (int i = T_late.size() - 2; i >= 0; i--)
	{
		int min_T_late = std::numeric_limits<int>::max();
		for (int k = i + 1; k < T_late.size(); k++)
		{
			Edge* curr_outcoming_edge = m_graph_ptr->GetEdge(m_graph_ptr->GetNode(i), m_graph_ptr->GetNode(k));
			if (curr_outcoming_edge == nullptr)continue;

			int tmp = T_late[k] - curr_outcoming_edge->weight;
			if (min_T_late > tmp) min_T_late = tmp;
		}

		T_late[i] = min_T_late;
	}

	// EVENT_TIME_RESERVE
	std::vector<int> time_reserve(m_graph_ptr->GetNodeAmount());
	for (size_t i = 0; i < time_reserve.size(); i++)
	{
		time_reserve[i] = T_late[i] - T_early[i];
	}



	//OutPutResults();

	return true;
}

bool ProcessGraph::Validate()
{
	// searching for edges in which from->index > to->index
	for (size_t i = 0; i < m_graph_ptr->GetEdgeAmount(); i++)
	{
		Edge* curr_edge = m_graph_ptr->GetEdge(i);
		if (curr_edge->from->index > curr_edge->to->index)return false;
	}




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
