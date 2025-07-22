#pragma once
#include "wx/wx.h"

// represents a matrix with N rows and M cols
class MatN{
public:
    MatN(int rows, int cols)
    {
        assert(rows >= 0);
        assert(cols >= 0);
        this->rows = rows;
        this->cols = cols;
        // fill matrix with 0
        for (size_t i = 0; i < rows * cols; i++)
            m_matrix_array.push_back(0);
        
    }

    int& At(int row, int col) // get an element by indices
    {
        assert(row >= 0 && row < rows);
        assert(col >= 0 && col < cols);
        return m_matrix_array[row * cols + col];
    }

    const wxString toWxString() const
    {
        wxString matrix_str;
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t k = 0; k < cols; k++)
            {
                matrix_str.append(wxString::Format("%i ", m_matrix_array[i*cols + k]));
            }
            matrix_str.erase(matrix_str.end() - 1);
            matrix_str.append("\n");
            
        }
        matrix_str.erase(matrix_str.end() - 1);
        return matrix_str;
    }

private:
    int m_total_elements;
    int rows;
    int cols;
    std::vector<int> m_matrix_array;
};