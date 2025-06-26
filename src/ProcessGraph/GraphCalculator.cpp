#include "ProcessGraph/GraphCalculator.h"
#include "GraphCalculator.h"

GraphCalculator::GraphCalculator(Graph *ptr)
{
    m_graph_ptr = ptr;
}
void GraphCalculator::CalculateEarlyEventDate()
{
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
}

void GraphCalculator::CalculateLateEventDate()
{
    CalculateEarlyEventDate();
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
}

void GraphCalculator::CalculateTimeReserve()
{
    CalculateEarlyEventDate();
	CalculateLateEventDate();
	for (size_t i = 0; i < m_Time_reserve.size(); i++)
	{
		m_Time_reserve[i] = m_T_late[i] - m_T_early[i];
	}
}

void GraphCalculator::SearchCritPath()
{
    CalculateTimeReserve();

	// make all edges non-critical
	for (size_t i = 0; i < m_graph_ptr->GetEdgeAmount(); i++)
	{
		m_graph_ptr->GetEdge(i)->critical_path_edge = false;
	}

	std::map<int, int> nodes_time_reserves;
	for (size_t i = 0; i < m_Time_reserve.size(); i++)
	{
		nodes_time_reserves.emplace(m_graph_ptr->GetNode(i)->index, m_Time_reserve[i]);
	}

	// find all cirtical nodes
	for (int i = 0; i < m_Time_reserve.size(); i++)
	{
		if (m_Time_reserve[i] == 0)	m_crit_path.push_back(m_graph_ptr->GetNode(i));
	}
}
