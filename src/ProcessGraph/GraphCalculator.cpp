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

MatN GraphCalculator::BuildKirchhoffMat()
{
	std::map<int,int> node_index_mat_index; // key - node index, value - node index in array
	for (size_t i = 0; i < m_graph_ptr->GetNodeAmount(); i++)
	{
		node_index_mat_index.emplace(m_graph_ptr->GetNodeByIndexInArray(i)->index, i);
	}

    m_kirchhoff_matrix = std::make_unique<MatN>(MatN(m_graph_ptr->GetNodeAmount(), m_graph_ptr->GetNodeAmount()));

	for (size_t row = 0; row < m_graph_ptr->GetNodeAmount(); row++)
	{
		std::vector<Edge*> outcoming_edges = m_graph_ptr->GetOutcomingEdges(m_graph_ptr->GetNodeByIndexInArray(row)); 
		(*m_kirchhoff_matrix).At(row, row) = outcoming_edges.size(); // main diagonal	
		for (size_t col = 0; col < outcoming_edges.size(); col++)
		{
			(*m_kirchhoff_matrix).At(row, node_index_mat_index[outcoming_edges[col]->to->index]) = -1;
		}
	}

	return *(m_kirchhoff_matrix);
}

wxString GraphCalculator::SeacrhShortestPathDijkstra()
{
	size_t nodeCount = m_graph_ptr->GetNodeAmount();
    const std::vector<int> nodeIndices = m_graph_ptr->GetNodeIndices();

    // choose start node (lowest index)
    int startIndex = *std::min_element(nodeIndices.begin(), nodeIndices.end());
    Node* startNode = m_graph_ptr->GetEdgeByNodeIndex(startIndex);

    // distance map
    std::unordered_map<int, int> dist;
    std::unordered_map<int, int> prev;
    for (int idx : nodeIndices) 
	{
        dist[idx] = std::numeric_limits<int>::max();
        prev[idx] = -1;
    }
    dist[startNode->index] = 0;

    // min-heap priority queue
    auto cmp = [&](const Node* a, const Node* b) { return dist[a->index] > dist[b->index]; };
    std::priority_queue<const Node*, std::vector<const Node*>, decltype(cmp)> pq(cmp);
    pq.push(startNode);

    while (!pq.empty()) 
	{
        const Node* current = pq.top();
        pq.pop();

        for (Edge* edge : m_graph_ptr->GetOutcomingEdges(current)) 
		{
            const Node* neighbor = edge->to;
            int alt = dist[current->index] + edge->weight;
            if (alt < dist[neighbor->index]) 
			{
                dist[neighbor->index] = alt;
                prev[neighbor->index] = current->index;
                pq.push(neighbor);
            }
        }
    }

    // result string
    wxString oss;
    for (int idx : nodeIndices)
        oss << "Node " << idx << " -> Distance: " << dist[idx] << "\n";

    return oss;
}

wxString GraphCalculator::SeacrhShortestPathBellmanFord()
{
    const int INF = std::numeric_limits<int>::max();
    size_t node_count = m_graph_ptr->GetNodeAmount();
    m_graph_ptr->Rank(); // ensure nodes are ordered by index

    Node* start_node = m_graph_ptr->GetNodeByIndexInArray(0); // start from node with lowest index
    std::map<int, int> dist;
    std::map<int, int> prev;
    for (size_t i = 0; i < node_count; ++i) // initialize maps with start values
    {
        dist.emplace(m_graph_ptr->GetNodeByIndexInArray(i)->index, INF);
        prev.emplace(m_graph_ptr->GetNodeByIndexInArray(i)->index, -1);
    }
    
    
    dist[start_node->index] = 0;

    // Step 1: Relax all edges |V|-1 times
    for (size_t i = 1; i < node_count; ++i) {
        for (size_t j = 0; j < node_count; ++j) {
            const Node* u = m_graph_ptr->GetNodeByIndexInArray(j);
            for (Edge* edge : m_graph_ptr->GetOutcomingEdges(u)) {
                const Node* v = edge->to;
                int weight = edge->weight;
                if (dist[u->index] != INF && dist[u->index] + weight < dist[v->index]) {
                    dist[v->index] = dist[u->index] + weight;
                    prev[v->index] = u->index;
                }
            }
        }
    }

    // Step 2: Check for negative-weight cycles
    for (size_t j = 0; j < node_count; ++j) {
        const Node* u = m_graph_ptr->GetNodeByIndexInArray(j);
        for (Edge* edge : m_graph_ptr->GetOutcomingEdges(u)) {
            const Node* v = edge->to;
            int weight = edge->weight;
            if (dist[u->index] != INF && dist[u->index] + weight < dist[v->index]) {
                return "Graph contains a negative-weight cycle.";
            }
        }
    }

    // Step 3: Build result string of shortest paths
    wxString result;
    for (size_t i = 0; i < node_count; ++i) {

        result << "Path to Node " << m_graph_ptr->GetNodeByIndexInArray(i)->index << ": ";
        if (dist[m_graph_ptr->GetNodeByIndexInArray(i)->index] == INF) {
            result << "Unreachable\n";
            continue;
        }

        // std::vector<int> path;
        // for (int at = i; at != -1; at = prev[at])
        //     path.insert(path.begin(), at);

        // for (size_t j = 0; j < path.size(); ++j) {
        //     result << path[j];
        //     if (j < path.size() - 1) result << " -> ";
        // }
        result << " | Cost: " << dist[m_graph_ptr->GetNodeByIndexInArray(i)->index] << "\n";
    }

    return result;
}
