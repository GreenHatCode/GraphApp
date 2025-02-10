#pragma once
#include "wx/wx.h"
#include <vector>


struct Node
{
	wxPoint coords;
	int early_event_deadline = -1;
	int late_event_deadline = -1;
	int time_reserve = -1;
	int idex = -1;

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
	void EditNode(const wxPoint& node_coords, int idex = -1, int t_early = -1, int t_late = -1, int time_reserve = -1);
	void AddEdge(const Node* from, const Node* to, int weight = 0);
	void Erase(const wxPoint& coords); // erase node
	void Erase(const Node* from, const Node* to); // erase edge
	Node* GetNode(const wxPoint& node_coords);
	Node* GetNode(size_t index);
	Edge* GetEdge(const Node* from, const Node* to);
	Edge* GetEdge(size_t index);
	void SetEdgeWeight(const Node* from, const Node* to, int weight);
	

	size_t GetNodeAmount();
	size_t GetEdgeAmount();
	void Clear(); // clears all the graph

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

