#include "ProcessGraph/ProcessGraph.h"
#include "ProcessGraph.h"

ProcessGraph::ProcessGraph(Graph *ptr, wxWindow *dialog_parent_window)
{
	m_graph_ptr = ptr;
	m_dialog_parent_window = dialog_parent_window;

}

bool ProcessGraph::DoProcess(bool show_dialog)
{
	if(m_dialog_parent_window == nullptr) return false;
	if (!ProcessGraphValidate()) return false;

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
	if (m_process_settings.GetCalculateComplexityFactor()) graph_calculator.CalculateComplexityFactor();

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

bool ProcessGraph::BuildAdjacencyMatrix()
{
	if (!MatrixValidate()) return false;
	GraphCalculator graph_calculator(m_graph_ptr);
	OutputProcessingResultsDialog* dialog = new OutputProcessingResultsDialog(m_dialog_parent_window, wxID_ANY, wxT("Adjacency matrix"), graph_calculator.BuildAdjacencyMat().toWxString());
	dialog->ShowModal();
	dialog->Destroy(); 
	return true;
}

bool ProcessGraph::BuildIncidenceMatrix()
{
	if (!MatrixValidate()) return false;
	GraphCalculator graph_calculator(m_graph_ptr);
	OutputProcessingResultsDialog* dialog = new OutputProcessingResultsDialog(m_dialog_parent_window, wxID_ANY, wxT("Incidence matrix"), graph_calculator.BuildIncidenceMat().toWxString());
	dialog->ShowModal();
	dialog->Destroy(); 
	return true;
}

bool ProcessGraph::BuildKirchhoffMatrix()
{
	return false;
}

bool ProcessGraph::SearchPathDijkstra()
{
	return false;
}

bool ProcessGraph::SearchPathBellmanFord()
{
	return false;
}

bool ProcessGraph::ProcessGraphValidate()
{
	if (m_graph_ptr->Empty())
	{
		wxMessageBox("Your graph is empty. It can't be processed.", "Graph processing error", wxICON_ERROR);
		return false;
	}

	// searching for edges in which from->index > to->index
	for (size_t i = 0; i < m_graph_ptr->GetEdgeAmount(); i++)
	{
		Edge* curr_edge = m_graph_ptr->GetEdge(i);
		if (curr_edge->from->index > curr_edge->to->index)
		{
			wxString err_ms = "The edge ";
			err_ms.append(wxString::Format("(%i,%i) ", curr_edge->from->index, curr_edge->to->index));
			err_ms.append("has the wrong direction, turn around the edge.");
			wxMessageBox(err_ms, "Graph processing error", wxICON_ERROR);

			return false;
		}
	}

	return true;
}

bool ProcessGraph::MatrixValidate()
{
	if (m_graph_ptr->Empty())
	{
		wxMessageBox("Your graph is empty.", "Graph matrix building error", wxICON_ERROR);
		return false;
	}

    return true;
}

bool ProcessGraph::ShowModalDialog()
{
    ProcessGraphDialog* dlg = new ProcessGraphDialog(m_dialog_parent_window, wxID_ANY, wxT("Process graph options"), m_process_settings);
	return dlg->ShowModal() == wxID_OK;
}

bool ProcessGraph::OutputResults(OutputDestination output_destination, const GraphCalculator& graph_calculator)
{
	// convert text values
	// complexity factor
	wxString complexity_factor_str = "Complexity factor: ";
	complexity_factor_str.append(wxNumberFormatter::ToString(graph_calculator.GetComplexityFactor(), 3));
	complexity_factor_str.append(" ");
	if (graph_calculator.GetComplexityFactor() >= 1 && graph_calculator.GetComplexityFactor() <= 1.5) complexity_factor_str.append("(the network graph has simple complexity).");
	else if (graph_calculator.GetComplexityFactor() > 1.5 && graph_calculator.GetComplexityFactor() <= 2.0) complexity_factor_str.append("(the network graph has medium complexity).");
	else if (graph_calculator.GetComplexityFactor() > 2.0) complexity_factor_str.append("(the network graph has high complexity).");


	if (output_destination == OutputDestination::DRAWING_AREA)
	{
		// modifing nodes
		const std::vector<int>& m_T_early = graph_calculator.GetEarlyEventDates();
		const std::vector<int>& m_T_late = graph_calculator.GetLateEventDate();
		const std::vector<int>& m_Time_reserve = graph_calculator.GetTimeReserve();
		for (size_t i = 0; i < m_graph_ptr->GetNodeAmount(); i++)
		{
			Node* curr_node = m_graph_ptr->GetNodeByIndexInArray(i);
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
		
		m_dialog_parent_window->Refresh();
		
		if (m_process_settings.GetCalculateComplexityFactor()) wxMessageBox(complexity_factor_str, wxT("Complexity factor"));
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
			output_message.append(wxT("\n\n"));
		}

		// append complexity factor
		if(m_process_settings.GetCalculateComplexityFactor()) output_message.append(complexity_factor_str);


		// invoke dialog to output results as a text
		// or invoke dialog to save them into a file
		if (m_process_settings.GetOutputDestination() == OutputDestination::SEPARATE_WINDOW)
		{
			// create a new window and show there a message
			OutputProcessingResultsDialog* dialog = new OutputProcessingResultsDialog(m_dialog_parent_window, wxID_ANY, wxT("Processing results"), output_message);
			dialog->ShowModal();
			dialog->Destroy();
		}
		else
		{
			// output to txt file
			wxFileDialog* save_file_dialog = new wxFileDialog(m_dialog_parent_window, wxT("Save Results"), "", "",
				wxT("Plain Text (*.txt)|*.txt"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
			if (save_file_dialog->ShowModal() == wxID_OK)
			{
				wxFileOutputStream output_stream(save_file_dialog->GetPath());
				if (!output_stream.IsOk())
				{
					wxLogError("Cannot save current contents in file '%s'.", save_file_dialog->GetPath());
					return false;
				}
			
				if (!output_stream.WriteAll(output_message, output_message.size()))
				{
					wxLogError("Cannot write data in the file '%s'.", save_file_dialog->GetPath());
					return false;
				}
				output_stream.Close();
			}
		}
	}

    return true;
}
