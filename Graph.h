#pragma once
#include "wx/wx.h"
#include <vector>


struct Node
{
	wxPoint coords;
	int early_event_deadline = -1;
	int late_event_deadline = -1;
	int time_reserve = -1;
	int index = -1;

	bool operator ==(Node right)
	{
		return this->coords == right.coords;
	}

};

struct Edge
{
	const Node* from = nullptr;
	const Node* to = nullptr;
	int weight;
	bool critical_path_edge = false;

	bool operator ==(Edge right)
	{
		return (this->from == right.from && this->to == right.to) || (this->from == right.to && this->to == right.from);
	}

	~Edge()
	{
		this->from = nullptr;
		this->to = nullptr;
	}
};

class Graph
{
public:
	void AddNode(const wxPoint& coords, int index);
	void EditNode(const wxPoint& node_coords);
	void AddEdge(const Node* from, const Node* to, int weight = 0);
	void Erase(const wxPoint& coords); // erase node
	void Erase(const Node* from, const Node* to); // erase edge
	Node* GetNode(const wxPoint& node_coords);
	Node* GetNode(size_t index);
	Edge* GetEdge(const Node* from, const Node* to);
	Edge* GetEdge(size_t index);
	std::vector<Edge*> GetIncomingEdges(const Node* in);
	void SetEdgeWeight(const Node* from, const Node* to, int weight);
	bool Empty();
	void Rank(); // changes the order of the nodes in the array according to their idexes

	size_t GetNodeAmount();
	size_t GetEdgeAmount();
	void Clear(); // clears all the graph
	bool Contain(int node_index); // searches for node with given index, if it exists return true
	int MaxNodeIndex();

	// for drawing
	bool IsInsideNode(const wxPoint& pt);
	bool IsOnEdge(const wxPoint& pt);

	~Graph();
private:
	std::vector<Node*> nodes;
	std::vector<Edge*> edges;

	
	bool IsNode(const wxPoint& node_coords, std::vector<Node*>::iterator& iter); // checks if the click is made inside node borders
	bool IsEdge(const wxPoint& click_coords, std::vector<Edge*>::iterator& iter); // checks if the click is made inside edge borders
};

