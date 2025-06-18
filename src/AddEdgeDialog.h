#pragma once
#include "wx/wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinctrl.h>

/* Desctiption:

*/

class AddEdgeDialog:
    public wxDialog
{
public:
    AddEdgeDialog(wxWindow* parent, wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE,
        const wxString& name = wxASCII_STR(wxDialogNameStr));

    ~AddEdgeDialog();




private:



};