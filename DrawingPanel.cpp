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
	switch (drawing_regime)
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
			0, 
			std::numeric_limits<int>::min(),
			std::numeric_limits<int>::max());

		if (dlg->ShowModal() == wxID_OK)
		{
			graph.AddNode(evt.GetPosition(), dlg->GetValue());
			Refresh();
		}
	}
		break;
	case DrawingPanel::ADD_EDGE:

		// select begin Node
		if (graph.IsInsideNode(evt.GetPosition()) && selected_begin_node == nullptr)
		{
			selected_begin_node = graph.GetNode(evt.GetPosition());
			Refresh();
		}
		// select end Node and add edge
		if (graph.IsInsideNode(evt.GetPosition()) && selected_begin_node != nullptr)
		{
			if (graph.GetNode(evt.GetPosition()) != selected_begin_node)// preventing chosing the same node
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
					graph.AddEdge(selected_begin_node, graph.GetNode(evt.GetPosition()), dlg->GetValue());
					Refresh();
				}
			}
		}
		break;
	case DrawingPanel::DELETE_NODE_OR_EDGE:
		graph.Erase(evt.GetPosition());
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

	if (colour_scheme == ColourScheme::COLOURED)
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
	for (size_t k = 0; k < graph.GetEdgeAmount(); k++)
	{
		DrawEdge(graph.GetEdge(k));
	}
	// redrawing all existing nodes
	for (size_t i = 0; i < graph.GetNodeAmount(); i++)
	{
		DrawNode(graph.GetNode(i));
	}

}

void DrawingPanel::OnMove(wxMouseEvent& evt)
{
	// calls when cusros moves
	
	// if cursor is inside node borders
	if (graph.IsInsideNode(evt.GetPosition()) && drawing_regime == DrawingPanel::STANDARD_CURSOR)
	{
		if (evt.m_leftDown)  // moving the node
		{
			SetCursor(wxCURSOR_SIZING);
			graph.EditNode(evt.GetPosition());
			Refresh();
		}
		else SetCursor(wxCURSOR_DEFAULT);
	}
	else if ((graph.IsOnEdge(evt.GetPosition()) || graph.IsInsideNode(evt.GetPosition())) && drawing_regime == DrawingPanel::DELETE_NODE_OR_EDGE)
	{
		// changing cursor in delete mode
		SetCursor(wxCURSOR_HAND);
	}
	else SetCursor(wxCURSOR_DEFAULT);
}

void DrawingPanel::OnClear()
{
	graph.Clear();
	Refresh();
}

void DrawingPanel::SetDrawingRegime(DrawingRegimes regime)
{
	drawing_regime = regime;
	//todo:add clearing temp vars for unused regimes

	if (drawing_regime != DrawingPanel::ADD_EDGE)
	{
		selected_begin_node = nullptr;
	}

	Refresh();
}

void DrawingPanel::SetColourScheme(ColourScheme scheme)
{
	colour_scheme = scheme;

	if (colour_scheme == ColourScheme::COLOURED)
	{
		SetBackgroundColour(*wxBLUE);
	}
	else SetBackgroundColour(*wxWHITE);
}

void DrawingPanel::PrintDrawing(wxDC& dc)
{
	wxPen pen;
	if (colour_scheme == ColourScheme::COLOURED)
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

	// drawing edges
	for (size_t k = 0; k < graph.GetEdgeAmount(); k++)
	{
		Edge* edge = graph.GetEdge(k);
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

		wxPointList* points = new wxPointList;
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


		if (colour_scheme == ColourScheme::COLOURED)dc.SetTextForeground(*wxWHITE);
		else dc.SetTextForeground(*wxBLACK);

		wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
		dc.SetFont(font);


		dc.DrawText(edge_weight_text, midpoint);
		
	}
	// drawing nodes
	for (size_t i = 0; i < graph.GetNodeAmount(); i++)
	{
		Node* node = graph.GetNode(i);
		int circle_radius = 30;
		dc.DrawCircle((*node).coords, circle_radius);
		dc.DrawLine(wxPoint((*node).coords.x, (*node).coords.y - circle_radius), wxPoint((*node).coords.x, (*node).coords.y + circle_radius)); // vertical line
		dc.DrawLine(wxPoint((*node).coords.x - circle_radius, (*node).coords.y), wxPoint((*node).coords.x + circle_radius, (*node).coords.y)); // horizontal line

		// drawing node indes in left bottom circle sector
		wxString str;
		str << (*node).index;
		wxSize str_width = dc.GetTextExtent(str);
		dc.DrawText(str, (*node).coords.x - circle_radius / 2 - str_width.x / 2, (*node).coords.y + 3);
	}
}

void DrawingPanel::DrawNode(const Node* node)
{
	wxClientDC dc(this);

	wxPen pen;
	if (node == selected_begin_node)pen.SetColour(wxColour(255, 11, 249));
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
	if (colour_scheme == ColourScheme::COLOURED)pen.SetColour(*wxWHITE);
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
	

	if (colour_scheme == ColourScheme::COLOURED)dc.SetTextForeground(*wxWHITE);
	else dc.SetTextForeground(*wxBLACK);

	wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	dc.SetFont(font);
	

	dc.DrawText(edge_weight_text, midpoint);

	dc.SetPen(wxNullPen);
}
