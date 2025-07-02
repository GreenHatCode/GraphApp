#pragma once
#include "Graph.h"
#include <map>

// this class does only calculations
// it returns arrays and strings 
// not user readable results

class GraphCalculator
{
public:
    GraphCalculator(Graph* ptr);

    std::vector<int> GetEarlyEventDates() { return m_T_early; };
    std::vector<int> GetLateEventDate() { return m_T_late; };
    std::vector<int> GetTimeReserve() { return m_Time_reserve; };
    std::vector<Node*> GetCritPath() { return m_crit_path; };
    double GetComplexityFactor() { return m_complexity_factor; }

    // calculation methods
    void CalculateEarlyEventDate();
    void CalculateLateEventDate();
    void CalculateTimeReserve();
    void CalculateComplexityFactor();
    void SearchCritPath();

private:
    Graph* m_graph_ptr = nullptr;

    // calculatoion data
    std::vector<int> m_T_early; // EARLY EVENT DATE
    std::vector<int> m_T_late; // LATE EVENT DATE
    std::vector<int> m_Time_reserve; // EVENT TIME RESERVE
    double m_complexity_factor = 0;
    std::vector<Node*> m_crit_path; // stores nodes that create a critical path



};