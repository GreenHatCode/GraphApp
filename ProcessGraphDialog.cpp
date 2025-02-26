#include "ProcessGraphDialog.h"

enum {
    ID_EARLY_EVENT_DATE,
    ID_LATE_EVENT_DATE,
    ID_EVENT_TIME_RESERVE,
    ID_CRITICAL_PATH,
    ID_OUTPUTTYPE_FILE,
    ID_OUTPUTTYPE_SEPARATE_WINDOW
};




ProcessGraphDialog::ProcessGraphDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
    :wxDialog(parent, id, title, pos, size, style, name)
{




    wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

    top_sizer->Add(boxSizer, 1, wxALL | wxEXPAND, 5);

    wxStaticBoxSizer* options_sizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Calculate")), wxVERTICAL);

    boxSizer->Add(options_sizer, 1, wxALL | wxEXPAND, 5);

    wxCheckBox* m_checkBox51 = new wxCheckBox(this, ID_EARLY_EVENT_DATE, _("Early event date (t eraly)"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBox51->SetValue(false);

    options_sizer->Add(m_checkBox51, 0, wxALL, 5);

    wxCheckBox* m_checkBox52 = new wxCheckBox(this, ID_LATE_EVENT_DATE, _("Late event date (t late)"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBox52->SetValue(false);

    options_sizer->Add(m_checkBox52, 0, wxALL, 5);

    wxCheckBox* m_checkBox53 = new wxCheckBox(this, ID_EVENT_TIME_RESERVE, _("Event time reserve (R)"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBox53->SetValue(false);

    options_sizer->Add(m_checkBox53, 0, wxALL, 5);

    wxStaticBoxSizer* staticBoxSizer62 = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Draw")), wxVERTICAL);

    boxSizer->Add(staticBoxSizer62, 1, wxALL | wxEXPAND, 5);

    wxCheckBox* m_checkBox63 = new wxCheckBox(this, ID_CRITICAL_PATH, _("Critical path"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBox63->SetValue(false);

    staticBoxSizer62->Add(m_checkBox63, 0, wxALL, 5);

    wxStaticBoxSizer* output_destination_sizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Output destination")), wxHORIZONTAL);

    boxSizer->Add(output_destination_sizer, 1, wxALL | wxEXPAND, 5);

    wxRadioButton* m_radioButton60 = new wxRadioButton(this, ID_OUTPUTTYPE_FILE, _(".txt file"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_radioButton60->SetValue(1);

    output_destination_sizer->Add(m_radioButton60, 0, wxALL, 5);

    wxRadioButton* m_radioButton61 = new wxRadioButton(this, ID_OUTPUTTYPE_SEPARATE_WINDOW, _("Separate window"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_radioButton61->SetValue(1);

    output_destination_sizer->Add(m_radioButton61, 0, wxALL, 5);

    wxBoxSizer* buttons_sizer = new wxBoxSizer(wxHORIZONTAL);

    boxSizer->Add(buttons_sizer, 0, wxALL | wxEXPAND, 5);

    wxButton* button_ok = new wxButton(this, wxID_OK, _("OK"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    buttons_sizer->Add(button_ok, 0, wxALL, 5);

    wxButton* button_cancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    buttons_sizer->Add(button_cancel, 0, wxALL, 5);

    SetSizerAndFit(top_sizer);
    SetSize(wxSize(400, -1));

}

ProcessGraphDialog::~ProcessGraphDialog()
{
}
