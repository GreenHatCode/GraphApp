#pragma once
#include "Graph.h"
#include "ProcessGraph/ProcessGraphDialog.h"
#include "ProcessGraph/ProcessGraphSettings.h"
#include "ProcessGraph/GraphCalculator.h"
#include "ProcessGraph/OutputProcessingResultsDialog.h"
#include "wx/wfstream.h"
#include "wx/numformatter.h"
#include <map>

// The class provides common methods for processing the graph and calculating its values.
// This class also performs graph validation and includes functionality from other classes in the ProcessGraph/ folder.

class ProcessGraph
{
public:
	ProcessGraph(Graph* ptr, wxWindow* dialog_parent_window);
	bool DoProcess(bool show_dialog = true); // executes graph porcessig, returns false if processing is failed
    void SetGraph(Graph* ptr); // sets a new graph, delete the previous graph before set a new one
    
    
    bool BuildAdjacencyMatrix();
    bool BuildIncidenceMatrix();
    bool BuildKirchhoffMatrix();
    bool SearchPathDijkstra();
    bool SearchPathBellmanFord();


private:
	Graph* m_graph_ptr = nullptr;
    wxWindow* m_dialog_parent_window = nullptr;
    ProcessGraphSettings m_process_settings;
    
    bool ProcessGraphValidate(); // validate graph for processing (calculate parameters form ProcessGraphDialog)
    bool MatrixValidate(); // validate graph for building matrices
    bool DijkstraAlgorithmValidate(); // validate graph before executing Dijkstra algorithm
    bool BellmanFordAlgorithmValidate(); // validate graph before executing BellmanFord algorithm
    bool ShowModalDialog();
    bool OutputResults(OutputDestination output_destination, const GraphCalculator& graph_calculator); // return false if can't output calculation results


};