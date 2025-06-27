#include "ProcessGraph/ProcessGraph.h"
#include "ProcessGraph.h"

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
		if(!ShowModalDialog()) return false; // the user cancelled the processing of the graph
	}

	// do processing (before get params from storage class)
	GraphCalculator graph_calculator(m_graph_ptr);
	if (m_process_settings.GetCalculateEarlyEventDate()) graph_calculator.CalculateEarlyEventDate();
	if (m_process_settings.GetCalculateLateEventDate()) graph_calculator.CalculateLateEventDate();
	if (m_process_settings.GetCalculateEvenTimeReserne()) graph_calculator.CalculateTimeReserve();
	if (m_process_settings.GetDrawCriticalPath()) graph_calculator.SearchCritPath();

	if (!OutputResults(m_process_settings.GetOutputDestination(), graph_calculator))
	{
		wxMessageBox("Can't output calculation results.", "Graph processing error", wxICON_ERROR);
		return false;
	}

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

bool ProcessGraph::OutputResults(OutputDestination output_destination, GraphCalculator graph_calculator)
{
	if (output_destination == OutputDestination::DRAWING_AREA)
	{
		// modifing nodes
		const std::vector<int>& m_T_early = graph_calculator.GetEarlyEventDates();
		const std::vector<int>& m_T_late = graph_calculator.GetLateEventDate();
		const std::vector<int>& m_Time_reserve = graph_calculator.GetTimeReserve();
		for (size_t i = 0; i < m_graph_ptr->GetNodeAmount(); i++)
		{
			Node* curr_node = m_graph_ptr->GetNode(i);
			if (m_process_settings.GetCalculateEarlyEventDate())curr_node->early_event_deadline = m_T_early[i];
			if (m_process_settings.GetCalculateLateEventDate())curr_node->late_event_deadline = m_T_late[i];
			if (m_process_settings.GetCalculateEvenTimeReserne())curr_node->time_reserve = m_Time_reserve[i];
		}

		if (m_process_settings.GetDrawCriticalPath())
		{
			// output ctirical path
			// marks edges as critical
			const std::vector<Node*>& m_crit_path = graph_calculator.GetCritPath();
			for (size_t i = 0; i < m_crit_path.size() - 1; i++)
			{
				for (size_t k = i + 1; k < m_crit_path.size(); k++)
				{
					Edge* crit_edge = m_graph_ptr->GetEdge(m_crit_path[i], m_crit_path[k]);
					if (crit_edge != nullptr)
					{
						crit_edge->critical_path_edge = true;
						break;
					}
				}
			}
		}
		
	}
	else 
	{
		wxString output_message;
		if (m_process_settings.GetCalculateEarlyEventDate())
		{
			const std::vector<int>& m_T_early = graph_calculator.GetEarlyEventDates();
			for (int i = 0; i < m_T_early.size(); i++)
			{
				output_message.append(wxString::Format("Node%i early event deadline: %i\n", i, m_T_early[i]));
			}
			output_message.append(wxT("\n"));
		}

		if (m_process_settings.GetCalculateLateEventDate())
		{
			const std::vector<int>& m_T_late = graph_calculator.GetLateEventDate();
			for (int i = 0; i < m_T_late.size(); i++)
			{
				output_message.append(wxString::Format("Node%i late event deadline: %i\n", i, m_T_late[i]));
			}
			output_message.append(wxT("\n"));
		}
		
		if (m_process_settings.GetCalculateEvenTimeReserne())
		{
			const std::vector<int>& m_Time_reserve = graph_calculator.GetTimeReserve();
			for (int i = 0; i < m_Time_reserve.size(); i++)
			{
				output_message.append(wxString::Format("Node%i event time reserve: %i\n", i, m_Time_reserve[i]));
			}
			output_message.append(wxT("\n"));
		}
		
		if (m_process_settings.GetDrawCriticalPath())
		{
			const std::vector<Node*>& m_crit_path = graph_calculator.GetCritPath();
			output_message.append(wxT("Critical path:"));
			for (int i = 0; i < m_crit_path.size(); i++)
			{
				output_message.append(wxString::Format(" %i,", m_crit_path[i]->index));
			}
			output_message.erase(output_message.end() - 1);
		}

		// invoke dialog to output results as a text
		// or invoke dialog to save them into a file
		if (m_process_settings.GetOutputDestination() == OutputDestination::SEPARATE_WINDOW)
		{
			// create a new window and show there a message
				OutputProcessingResultsDialog* dialog = new OutputProcessingResultsDialog(m_dialog_parent_window, wxID_ANY, wxT(""));
				dialog->SetOutputMessage(output_message);
				dialog->ShowModal();
				dialog->Destroy();
		}
		else
		{

		}
	}



    return true;
}
