#include "ProcessGraph.h"

ProcessGraph::ProcessGraph(Graph* ptr, OutputDestination output_destination_type)
{
	m_graph_ptr = ptr;
	m_output_destination_type = output_destination_type;
	m_T_early.resize(ptr->GetNodeAmount());
	m_T_late.resize(ptr->GetNodeAmount());
	m_Time_reserve.resize(ptr->GetNodeAmount());
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
	// 2) find the edge with max weight among these edges. This is our m_T_early
	// If the node has'n any incoming edges, m_T_early = 0

	// EARLY_EVENT_DATE
	for (size_t i = 0; i < m_T_early.size(); i++)
	{
		int max_m_T_early = 0;
		for (int k = i - 1; k >= 0; k--)
		{
			Edge* curr_incoming_edge = m_graph_ptr->GetEdge(m_graph_ptr->GetNode(k), m_graph_ptr->GetNode(i));
			if (curr_incoming_edge == nullptr)continue;

			int tmp = curr_incoming_edge->weight + m_T_early[k];
			if (max_m_T_early < tmp) max_m_T_early = tmp;
		}

		m_T_early[i] = max_m_T_early;
	}

	// LATE_EVENT_DATE
	m_T_late[m_graph_ptr->GetNodeAmount() - 1] = m_T_early[m_graph_ptr->GetNodeAmount() - 1];
	for (int i = m_T_late.size() - 2; i >= 0; i--)
	{
		int min_m_T_late = std::numeric_limits<int>::max();
		for (int k = i + 1; k < m_T_late.size(); k++)
		{
			Edge* curr_outcoming_edge = m_graph_ptr->GetEdge(m_graph_ptr->GetNode(i), m_graph_ptr->GetNode(k));
			if (curr_outcoming_edge == nullptr)continue;

			int tmp = m_T_late[k] - curr_outcoming_edge->weight;
			if (min_m_T_late > tmp) min_m_T_late = tmp;
		}

		m_T_late[i] = min_m_T_late;
	}

	// EVENT_m_Time_reserve
	for (size_t i = 0; i < m_Time_reserve.size(); i++)
	{
		m_Time_reserve[i] = m_T_late[i] - m_T_early[i];
	}



	OutputResults();

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

void ProcessGraph::OutputResults()
{
	// modifing nodes
	for (size_t i = 0; i < m_graph_ptr->GetNodeAmount(); i++)
	{
		Node* curr_node = m_graph_ptr->GetNode(i);
		curr_node->early_event_deadline = m_T_early[i];
		curr_node->late_event_deadline = m_T_late[i];
		curr_node->time_reserve = m_Time_reserve[i];
	}


}
