#include "Graph.h"

void Graph::AddNode(const wxPoint& coords, int index)
{
	Node *new_node = new Node;
	new_node->coords = coords;
	new_node->index = index;
	nodes.push_back(new_node);
	Rank();
}

void Graph::EditNode(const wxPoint& node_coords)
{
	// searching for the node
	std::vector<Node*>::iterator iter = nodes.begin();
	for (; iter != nodes.end(); iter++)
	{
		if (IsNode(node_coords, iter))break;
	}
	(*iter)->coords = node_coords;
	Rank();
}

void Graph::AddEdge(const Node* from, const Node* to, int weight)
{
	Edge* new_edge = new Edge;
	new_edge->from = from;
	new_edge->to = to;
	new_edge->weight = weight;
	
	// preventing duplication
	for (size_t i = 0; i < edges.size(); i++)
	{
		if (*edges[i] == *new_edge)
		{
			delete new_edge;
			return;
		}
	}

	edges.push_back(new_edge); 
}

void Graph::Erase(const wxPoint& coords)
{
	// deleting node
	for (std::vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		if (IsNode(coords, iter))
		{
			// delete all edges that connected to this node

			for (std::vector<Edge*>::iterator i = edges.begin(); i != edges.end();)
			{
				if ((*i)->to == *iter || (*i)->from == *iter)
				{
					delete (*i);
					i = edges.erase(i);
				}
				else i++;
			}
			delete *iter;
			nodes.erase(iter); // delete the node pointer
			return;
		}
	}
	Rank();

	// deleting edge
	for (std::vector<Edge*>::iterator iter = edges.begin(); iter != edges.end(); iter++)
	{
		if (IsEdge(coords, iter))
		{
			delete (*iter);
			edges.erase(iter);
			return;
		}
	}
}

void Graph::Erase(const Node* from, const Node* to)
{
	// todo: erase edge by begin node and end node
}

Node* Graph::GetNode(const wxPoint& node_coords)
{
	for (std::vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		if (IsNode(node_coords, iter))
		{
			return *iter;
		}
	}
	return nullptr;
}

Node* Graph::GetNode(size_t index)
{
	if (nodes.empty() || index >= nodes.size())return nullptr;
	else return nodes[index];
}

const Node* Graph::GetNode(size_t index) const
{
	if (nodes.empty() || index >= nodes.size())return nullptr;
	else return nodes[index];
}

Edge* Graph::GetEdge(const Node* from, const Node* to)
{
	
	for (size_t i = 0; i < edges.size(); i++)
	{
		if (edges[i]->from == from && edges[i]->to == to)
		{
			return edges[i];
		}
	}
	return nullptr;
}

Edge* Graph::GetEdge(size_t index)
{
	if (edges.empty() || index >= edges.size()) return nullptr;
	if (index < edges.size())return edges[index];
	else throw "Index out of range";
}

std::vector<Edge*> Graph::GetIncomingEdges(const Node* in)
{
	std::vector<Edge*> result;
	for (std::vector<Edge*>::iterator iter = edges.begin(); iter < edges.end(); iter++)
	{
		if ((*iter)->to == in)result.push_back(*iter);
	}

	return result;
}

void Graph::SetEdgeWeight(const Node* from, const Node* to, int weight)
{

}

bool Graph::Empty()
{
	if (nodes.empty())
	{
		return true;
	}
	return false;
}

void Graph::Rank()
{
	std::sort(nodes.begin(), nodes.end(),
		[](const Node* node1, const Node* node2)
		{
			return node1->index < node2->index;
		}
	);
}

size_t Graph::GetNodeAmount() const
{
	return nodes.size();
}

size_t Graph::GetEdgeAmount() const
{
	return edges.size();
}

void Graph::Clear()
{
	for (size_t i = 0; i < edges.size(); i++)
	{
		delete edges[i];
	}
	for (size_t i = 0; i < nodes.size(); i++)
	{
		delete nodes[i];
	}

	nodes.clear();
	edges.clear();
}

bool Graph::Contain(int node_index)
{
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->index == node_index) return true;
	}

	return false;

}

int Graph::MaxNodeIndex()
{
	if (!nodes.empty())
	{
		Node* node = nodes[0];
		for (std::vector<Node*>::iterator iter = nodes.begin()+1; iter < nodes.end(); iter++)
		{
			if (node->index < (*iter)->index)
			{
				node = *iter;
			}
		}

		return node->index;
	}
	return -1; // the index of the first node will be 0
}

bool Graph::IsInsideNode(const wxPoint& pt)
{
	for (std::vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		if (IsNode(pt, iter))
		{
			return true;
		}
	}
	return false;
}

bool Graph::IsOnEdge(const wxPoint& pt)
{
	for (std::vector<Edge*>::iterator iter = edges.begin(); iter != edges.end(); iter++)
	{
		if (IsEdge(pt, iter))
		{
			return true;
		}
	}
	return false;
}

bool Graph::IsNode(const wxPoint& node_coords, std::vector<Node*>::iterator& iter)
{
	Node* node = *iter;


	if ((pow(((*node).coords).x - node_coords.x, 2) + pow(((*node).coords).y - node_coords.y, 2)) <= 900)
	{
		return true;
	}
	return false;
}


bool Graph::IsEdge(const wxPoint& click_coords, std::vector<Edge*>::iterator& iter)
{
	// calculating edge's borders
	const Node* from = (*iter)->from;
	const Node* to = (*iter)->to;

	wxPoint vector((to->coords.x - from->coords.x), (to->coords.y - from->coords.y));
	double d = sqrt(pow(to->coords.x - from->coords.x, 2) + pow(to->coords.y - from->coords.y, 2));

	// normalized vector
	double normalized_x = vector.x / d;
	double normalized_y = vector.y / d;

	// the beginning
	wxPoint buffer;
	buffer.x = from->coords.x + 30 * normalized_x;
	buffer.y = from->coords.y + 30 * normalized_y;

	wxPoint point_A;
	point_A.x = buffer.x + 7 * (normalized_y);
	point_A.y = buffer.y + 7 * (-normalized_x);
	wxPoint point_B;
	point_B.x = buffer.x - 7 * (normalized_y);
	point_B.y = buffer.y - 7 * (-normalized_x);

	// the end
	buffer.x = to->coords.x - 30 * normalized_x;
	buffer.y = to->coords.y - 30 * normalized_y;

	wxPoint point_C;
	point_C.x = buffer.x + 7 * (normalized_y);
	point_C.y = buffer.y + 7 * (-normalized_x);
	wxPoint point_D;
	point_D.x = buffer.x - 7 * (normalized_y);
	point_D.y = buffer.y - 7 * (-normalized_x);

	// checking the place of the click	
	// order of traversal: A B D C
	auto product = [](const wxPoint* pt, const wxPoint* A, const wxPoint* B) {
		return (B->x - A->x) * (pt->y - A->y) - (B->y - A->y) * (pt->x - A->x);
	};

	if (product(&click_coords, &point_A, &point_B) < 0
		&& product(&click_coords, &point_B, &point_D) < 0
		&& product(&click_coords, &point_D, &point_C) < 0
		&& product(&click_coords, &point_C, &point_A) < 0)
	{
		return true;
	}
	return false;
}

Graph::~Graph()
{
	this->Clear();
}
