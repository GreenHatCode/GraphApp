#pragma once
#include "wx\wx.h"

// toolbar images
#include "res/cursor24.xpm"
#include "res/delete.xpm"
#include "res/node24.xpm"
#include "res/edge24.xpm"
#include "res/process24color.xpm"
#include "res/help.xpm"


class mainFrame :
    public wxFrame
{
public:
    mainFrame(const wxString& title);

private:



    // menu bar functions
    void OnQuit(wxCommandEvent& evt);


    DECLARE_EVENT_TABLE();
};

