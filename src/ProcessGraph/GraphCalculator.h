#pragma once
#include "Graph.h"

// this class does only calculations
// it returns arrays and strings 
// not user readable results

class GraphCalculator
{
public:
    GraphCalculator(Graph* ptr);

    std::vector<int> GetEarlyEventDates();
    std::vector<int> GetEarlyEventDates();
    std::vector<int> GetEarlyEventDates();
    std::vector<Node*> GetCritPath();


private:
    Graph* m_graph_ptr = nullptr;

    // calculatoion data
    std::vector<int> m_T_early; // EARLY EVENT DATE
    std::vector<int> m_T_late; // LATE EVENT DATE
    std::vector<int> m_Time_reserve; // EVENT TIME RESERVE
    std::vector<Node*> m_crit_path; // stores nodes that create a critical path

    // calculation methods
    void CalculateEarlyEventDate();
    void CalculateLateEventDate();
    void CalculateTimeReserve();
    void SearchCritPath();

};