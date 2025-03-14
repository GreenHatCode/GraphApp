#include "GraphFile.h"

GraphFile::GraphFile(const wxString& file, const Graph* graph)
{
	m_curr_save_file = file;
	m_graph_ptr = graph;
}

bool GraphFile::SaveToFile()
{
	return false;
}

bool GraphFile::SaveAsToFile(const wxString& file)
{
	return false;
}

Graph* GraphFile::LoadGraph(const wxString& file)
{
	return nullptr;
}

wxString GraphFile::GetCurrSaveFilename()
{
	return m_curr_save_file;
}
