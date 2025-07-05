#include "ProcessGraph/GraphCalculator.h"
#include "GraphCalculator.h"

GraphCalculator::GraphCalculator(Graph *ptr)
{
    m_graph_ptr = ptr;
    m_T_early.resize(ptr->GetNodeAmount());
	m_T_late.resize(ptr->GetNodeAmount());
	m_Time_reserve.resize(ptr->GetNodeAmount());
}
void GraphCalculator::CalculateEarlyEventDate()
{
    for (size_t i = 0; i < m_T_early.size(); i++)
	{
		int max_m_T_early = 0;
		for (int k = i - 1; k >= 0; k--)
		{
			Edge* curr_incoming_edge = m_graph_ptr->GetEdge(m_graph_ptr->GetNodeByIndexInArray(k), m_graph_ptr->GetNodeByIndexInArray(i));
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
			Edge* curr_outcoming_edge = m_graph_ptr->GetEdge(m_graph_ptr->GetNodeByIndexInArray(i), m_graph_ptr->GetNodeByIndexInArray(k));
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

void GraphCalculator::CalculateComplexityFactor()
{
	m_complexity_factor = static_cast<float>(m_graph_ptr->GetEdgeAmount()) / static_cast<float>(m_graph_ptr->GetNodeAmount());
}

void GraphCalculator::SearchCritPath()
{
    CalculateTimeReserve();
	// find all cirtical nodes
	for (int i = 0; i < m_Time_reserve.size(); i++)
	{
		if (m_Time_reserve[i] == 0)	m_crit_path.push_back(m_graph_ptr->GetNodeByIndexInArray(i));
	}
}

void GraphCalculator::BuildAdjacencyMat()
{
	MatN matrix(4);
	matrix.At(2,2) = 10;
	int a = matrix.At(2,2);
	a++;
}
