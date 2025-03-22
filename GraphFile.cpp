#include "GraphFile.h"

GraphFile::GraphFile(const wxString& file, const Graph* graph)
{
	m_curr_save_file = file;
	m_graph_ptr = graph;
}

bool GraphFile::SaveToFile()
{
	//if curr save file is empty, that means the user have not saved the file previously
	return false;
}

bool GraphFile::SaveAsToFile(const wxString& file)
{
	wxXmlDocument xml_file;
	wxXmlNode* XmlGraph = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("Graph"));
	wxXmlNode* XmlGraphInfo = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("graph_info"));
	XmlGraph->AddChild(XmlGraphInfo);

	// adding nodes
	for (size_t i = 0; i < m_graph_ptr->GetNodeAmount(); i++)
	{
		wxXmlNode* XmlGraphNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("node"));
		
		const Node* node = m_graph_ptr->GetNode(i);
		
		// index
		wxXmlNode* node_index = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("index"));
		wxXmlNode* node_index_value = new wxXmlNode(wxXML_TEXT_NODE, wxT("index"), wxString::Format(wxT("%i"),node->index));
		node_index->AddChild(node_index_value);
		
		// coords
		wxXmlNode* node_coords = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("coords"));
		wxXmlNode* node_coords_x = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("coords_x"));
		wxXmlNode* node_coords_y = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("coords_y"));
		
		wxXmlNode* node_coords_x_value = new wxXmlNode(wxXML_TEXT_NODE, wxT("x"), wxString::Format(wxT("%i"), node->coords.x));
		node_coords_x->AddChild(node_coords_x_value);
		wxXmlNode* node_coords_y_value = new wxXmlNode(wxXML_TEXT_NODE, wxT("y"), wxString::Format(wxT("%i"), node->coords.y));
		node_coords_y->AddChild(node_coords_y_value);

		node_coords->AddChild(node_coords_x);
		node_coords->AddChild(node_coords_y);




		XmlGraphNode->AddChild(node_index);
		XmlGraphNode->AddChild(node_coords);


		XmlGraphInfo->AddChild(XmlGraphNode);
	}


	//add root node
	xml_file.SetRoot(XmlGraph);
	return xml_file.Save(file);
}

Graph* GraphFile::LoadGraph(const wxString& file)
{
	return nullptr;
}

wxString GraphFile::GetCurrSaveFilename()
{
	return m_curr_save_file;
}
