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

MatN GraphCalculator::BuildAdjacencyMat()
{
	std::map<int,int> node_index_mat_index; // key - node index, value - node index in array
	for (size_t i = 0; i < m_graph_ptr->GetNodeAmount(); i++)
	{
		node_index_mat_index.emplace(m_graph_ptr->GetNodeByIndexInArray(i)->index, i);
	}
	
	m_adjacency_matrix = std::make_unique<MatN>(MatN(m_graph_ptr->GetNodeAmount(), m_graph_ptr->GetNodeAmount()));
	for (size_t row = 0; row < m_graph_ptr->GetNodeAmount(); row++)
	{
		std::vector<Edge*> outcoming_edges = m_graph_ptr->GetOutcomingEdges(m_graph_ptr->GetNodeByIndexInArray(row)); 	
		for (size_t col = 0; col < outcoming_edges.size(); col++)
		{
			m_adjacency_matrix.get()->At(row, node_index_mat_index[outcoming_edges[col]->to->index]) = 1;
		}
	}
	return *(m_adjacency_matrix);
}

MatN GraphCalculator::BuildIncidenceMat()
{
    std::map<int,int> node_index_mat_index; // key - node index, value - node index in array
	for (size_t i = 0; i < m_graph_ptr->GetNodeAmount(); i++)
	{
		node_index_mat_index.emplace(m_graph_ptr->GetNodeByIndexInArray(i)->index, i);
	}
	
	m_incidence_matrix = std::make_unique<MatN>(MatN(m_graph_ptr->GetNodeAmount(), m_graph_ptr->GetEdgeAmount()));
	for (size_t i = 0; i < m_graph_ptr->GetEdgeAmount(); i++)
	{
		Edge* curr_edge = m_graph_ptr->GetEdge(i);
		(*m_incidence_matrix).At(node_index_mat_index[curr_edge->from->index], i) = 1;
		(*m_incidence_matrix).At(node_index_mat_index[curr_edge->to->index], i) = -1;
	}
	return *(m_incidence_matrix);
}
