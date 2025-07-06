#pragma once
#include "Graph.h"
#include "ProcessGraph/Matrix/MatN.h"
#include <map>

// this class does only calculations
// it returns arrays and strings 
// not user readable results

class GraphCalculator
{
public:
    GraphCalculator(Graph* ptr);

    const std::vector<int> GetEarlyEventDates() const { return m_T_early; };
    const std::vector<int> GetLateEventDate() const { return m_T_late; };
    const std::vector<int> GetTimeReserve() const { return m_Time_reserve; };
    const std::vector<Node*> GetCritPath() const { return m_crit_path; };
    const float GetComplexityFactor() const { return m_complexity_factor; }
    const MatN GetAdjacencyMat() const { return *(m_adjacency_matrix); }
    const MatN GetIncidenceMat() const { return *(m_incidence_matrix); }

    // calculation methods
    void CalculateEarlyEventDate();
    void CalculateLateEventDate();
    void CalculateTimeReserve();
    void CalculateComplexityFactor();
    void SearchCritPath();

    // build matrix methods
    // return false if can't build the matrix
    void BuildAdjacencyMat();
    void BuildIncidenceMat();
    void BuildKirchhoffMat();

    // seach the shortest path methods
    // returns false if can't search path
    //bool SeacrhShortestPathDijkstra();
    //bool SeacrhShortestPathBellmanFord();



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
};