#pragma once
#include "Graph.h"
#include "ProcessGraph/ProcessGraphDialog.h"
#include "ProcessGraph/ProcessGraphSettings.h"
#include <map>

// the class is used to process graph, calculate nodes' params etc.

class ProcessGraph
{
public:
	ProcessGraph(Graph* ptr, wxWindow* dialog_parent_window);
	bool DoProcess(bool show_dialog = true); // executes graph porcessig, returns false if processing is failed
    void SetGraph(Graph* ptr); // sets a new graph
    

private:
	Graph* m_graph_ptr = nullptr;
    wxWindow* m_dialog_parent_window = nullptr;
    ProcessGraphSettings m_process_settings;
    
    bool Validate();
    bool ShowModalDialog();


};