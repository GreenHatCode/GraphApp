#pragma once
#include "wx/print.h"
#include "wx/printdlg.h"
#include "wx/wx.h"

// This class provides a simple functionality to print a graph as an image.
// Source link: https://github.com/GreenHatCode/Projects/tree/main/QuickPrint

class QuickPrint :
    public wxPrintout
{
public:

    QuickPrint(const QuickPrint& obj);
    QuickPrint(int page_amount, wxString title, float units_per_cm, std::function<void(wxDC& dc, int pageNum, wxSize dc_size)> print_fun);
    bool performPageSetup(const bool showPageSetupDialog);
    void OnBeginPrinting();
    wxPrintData getPrintData();
    bool OnBeginDocument(int startPage, int endPage);
    void GetPageInfo(int* minPage, int* maxPage, int* pageSelFrom, int* pageSelTo);
    bool HasPage(int pageNum);
    bool OnPrintPage(int pageNum);

private:
    wxPageSetupData m_page_setup;
    wxPaperSize m_paper_type; // the type of paper: latter, A4, etc
    int m_orient; // horizontal or vertical
    int m_page_amount;
    int m_margin_left, m_margin_right, m_margin_top, m_margin_bottom; // margins in millimeters
    float m_units_per_cm; //how fine the coordinate system is
    int m_coord_system_width, m_coord_system_height;
    std::function<void(wxDC& dc, int pageNum, wxSize dc_size)> m_print_fun;
};

