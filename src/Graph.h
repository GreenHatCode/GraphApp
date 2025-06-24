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
	// modify the graph
	void AddNode(const wxPoint& coords, int index, int early_event_deadline = -1, int late_event_deadline = -1, int time_reserve = -1);
	void EditNode(const wxPoint& node_coords);
	void EditNode(const wxPoint& node_coords, int index, int early_event_deadline = -1, int late_event_deadline = -1, int time_reserve = -1);
	void AddEdge(const Node* from, const Node* to, int weight = 0, bool critical_path = false);
	void Erase(const wxPoint& coords);
	void TurnAroundEdge(const wxPoint& coords);
	void Clear(); // clears all the graph

	Node* GetNode(const wxPoint& node_coords);
	Node* GetNode(size_t index);
	const Node* GetNode(size_t index) const;
	const std::vector<int> GetNodeIndices() const;
	Node* GetEdgeByNodeIndex(int index); // get node by its number (not index in vector)
	Edge* GetEdge(const Node* from, const Node* to);
	Edge* GetEdge(size_t index);
	Edge* GetEdge(const wxPoint& coords);
	const Edge* GetEdge(size_t index) const;
	std::vector<Edge*> GetIncomingEdges(const Node* in);
	
	bool Empty();
	void Rank(); // changes the order of the nodes in the array according to their idexes
	size_t GetNodeAmount() const;
	size_t GetEdgeAmount() const;
	
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

