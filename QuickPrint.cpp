#include "QuickPrint.h"

QuickPrint::QuickPrint(const QuickPrint& obj)
	:wxPrintout(obj.GetTitle())
{
	m_page_amount = obj.m_page_amount;
	m_orient = obj.m_orient; // wxPORTRAIT, WXLANDSCAPE
	m_paper_type = obj.m_paper_type;
	m_margin_left = obj.m_margin_left;
	m_margin_right = obj.m_margin_right;
	m_margin_top = obj.m_margin_top;
	m_margin_bottom = obj.m_margin_bottom;
	m_page_setup = obj.m_page_setup;

	m_units_per_cm = obj.m_units_per_cm;
	m_print_fun = obj.m_print_fun;
}

QuickPrint::QuickPrint(
	int page_amount,
	wxString title,
	float units_per_cm,
	std::function<void(wxDC& dc, int pageNum, wxSize dc_size)> print_fun
)
	:wxPrintout(title)
{
	m_page_amount = page_amount;
	m_orient = wxPORTRAIT; // wxPORTRAIT, WXLANDSCAPE
	m_paper_type = wxPAPER_LETTER;
	m_margin_left = 16;
	m_margin_right = 16;
	m_margin_top = 32;
	m_margin_bottom = 32;

	m_units_per_cm = units_per_cm;
	m_print_fun = print_fun;
}

bool QuickPrint::performPageSetup(const bool showPageSetupDialog)
{
	wxPrintData printdata;
	printdata.SetPrintMode(wxPRINT_MODE_PRINTER);
	printdata.SetOrientationReversed(m_orient);
	printdata.SetNoCopies(1);
	printdata.SetPaperId(m_paper_type);

	m_page_setup = wxPageSetupDialogData(printdata);
	m_page_setup.SetMarginTopLeft(wxPoint(m_margin_left, m_margin_top));
	m_page_setup.SetMarginBottomRight(wxPoint(m_margin_right, m_margin_bottom));

	if (showPageSetupDialog)
	{
		wxPageSetupDialog dialog(NULL, &m_page_setup);
		if (dialog.ShowModal() == wxID_OK)
		{
			m_page_setup = dialog.GetPageSetupData();
			m_orient = m_page_setup.GetPrintData().GetOrientation();
			m_paper_type = m_page_setup.GetPrintData().GetPaperId();

			wxPoint marginTopLeft = m_page_setup.GetMarginTopLeft();
			wxPoint marginBottomRight = m_page_setup.GetMarginBottomRight();

			m_margin_left = marginTopLeft.x;
			m_margin_right = marginBottomRight.x;
			m_margin_top = marginTopLeft.y;
			m_margin_bottom = marginBottomRight.y;
		}
		else
		{
			// the user canceled at first dialog
			return false;
		}
	}
	return true;
}

void QuickPrint::OnBeginPrinting()
{
	wxSize paperSize = m_page_setup.GetPaperSize();

	float large_side = std::max(paperSize.GetWidth(), paperSize.GetHeight());
	float small_side = std::min(paperSize.GetWidth(), paperSize.GetHeight());

	float large_side_cm = large_side / 10.0f;
	float small_side_cm = small_side / 10.0f;

	if (m_orient = wxPORTRAIT)
	{
		float ratio = float(large_side - m_margin_top - m_margin_bottom) /
			float(small_side - m_margin_left - m_margin_right);

		m_coord_system_width = (int)((small_side_cm - m_margin_left / 10.f -
			m_margin_right / 10.0f) * m_units_per_cm);
		m_coord_system_height = m_coord_system_width * ratio;
	}
	else
	{
		float ratio = float(large_side - m_margin_left - m_margin_right) /
			float(small_side - m_margin_top - m_margin_bottom);

		m_coord_system_height = (int)((small_side_cm - m_margin_top / 10.0f -
			m_margin_bottom / 10.0f) * m_units_per_cm);
		m_coord_system_width = m_coord_system_height * ratio;
	}
}

wxPrintData QuickPrint::getPrintData()
{
	return m_page_setup.GetPrintData();
}

bool QuickPrint::OnBeginDocument(int startPage, int endPage)
{
	return wxPrintout::OnBeginDocument(startPage, endPage);
}

void QuickPrint::GetPageInfo(int* minPage, int* maxPage, int* pageSelFrom, int* pageSelTo)
{
	*minPage = 1;
	*maxPage = m_page_amount;

	*pageSelFrom = 1;
	*pageSelTo = m_page_amount;
}

bool QuickPrint::HasPage(int pageNum)
{
	return pageNum >= 1 && pageNum <= m_page_amount;
}

bool QuickPrint::OnPrintPage(int pageNum)
{
	// ---- setup DC with coordinate system ----
	FitThisSizeToPageMargins(wxSize(m_coord_system_width, m_coord_system_height), m_page_setup);

	wxRect fitRect = GetLogicalPageMarginsRect(m_page_setup);

	wxCoord xoff = (fitRect.width - m_coord_system_width) / 2;
	wxCoord yoff = (fitRect.height - m_coord_system_height) / 2;
	OffsetLogicalOrigin(xoff, yoff);

	wxDC* ptr = GetDC();
	if (ptr == NULL || !ptr->IsOk())
	{
		// DC is not Ok, interrupting printing
		return false;
	}
	wxDC& dc = *ptr; // printger dc

	
	m_print_fun(dc, pageNum, wxSize(m_coord_system_width, m_coord_system_height));// drawing into printerDC all we need to print 

	return true;
}
