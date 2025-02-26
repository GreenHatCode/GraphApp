#include "DrawingPanel.h"

BEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
	EVT_PAINT(DrawingPanel::OnPaint)
	EVT_LEFT_DCLICK(DrawingPanel::OnLeftDClick)
	EVT_MOTION(DrawingPanel::OnMove)
END_EVENT_TABLE()


DrawingPanel::DrawingPanel(wxWindow* parent, wxWindowID winid)
	:wxPanel(parent, winid)
{
	SetDoubleBuffered(true);
}

void DrawingPanel::OnLeftDClick(wxMouseEvent& evt)
{
	switch (m_drawing_regime)
	{
	case DrawingPanel::STANDARD_CURSOR:
		// do nothing
		break;
	case DrawingPanel::ADD_NODE:
	{
		wxNumberEntryDialog* dlg = new wxNumberEntryDialog(
			this,
			wxT("Set the index of the node. Remember that \nthe node index is unique number."), 
			wxT("Enter a number:"),
			wxT("Set node index"), 
			m_graph.MaxNodeIndex() + 1, 
			std::numeric_limits<int>::min(),
			std::numeric_limits<int>::max());

		if (dlg->ShowModal() == wxID_OK)
		{
			if (m_graph.Contain(dlg->GetValue()))
			{
				if(m_dupl_warning)wxLogWarning("You can't add node with index %i, because it is already exist.", dlg->GetValue());
			}
			else 
			{
				m_graph.AddNode(evt.GetPosition(), dlg->GetValue());
				Refresh();
			}
		}
	}
		break;
	case DrawingPanel::ADD_EDGE:

		// select begin Node
		if (m_graph.IsInsideNode(evt.GetPosition()) && m_selected_begin_node == nullptr)
		{
			m_selected_begin_node = m_graph.GetNode(evt.GetPosition());
			Refresh();
		}
		// select end Node and add edge
		if (m_graph.IsInsideNode(evt.GetPosition()) && m_selected_begin_node != nullptr)
		{
			if (m_graph.GetNode(evt.GetPosition()) != m_selected_begin_node)// preventing chosing the same node
			{
				wxNumberEntryDialog* dlg = new wxNumberEntryDialog(
				this,
					wxT("Set the weight of the edge. Remember that \nthe edge weight can be only integer."),
					wxT("Enter a number:"),
					wxT("Set edge weight"),
					0,
					std::numeric_limits<int>::min(),
					std::numeric_limits<int>::max());

				if (dlg->ShowModal() == wxID_OK)
				{
					m_graph.AddEdge(m_selected_begin_node, m_graph.GetNode(evt.GetPosition()), dlg->GetValue());
					m_selected_begin_node = nullptr;
					Refresh();
				}
			}
		}
		break;
	case DrawingPanel::DELETE_NODE_OR_EDGE:
		m_graph.Erase(evt.GetPosition());
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
	for (size_t k = 0; k < m_graph.GetEdgeAmount(); k++)
	{
		DrawEdge(m_graph.GetEdge(k));
	}
	// redrawing all existing nodes
	for (size_t i = 0; i < m_graph.GetNodeAmount(); i++)
	{
		DrawNode(m_graph.GetNode(i));
	}

}

void DrawingPanel::OnMove(wxMouseEvent& evt)
{
	// calls when cusros moves
	
	// if cursor is inside node borders
	if (m_graph.IsInsideNode(evt.GetPosition()) && m_drawing_regime == DrawingPanel::STANDARD_CURSOR)
	{
		if (evt.m_leftDown)  // moving the node
		{
			SetCursor(wxCURSOR_SIZING);
			m_graph.EditNode(evt.GetPosition());
			Refresh();
		}
		else SetCursor(wxCURSOR_DEFAULT);
	}
	else if ((m_graph.IsOnEdge(evt.GetPosition()) || m_graph.IsInsideNode(evt.GetPosition())) && m_drawing_regime == DrawingPanel::DELETE_NODE_OR_EDGE)
	{
	// changing cursor in delete mode
	SetCursor(wxCURSOR_HAND);
	}
	else SetCursor(wxCURSOR_DEFAULT);
}

void DrawingPanel::OnClear()
{
	m_graph.Clear();
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

void DrawingPanel::Print(wxDC& dc, int pageNum, wxSize dc_size)
{
	if (m_graph.Empty())return;

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
	int x_min = m_graph.GetNode(0)->coords.x;
	int y_min = m_graph.GetNode(0)->coords.y;

	// search for x_min and y_min
	for (size_t i = 1; i < m_graph.GetNodeAmount(); i++)
	{
		if (x_min > m_graph.GetNode(i)->coords.x)
			x_min = m_graph.GetNode(i)->coords.x;

		if (y_min > m_graph.GetNode(i)->coords.y)
			y_min = m_graph.GetNode(i)->coords.y;
	}

	// this value determines how far we should move our graph drawing to the left top corner of the sheet of paper
	wxPoint diff(0 - x_min + node_radius + margin, 0 - y_min + node_radius + margin);

	// drawing edges
	std::vector<Node> out_of_range_nodes;
	for (size_t k = 0; k < m_graph.GetEdgeAmount(); k++)
	{
		Node from = *(*m_graph.GetEdge(k)).from;
		Node to = *(*m_graph.GetEdge(k)).to;
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
		edge_weight_text << (*m_graph.GetEdge(k)).weight;
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
	for (size_t i = 0; i < m_graph.GetNodeAmount(); i++)
	{
		Node node = *(m_graph.GetNode(i));

		node.coords += diff; // nove the node

		int circle_radius = 30;
		dc.DrawCircle(node.coords, circle_radius);
		dc.DrawLine(wxPoint(node.coords.x, node.coords.y - circle_radius), wxPoint(node.coords.x, node.coords.y + circle_radius)); // vertical line
		dc.DrawLine(wxPoint(node.coords.x - circle_radius, node.coords.y), wxPoint(node.coords.x + circle_radius, node.coords.y)); // horizontal line

		// drawing node indes in left bottom circle sector
		wxString str;
		str << node.index;
		wxSize str_width = dc.GetTextExtent(str);
		dc.DrawText(str, node.coords.x - circle_radius / 2 - str_width.x / 2, node.coords.y + 3);
	}
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

	// drawing node indes in left bottom circle sector
	wxString str;
	str << (*node).index;
	wxSize str_width = dc.GetTextExtent(str);
	dc.DrawText(str, (*node).coords.x - circle_radius / 2 - str_width.x / 2, (*node).coords.y + 3);

	dc.SetPen(wxNullPen);
}

void DrawingPanel::DrawEdge(const Edge* edge)
{
	wxClientDC dc(this);
	wxPen pen;
	if (m_colour_scheme == ColourSchemes::COLOURED)pen.SetColour(*wxWHITE);
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
