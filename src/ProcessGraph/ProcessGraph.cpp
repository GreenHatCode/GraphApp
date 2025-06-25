#include "ProcessGraph/ProcessGraph.h"
#include "ProcessGraph.h"

ProcessGraph::ProcessGraph(Graph *ptr, wxWindow *dialog_parent_window)
{
	m_graph_ptr = ptr;
	m_dialog_parent_window = dialog_parent_window;

}

bool ProcessGraph::DoProcess()
{
	if (m_graph_ptr->Empty() || m_dialog_parent_window == nullptr)return false;
	if (!Validate())return false;

    return false;
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
