#pragma once
#include "Graph.h"
#include "wx/xml/xml.h"
#include <vector>

// This class stores information about the file in which the current graph is saved.
// It also provides methods for loading and saving the graph to a file.

class GraphFile
{
public:
	GraphFile(const wxString& file, const Graph* graph);
	bool SaveToFile(); // saves graph in opended file
	bool SaveAsToFile(const wxString& file); // saves graph to a new file
	Graph* LoadGraph(const wxString& file); // constructs new graph using data from save file
	
	wxString GetCurrSaveFileName();
	wxString GetCurrSaveFilePath();
	void SetCurrSaveFilePath(const wxString& file_path = "");

private:
	wxString m_curr_save_file_path;
	const Graph* m_graph_ptr;
};

