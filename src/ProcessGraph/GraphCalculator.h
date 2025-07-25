#pragma once
#include "Graph.h"
#include "ProcessGraph/Matrix/MatN.h"
#include <map>
#include <queue>
#include <unordered_map>
#include <limits>
#include <memory>

// This class provides methods to calculate some graph values.
// It does not perform data validation, look for it in the ProcessGraph header.
// It only performs calculations and returns non-user-readable results.

class GraphCalculator
{
public:
    GraphCalculator(Graph* ptr);

    const std::vector<int> GetEarlyEventDates() const { return m_T_early; };
    const std::vector<int> GetLateEventDate() const { return m_T_late; };
    const std::vector<int> GetTimeReserve() const { return m_Time_reserve; };
    const std::vector<Node*> GetCritPath() const { return m_crit_path; };
    const float GetComplexityFactor() const { return m_complexity_factor; }

    // calculation methods
    void CalculateEarlyEventDate();
    void CalculateLateEventDate();
    void CalculateTimeReserve();
    void CalculateComplexityFactor();
    void SearchCritPath();

    // build matrix methods
    // return false if can't build the matrix
    MatN BuildAdjacencyMat();
    MatN BuildIncidenceMat();
    MatN BuildKirchhoffMat();

    // seach the shortest path methods
    // returns false if can't search path
    wxString SeacrhShortestPathDijkstra(); // searches the shortest pathes and returns a message with them
    wxString SeacrhShortestPathBellmanFord(); // searches the shortest pathes and returns a message with them (works with negative edge weight)



private:
    Graph* m_graph_ptr = nullptr;

    // calculatoion data
    std::vector<int> m_T_early; // EARLY EVENT DATE
    std::vector<int> m_T_late; // LATE EVENT DATE
    std::vector<int> m_Time_reserve; // EVENT TIME RESERVE
    float m_complexity_factor = 0;
    std::vector<Node*> m_crit_path; // stores nodes that create a critical path

    // matrices
    std::unique_ptr<MatN> m_adjacency_matrix = nullptr;
    std::unique_ptr<MatN> m_incidence_matrix = nullptr;
    std::unique_ptr<MatN> m_kirchhoff_matrix = nullptr;
};