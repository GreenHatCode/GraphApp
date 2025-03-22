#include "GraphFile.h"

GraphFile::GraphFile(const wxString& file, const Graph* graph)
{
	m_curr_save_file = file;
	m_graph_ptr = graph;
}

bool GraphFile::SaveToFile()
{
	if (m_curr_save_file.empty())return false;
	return SaveAsToFile(m_curr_save_file);
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

		// early_event_deadline
		wxXmlNode* node_early_event_deadline = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("early_event_deadline"));
		wxXmlNode* early_event_deadline_value = new wxXmlNode(wxXML_TEXT_NODE, wxT("early_event_deadline"), wxString::Format(wxT("%i"), node->early_event_deadline));
		node_early_event_deadline->AddChild(early_event_deadline_value);

		// late_event_deadline
		wxXmlNode* node_late_event_deadline = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("late_event_deadline"));
		wxXmlNode* late_event_deadline_value = new wxXmlNode(wxXML_TEXT_NODE, wxT("late_event_deadline"), wxString::Format(wxT("%i"), node->late_event_deadline));
		node_late_event_deadline->AddChild(late_event_deadline_value);

		// late_event_deadline
		wxXmlNode* node_time_reserve = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("time_reserve"));
		wxXmlNode* time_reserve_value = new wxXmlNode(wxXML_TEXT_NODE, wxT("time_reserve"), wxString::Format(wxT("%i"), node->time_reserve));
		node_time_reserve->AddChild(time_reserve_value);


		XmlGraphNode->AddChild(node_index);
		XmlGraphNode->AddChild(node_coords);
		XmlGraphNode->AddChild(node_early_event_deadline);
		XmlGraphNode->AddChild(node_late_event_deadline);
		XmlGraphNode->AddChild(node_time_reserve);

		XmlGraphInfo->AddChild(XmlGraphNode);
	}







	//add root node
	xml_file.SetRoot(XmlGraph);
	if (xml_file.Save(file))
	{
		m_curr_save_file = file;
		return true;
	}

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
