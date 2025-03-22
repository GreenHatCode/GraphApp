#pragma once
#include "Graph.h"
#include "wx/xml/xml.h"


class GraphFile
{
public:
	GraphFile(const wxString& file, const Graph* graph);
	bool SaveToFile(); // saves graph in opended file
	bool SaveAsToFile(const wxString& file); // saves graph to a new file
	Graph* LoadGraph(const wxString& file); // constructs new graph using data from save file
	wxString GetCurrSaveFilename();


private:
	wxString m_curr_save_file;
	const Graph* m_graph_ptr;
};

