#pragma once
#include "wx/wx.h"

// represents a square matrix with N rows and cols
class matN{
public:
    matN(int dimensions)
    {
        m_dimensions = dimensions;
        m_total_elements = dimensions * dimensions;
        m_matrix_array = std::make_unique<int[]>(m_total_elements); // fill matrix with 0
        for (size_t i = 0; i < m_total_elements; i++)
            m_matrix_array[i] = 0;
        
    }

private:
    int m_total_elements;
    int m_dimensions;
    std::unique_ptr<int[]> m_matrix_array = nullptr;
};