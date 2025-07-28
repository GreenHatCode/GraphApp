#include "DrawingPanel.h"
#include "ProcessGraph/ProcessGraphDialog.h"

enum {
	ID_EDIT_NODE,
	ID_DELETE_NODE,
	ID_EDIT_EDGE,
	ID_TURN_AROUND_EDGE,
	ID_DELETE_EDGE,
	ID_ADD_NEW_NODE,
};

BEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
	EVT_PAINT(DrawingPanel::OnPaint)
	EVT_RIGHT_UP(DrawingPanel::OnRightUp)
	EVT_LEFT_UP(DrawingPanel::OnLeftUp)
	EVT_MOTION(DrawingPanel::OnMove)
	EVT_MENU(ID_EDIT_NODE, DrawingPanel::OnEditNode)
	EVT_MENU(ID_DELETE_NODE, DrawingPanel::OnDeleteNode)
	EVT_MENU(ID_EDIT_EDGE, DrawingPanel::OnEditEdge)
	EVT_MENU(ID_TURN_AROUND_EDGE, DrawingPanel::OnTurnAroundEdge)
	EVT_MENU(ID_DELETE_EDGE, DrawingPanel::OnDeleteEdge)
	EVT_MENU(ID_ADD_NEW_NODE, DrawingPanel::OnAddNewNode)
END_EVENT_TABLE()


DrawingPanel::DrawingPanel(wxWindow* parent, wxWindowID winid)
	:wxPanel(parent, winid)
{
	SetDoubleBuffered(true);
	m_graph = new Graph([this](){
		this->OnGraphModified();
	});
	m_graph_processor = new ProcessGraph(m_graph, this);
}

void DrawingPanel::AddNewNode(const wxPoint &node_coords)
{
	// on windows it works normally with std::numeric_limits<int>
	// but on linux, it doesn't render spin buttons
	// if the max number is longer than 5 chars (inluding '-')
	wxNumberEntryDialog* dlg = new wxNumberEntryDialog(
		this,
		wxT("Set the index of the node. Remember that \nthe node index is unique number."), 
		wxT("Enter a number:"),
		wxT("Set node index"), 
		m_graph->MaxNodeIndex() + 1, 
		-9999,
		99999);

	if (dlg->ShowModal() == wxID_OK)
	{
		if (m_graph->Contain(dlg->GetValue()))
		{
			if(m_dupl_warning)wxLogWarning("You can't add node with index %i, because it is already exist.", dlg->GetValue());
		}
		else 
		{
			m_graph->AddNode(node_coords, dlg->GetValue());
			Refresh();
		}
	}
}

void DrawingPanel::AddNewEdge(const Node* node_from, const Node* node_to)
{
	// on windows it works normally with std::numeric_limits<int>
	// but on linux, it doesn't render spin buttons
	// if the max number is longer than 5 chars (inluding '-')		
	wxNumberEntryDialog* dlg = new wxNumberEntryDialog(
	this,
		wxT("Set the weight of the edge. Remember that \nthe edge weight can be only integer."),
		wxT("Enter a number:"),
		wxT("Set edge weight"),
		0,
		-9999,
		99999);

	if (dlg->ShowModal() == wxID_OK)
	{
		m_graph->AddEdge(node_from, node_to, dlg->GetValue());
		m_selected_begin_node = nullptr;
		Refresh();
	}
}

void DrawingPanel::OnGraphModified()
{
	if (m_dynamic_graph_processing)m_graph_processor->DoProcess(false);
}

void DrawingPanel::OnRightUp(wxMouseEvent &evt)
{
	wxMenu* m_context_menu = nullptr;
	m_context_menu = new wxMenu();

	if(m_graph->IsInsideNode(evt.GetPosition()))
	{
		// node
		m_context_menu->Append(ID_EDIT_NODE, "Edit node");
		m_context_menu->Append(ID_DELETE_NODE, "Delete node");
	}
	else if (m_graph->IsOnEdge(evt.GetPosition()))
	{
		// edge
		m_context_menu->Append(ID_EDIT_EDGE, "Edit edge");
		m_context_menu->Append(ID_TURN_AROUND_EDGE, "Turn around"); // swap begin and end nodes in the edge
		m_context_menu->Append(ID_DELETE_EDGE, "Delete edge");
	}
	else
	{
		// empty area
		m_context_menu->Append(ID_ADD_NEW_NODE, "Add node");	
	}

	m_context_menu_click_coords = evt.GetPosition();
	PopupMenu(m_context_menu, evt.GetPosition());
}

void DrawingPanel::OnLeftUp(wxMouseEvent &evt)
{
	switch (m_drawing_regime)
	{
	case DrawingPanel::STANDARD_CURSOR:
		// do nothing
		break;
	case DrawingPanel::ADD_NODE:
	{
		AddNewNode(evt.GetPosition());
	}
		break;
	case DrawingPanel::ADD_EDGE:

		// select begin Node
		if (m_graph->IsInsideNode(evt.GetPosition()) && m_selected_begin_node == nullptr)
		{
			m_selected_begin_node = m_graph->GetNode(evt.GetPosition());
			Refresh();
		}
		// select end Node and add edge
		if (m_graph->IsInsideNode(evt.GetPosition()) && m_selected_begin_node != nullptr)
		{
			if (m_graph->GetNode(evt.GetPosition()) != m_selected_begin_node)// preventing chosing the same node
			{
				AddNewEdge(m_selected_begin_node, m_graph->GetNode(evt.GetPosition()));
			}
		}
		break;
	case DrawingPanel::DELETE_NODE_OR_EDGE:
		m_graph->Erase(evt.GetPosition());
		Refresh();
		break;
	default:
		break;
	}

}

void DrawingPanel::OnPaint(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	wxPen pen;

	if (m_colour_scheme == ColourSchemes::COLOURED)
	{
		pen.SetColour(*wxBLACK);
		dc.SetBackground(*wxWHITE);
	}
	else
	{
		pen.SetColour(*wxBLACK);
		dc.SetBackground(*wxBLUE);
	}
	pen.SetWidth(2);

	
	dc.SetPen(pen);
	
	// redrawing all existing edges
	for (size_t k = 0; k < m_graph->GetEdgeAmount(); k++)
	{
		DrawEdge(m_graph->GetEdge(k));
	}
	// redrawing all existing nodes
	for (size_t i = 0; i < m_graph->GetNodeAmount(); i++)
	{
		DrawNode(m_graph->GetNodeByIndexInArray(i));
	}

}

void DrawingPanel::OnMove(wxMouseEvent& evt)
{
	// calls when cusros moves
	
	// if cursor is inside node borders
	if (m_graph->IsInsideNode(evt.GetPosition()) && m_drawing_regime == DrawingPanel::STANDARD_CURSOR)
	{
		if (evt.m_leftDown)  // moving the node
		{
			SetCursor(wxCURSOR_SIZING);
			m_graph->EditNode(evt.GetPosition());
			Refresh();
		}
		else SetCursor(wxCURSOR_DEFAULT);
	}
	else if ((m_graph->IsOnEdge(evt.GetPosition()) || m_graph->IsInsideNode(evt.GetPosition())) && m_drawing_regime == DrawingPanel::DELETE_NODE_OR_EDGE)
	{
		// changing cursor in delete mode
		SetCursor(wxCURSOR_HAND);
	}
	else SetCursor(wxCURSOR_DEFAULT);
}

void DrawingPanel::OnEditNode(wxCommandEvent &evt)
{
	// on windows it works normally with std::numeric_limits<int>
	// but on linux, it doesn't render spin buttons
	// if the max number is longer than 5 chars (inluding '-')
	wxNumberEntryDialog* dlg = new wxNumberEntryDialog(
		this,
		wxT("Edit the index of the node. Remember that \nthe node index is unique number."), 
		wxT("Enter a number:"),
		wxT("Set node index"), 
		m_graph->GetNode(m_context_menu_click_coords)->index,
		-9999,
		99999);

	if (dlg->ShowModal() == wxID_OK)
	{
		if (m_graph->Contain(dlg->GetValue()))
		{
			if(m_dupl_warning)
				wxLogWarning("You cannot set such index %i because a node with such index already exists.", dlg->GetValue());
		}
		else 
		{
			m_graph->EditNode(m_context_menu_click_coords, dlg->GetValue());
			Refresh();
		}
	}
}

void DrawingPanel::OnDeleteNode(wxCommandEvent &evt)
{
	m_graph->Erase(m_context_menu_click_coords);
	Refresh();
}

void DrawingPanel::OnEditEdge(wxCommandEvent &evt)
{
	// on windows it works normally with std::numeric_limits<int>
	// but on linux, it doesn't render spin buttons
	// if the max number is longer than 5 chars (inluding '-')
	wxNumberEntryDialog* dlg = new wxNumberEntryDialog(
		this,
		wxT("Edit the weight of the edge.  Remember that \nthe edge weight can be only integer."), 
		wxT("Enter a number:"),
		wxT("Set edge weight"), 
		m_graph->GetEdge(m_context_menu_click_coords)->weight,
		-9999,
		99999);

	if (dlg->ShowModal() == wxID_OK)
	{
		m_graph->GetEdge(m_context_menu_click_coords)->weight = dlg->GetValue();
		Refresh();
	}
}

void DrawingPanel::OnTurnAroundEdge(wxCommandEvent &evt)
{
	m_graph->TurnAroundEdge(m_context_menu_click_coords);
	Refresh();
}

void DrawingPanel::OnDeleteEdge(wxCommandEvent &evt)
{
	m_graph->Erase(m_context_menu_click_coords);
	Refresh();
}

void DrawingPanel::OnAddNewNode(wxCommandEvent &evt)
{
	AddNewNode(m_context_menu_click_coords);
}

DrawingPanel::~DrawingPanel()
{
	delete m_graph;
	delete m_graph_processor;
}

void DrawingPanel::OnClear()
{
	m_graph->Clear();
	Refresh();
}

void DrawingPanel::SetDrawingRegime(DrawingRegimes regime)
{
	m_drawing_regime = regime;
	// clearing temp vars for unused regimes

	if (m_drawing_regime != DrawingPanel::ADD_EDGE)
	{
		m_selected_begin_node = nullptr;
	}

	Refresh();
}

void DrawingPanel::SetColourScheme(ColourSchemes scheme)
{
	m_colour_scheme = scheme;

	if (m_colour_scheme == ColourSchemes::COLOURED)
	{
		SetBackgroundColour(*wxBLUE);
	}
	else SetBackgroundColour(*wxWHITE);
	Refresh();
}

void DrawingPanel::ShowNodeDuplicationWarning(bool show)
{
	m_dupl_warning = show;
}

void DrawingPanel::SetDynamicGraphProcessing(bool value)
{
	m_dynamic_graph_processing = value;
}

void DrawingPanel::Print(wxDC& dc, int pageNum, wxSize dc_size)
{
	if (m_graph->Empty())return;

	// setting colours
	wxPen pen;
	pen.SetColour(*wxBLACK);
	pen.SetWidth(2);
	dc.SetPen(pen);
	dc.SetBackground(*wxWHITE);

	// We are looking for the minimum coords of the rectangle which we can draw around the graph.
	// Here we are looking for the coords of a rectangle that can contain the graph.
	// Or we can say that we are looking for coords 
	// to draw a border around the graph with a given margin.

	int margin = 5; // 5px
	int node_radius = 30;
	int x_min = m_graph->GetNodeByIndexInArray(0)->coords.x;
	int y_min = m_graph->GetNodeByIndexInArray(0)->coords.y;

	// search for x_min and y_min
	for (size_t i = 1; i < m_graph->GetNodeAmount(); i++)
	{
		if (x_min > m_graph->GetNodeByIndexInArray(i)->coords.x)
			x_min = m_graph->GetNodeByIndexInArray(i)->coords.x;

		if (y_min > m_graph->GetNodeByIndexInArray(i)->coords.y)
			y_min = m_graph->GetNodeByIndexInArray(i)->coords.y;
	}

	// this value determines how far we should move our graph drawing to the left top corner of the sheet of paper
	wxPoint diff(0 - x_min + node_radius + margin, 0 - y_min + node_radius + margin);

	// drawing edges
	std::vector<Node> out_of_range_nodes;
	for (size_t k = 0; k < m_graph->GetEdgeAmount(); k++)
	{
		Node from = *(*m_graph->GetEdge(k)).from;
		Node to = *(*m_graph->GetEdge(k)).to;
		from.coords += diff; // nove the node
		to.coords += diff; // nove the node

		// check if the node coords are in the range
		if (std::count(out_of_range_nodes.begin(), out_of_range_nodes.end(), from) == 0 && (from.coords.x >= dc_size.x || from.coords.y >= dc_size.y))
		{
			out_of_range_nodes.push_back(from);
		}
		if (std::count(out_of_range_nodes.begin(), out_of_range_nodes.end(), to) == 0 && (to.coords.x >= dc_size.x || to.coords.y >= dc_size.y))
		{
			out_of_range_nodes.push_back(to);
		}


		// drawing the edge
		dc.DrawLine(from.coords, to.coords);

		// calculating trianle coords
		wxPoint vector((to.coords.x - from.coords.x), (to.coords.y - from.coords.y));
		double d = sqrt(pow(to.coords.x - from.coords.x, 2) + pow(to.coords.y - from.coords.y, 2));

		// normalized vector
		double normalized_x = vector.x / d;
		double normalized_y = vector.y / d;

		wxPoint triangle_head; // the first triangle node
		triangle_head.x = to.coords.x - 30 * normalized_x;
		triangle_head.y = to.coords.y - 30 * normalized_y;


		wxPoint triangle_base_center;
		triangle_base_center.x = to.coords.x - 45 * normalized_x;
		triangle_base_center.y = to.coords.y - 45 * normalized_y;

		wxPoint triangle_base_A; // the second triangle node
		triangle_base_A.x = triangle_base_center.x - 10 * (normalized_y);
		triangle_base_A.y = triangle_base_center.y - 10 * (-normalized_x);
		wxPoint triangle_base_B; // the third triangle node
		triangle_base_B.x = triangle_base_center.x - 10 * (-normalized_y);
		triangle_base_B.y = triangle_base_center.y - 10 * (normalized_x);

		wxPointList* points = new wxPointList;
		points->Insert(&triangle_head);
		points->Insert(&triangle_base_A);
		points->Insert(&triangle_base_B);

		dc.DrawPolygon(points); // drawing triangle


		// drawing edge weight
		wxPoint midpoint = (from.coords + to.coords) / 2;
		midpoint.y += 10;
		wxString edge_weight_text;
		edge_weight_text << (*m_graph->GetEdge(k)).weight;
		wxSize str_width = dc.GetTextExtent(edge_weight_text);

		dc.SetTextForeground(*wxBLACK);

		wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
		dc.SetFont(font);


		dc.DrawText(edge_weight_text, midpoint);
		
	}

	// print a warning about all nodes 
	// that cannot be drawn on the current sheet of paper
	if (!out_of_range_nodes.empty())
	{
		if (out_of_range_nodes.size() > 1)
		{
			wxString ms = "The nodes with indexes ";
			for (std::vector<Node>::iterator iter = out_of_range_nodes.begin(); iter < out_of_range_nodes.end(); iter++)
			{
				ms += wxString::Format("%i, ", (*iter).index);
			}
			ms.erase(ms.size() - 2, 2);
			ms += " have coordinates larger than the current sheet of paper. Select a larger sheet of paper or move the nodes closer to the top left corner of the drawing area.";
			wxLogWarning(ms);
		}
		else
		{
			wxLogWarning("The node with index %i has coordinates larger than the current sheet of paper. Select a larger sheet of paper or move the node closer to the top left corner of the drawing area.", out_of_range_nodes[0].index);
		}
		return;
	}



	// drawing nodes
	for (size_t i = 0; i < m_graph->GetNodeAmount(); i++)
	{
		Node node = *(m_graph->GetNodeByIndexInArray(i));

		node.coords += diff; // nove the node

		int circle_radius = 30;
		dc.DrawCircle(node.coords, circle_radius);
		dc.DrawLine(wxPoint(node.coords.x, node.coords.y - circle_radius), wxPoint(node.coords.x, node.coords.y + circle_radius)); // vertical line
		dc.DrawLine(wxPoint(node.coords.x - circle_radius, node.coords.y), wxPoint(node.coords.x + circle_radius, node.coords.y)); // horizontal line

		// drawing node index in left bottom circle sector
		wxString str;
		str << node.index;
		wxSize str_size = dc.GetTextExtent(str);
		dc.DrawText(str, node.coords.x - circle_radius / 2 - str_size.x / 2, node.coords.y + 3);

		if (node.early_event_deadline >= 0)
		{
			// drawing node t_early in left top circle sector
			str.clear();
			str << node.early_event_deadline;
			str_size = dc.GetTextExtent(str);
			dc.DrawText(str, node.coords.x - circle_radius / 2 - str_size.x / 2, node.coords.y - str_size.y - 3);
		}
		if (node.late_event_deadline >= 0)
		{
			// drawing node t_late in right bottom circle sector
			str.clear();
			str << node.late_event_deadline;
			str_size = dc.GetTextExtent(str);
			dc.DrawText(str, node.coords.x + circle_radius / 2 - str_size.x / 2 - 3, node.coords.y + 3);
		}
		if (node.time_reserve >= 0)
		{
			// drawing node time_reserve in right bottom circle sector
			str.clear();
			str << node.time_reserve;
			str_size = dc.GetTextExtent(str);
			dc.DrawText(str, node.coords.x + circle_radius / 2 - str_size.x / 2 - 3, node.coords.y - str_size.y - 3);
		}

	}
}

Graph* DrawingPanel::GetGraph()
{
	return m_graph;
}

void DrawingPanel::SetGraph(Graph* graph_ptr)
{
	m_graph->Clear();
	delete m_graph;
	m_graph = graph_ptr;
	m_graph_processor->SetGraph(m_graph);
	m_graph->RegisterChangeListener([this](){
		this->OnGraphModified();
	});
	Refresh();
}

void DrawingPanel::AddNewEdge(int node_from_index, int node_to_index, int weight)
{
	m_graph->AddEdge(m_graph->GetNodeByIndex(node_from_index), m_graph->GetNodeByIndex(node_to_index), weight);
	Refresh();
}

bool DrawingPanel::ProcessCurrentGraph()
{
    return m_graph_processor->DoProcess(); // create an object of ProcessGraph and process the graph
}

void DrawingPanel::BuildAdjacencyMatrix()
{
	if(!m_graph_processor->BuildAdjacencyMatrix()) 
		wxMessageBox(wxT("Can't build adjacency matrix."), wxT("Build matrix error"), wxICON_ERROR);
}

void DrawingPanel::BuildIncidenceMatrix()
{
	if(!m_graph_processor->BuildIncidenceMatrix()) 
		wxMessageBox(wxT("Can't build incidence matrix."), wxT("Build matrix error"), wxICON_ERROR);
}

void DrawingPanel::BuildKirchhoffMatrix()
{
	if(!m_graph_processor->BuildKirchhoffMatrix()) 
		wxMessageBox(wxT("Can't build Kirchhoff matrix."), wxT("Build matrix error"), wxICON_ERROR);
}

void DrawingPanel::SearchPathDijkstra()
{
	if(!m_graph_processor->SearchPathDijkstra()) 
		wxMessageBox(wxT("Can't search the shortest path using Dijkstra's algorithm."), wxT("Search path error"), wxICON_ERROR);
}

void DrawingPanel::SearchPathBellmanFord()
{
	if(!m_graph_processor->SearchPathBellmanFord()) 
		wxMessageBox(wxT("Can't search the shortest path using Bellman-Ford algorithm."), wxT("Search path error"), wxICON_ERROR);
}

void DrawingPanel::CircleLayout()
{
	if(m_graph->Empty())wxMessageBox(wxT("The graph is empty. Can't use layout."), wxT("Graph layout error"), wxICON_ERROR);

	int total_nodes_amount = m_graph->GetNodeAmount();
	int node_radius = 30;
	int centerX = this->GetSize().x / 2;
	int centerY = this->GetSize().y / 2;


	// compute the radius
	double angle_step = 2 * M_PI / std::max(1, total_nodes_amount - 1);
	double min_radius = node_radius / (2 * std::sin(angle_step / 2));
	double curr_radius = std::min(this->GetSize().x, this->GetSize().y) / 2 - 50; // 50px is margin between nodes
	double radius = std::max(min_radius, curr_radius);

	for (int node_index = 0; node_index < total_nodes_amount - 1; node_index++)
	{
		double angle = 2 * M_PI * node_index / (total_nodes_amount - 1);
		int x = centerX + radius * std::cos(angle);
		int y = centerY + radius * std::sin(angle);
		m_graph->GetNodeByIndexInArray(node_index)->coords = wxPoint(x, y);
	}
	m_graph->GetNodeByIndexInArray(m_graph->GetNodeAmount() - 1)->coords = wxPoint(centerX, centerY);



	Refresh();
}

void DrawingPanel::TreeLayout()
{
	if(m_graph->Empty())wxMessageBox(wxT("The graph is empty. Can't use layout."), wxT("Graph layout error"), wxICON_ERROR);



}

void DrawingPanel::DrawNode(const Node* node)
{
	wxClientDC dc(this);

	wxPen pen;
	if (node == m_selected_begin_node)pen.SetColour(wxColour(255, 11, 249));
	else pen.SetColour(*wxBLACK);
	pen.SetWidth(2);
	

	dc.SetPen(pen);
	int circle_radius = 30;
	dc.DrawCircle((*node).coords, circle_radius);
	dc.DrawLine(wxPoint((*node).coords.x, (*node).coords.y - circle_radius), wxPoint((*node).coords.x, (*node).coords.y + circle_radius)); // vertical line
	dc.DrawLine(wxPoint((*node).coords.x - circle_radius, (*node).coords.y), wxPoint((*node).coords.x + circle_radius, (*node).coords.y)); // horizontal line

	// drawing node index in left bottom circle sector
	wxString str;
	str << (*node).index;
	wxSize str_size = dc.GetTextExtent(str);
	dc.DrawText(str, (*node).coords.x - circle_radius / 2 - str_size.x / 2, (*node).coords.y + 3);

	if ((*node).early_event_deadline >= 0)
	{
		// drawing node t_early in left top circle sector
		str.clear();
		str << (*node).early_event_deadline;
		str_size = dc.GetTextExtent(str);
		dc.DrawText(str, (*node).coords.x - circle_radius / 2 - str_size.x / 2, (*node).coords.y - str_size.y - 3);
	}
	if ((*node).late_event_deadline >= 0)
	{
		// drawing node t_late in right bottom circle sector
		str.clear();
		str << (*node).late_event_deadline;
		str_size = dc.GetTextExtent(str);
		dc.DrawText(str, (*node).coords.x + circle_radius / 2 - str_size.x / 2 - 3, (*node).coords.y + 3);
	}
	if ((*node).time_reserve >= 0)
	{
		// drawing node time_reserve in right bottom circle sector
		str.clear();
		str << (*node).time_reserve;
		str_size = dc.GetTextExtent(str);
		dc.DrawText(str, (*node).coords.x + circle_radius / 2 - str_size.x / 2 - 3, (*node).coords.y - str_size.y - 3);
	}



	dc.SetPen(wxNullPen);
}

void DrawingPanel::DrawEdge(const Edge* edge)
{
	wxClientDC dc(this);
	wxPen pen;
	if (edge->critical_path_edge) pen.SetColour(wxColour(245, 5, 5));
	else if (m_colour_scheme == ColourSchemes::COLOURED)pen.SetColour(*wxWHITE);
	else pen.SetColour(*wxBLACK);
	pen.SetWidth(2);




	dc.SetPen(pen);
	dc.DrawLine((*(edge->from)).coords, (*(edge->to)).coords);

	// calculating trianle coords
	const Node* from = (*edge).from;
	const Node* to = (*edge).to;

	wxPoint vector((to->coords.x - from->coords.x), (to->coords.y - from->coords.y));
	double d = sqrt(pow(to->coords.x - from->coords.x, 2) + pow(to->coords.y - from->coords.y, 2));
	
	// normalized vector
	double normalized_x = vector.x / d;
	double normalized_y = vector.y / d;
	
	wxPoint triangle_head; // the first triangle node
	triangle_head.x = to->coords.x - 30 * normalized_x;
	triangle_head.y = to->coords.y - 30 * normalized_y;


	wxPoint triangle_base_center;
	triangle_base_center.x = to->coords.x - 45 * normalized_x;
	triangle_base_center.y = to->coords.y - 45 * normalized_y;

	wxPoint triangle_base_A; // the second triangle node
	triangle_base_A.x = triangle_base_center.x - 10 * (normalized_y);
	triangle_base_A.y = triangle_base_center.y - 10 * (-normalized_x);
	wxPoint triangle_base_B; // the third triangle node
	triangle_base_B.x = triangle_base_center.x - 10 * (-normalized_y);
	triangle_base_B.y = triangle_base_center.y - 10 * (normalized_x);

	wxPointList *points = new wxPointList;
	points->Insert(&triangle_head);
	points->Insert(&triangle_base_A);
	points->Insert(&triangle_base_B);

	dc.DrawPolygon(points); // drawing triangle
	delete points;

	// drawing edge weight
	wxPoint midpoint = ((*(edge->from)).coords + (*(edge->to)).coords) / 2;
	midpoint.y += 10;
	wxString edge_weight_text;
	edge_weight_text << (*edge).weight;
	wxSize str_width = dc.GetTextExtent(edge_weight_text);
	

	if (m_colour_scheme == ColourSchemes::COLOURED)dc.SetTextForeground(*wxWHITE);
	else dc.SetTextForeground(*wxBLACK);

	wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	dc.SetFont(font);
	

	dc.DrawText(edge_weight_text, midpoint);

	dc.SetPen(wxNullPen);
}
