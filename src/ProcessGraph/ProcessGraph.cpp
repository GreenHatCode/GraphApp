#include "ProcessGraph/ProcessGraph.h"

ProcessGraph::ProcessGraph(Graph *ptr, wxWindow *dialog_parent_window)
{
	m_graph_ptr = ptr;
	m_dialog_parent_window = dialog_parent_window;

}

bool ProcessGraph::DoProcess(bool show_dialog)
{
	if(m_dialog_parent_window == nullptr)return false;
	if (m_graph_ptr->Empty())
	{
		wxMessageBox("Your graph is empty. It can't be processed.", "Graph processing error", wxICON_ERROR);
		return false;
	}

	if (!Validate())
	{
		wxMessageBox("You didn't pass the graph validation. Correct your net graph.", "Graph processing error", wxICON_ERROR);
		return false;
	}

	// call dialog and get processing params
	// if we don't call the dialog
	// the app will use processing params from the previous 
	// dialog call
	if (show_dialog)
	{
		if(ShowModalDialog())return false; // the user cancelled the processing of the graph
	}

	// do processing (before get params from storage class)
	GraphCalculator graph_calculator(m_graph_ptr);
	if (m_process_settings.GetCalculateEarlyEventDate()) graph_calculator.CalculateEarlyEventDate();
	if (m_process_settings.GetCalculateLateEventDate()) graph_calculator.CalculateEarlyEventDate();
	if (m_process_settings.GetCalculateEvenTimeReserne()) graph_calculator.CalculateEarlyEventDate();
	if (m_process_settings.GetDrawCriticalPath()) graph_calculator.CalculateEarlyEventDate();


    return true;
}

void ProcessGraph::SetGraph(Graph* ptr)
{
	m_graph_ptr = ptr;
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

bool ProcessGraph::ShowModalDialog()
{
    ProcessGraphDialog* dlg = new ProcessGraphDialog(m_dialog_parent_window, wxID_ANY, wxT("Process graph options"), m_process_settings);
	return dlg->ShowModal();
}
