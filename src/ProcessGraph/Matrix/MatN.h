#pragma once
#include "wx/wx.h"

// represents a square matrix with N rows and cols
class MatN{
public:
    MatN(int dimensions)
    {
        m_dimensions = dimensions;
        m_total_elements = dimensions * dimensions;
        m_matrix_array = std::make_unique<int[]>(m_total_elements); // fill matrix with 0
        for (size_t i = 0; i < m_total_elements; i++)
            m_matrix_array[i] = 0;
        
    }

    int& At(int row, int col) // get an element by indices
    {
        assert(row >= 0 && row < m_dimensions);
        assert(col >= 0 && col < m_dimensions);
        return m_matrix_array[row * m_dimensions + col];
    }

    const wxString toWxString() const
    {
        wxString matrix_str;
        for (size_t i = 0; i < m_dimensions; i++)
        {
            for (size_t k = 0; k < m_dimensions; k++)
            {
                matrix_str.append(wxString::Format("%i ", m_matrix_array[i*m_dimensions + k]));
            }
            matrix_str.erase(matrix_str.end() - 1);
            matrix_str.append("\n");
            
        }
        matrix_str.erase(matrix_str.end() - 1);
        return matrix_str;
    }

private:
    int m_total_elements;
    int m_dimensions;
    std::unique_ptr<int[]> m_matrix_array = nullptr;
};