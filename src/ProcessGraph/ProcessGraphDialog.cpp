#include "ProcessGraph/ProcessGraphDialog.h"

enum {
    ID_EARLY_EVENT_DATE,
    ID_LATE_EVENT_DATE,
    ID_EVENT_TIME_RESERVE,
    ID_CRITICAL_PATH,
    ID_OUTPUTTYPE_DESTINATION
};

ProcessGraphDialog::ProcessGraphDialog(
    wxWindow* parent, 
    wxWindowID id, 
    const wxString& title, 
    const wxPoint& pos, 
    const wxSize& size, 
    ProcessGraphSettings& process_settings,
    long style, 
    const wxString& name
)
    :m_process_settings{process_settings},wxDialog(parent, id, title, pos, size, style, name)
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

    wxArrayString output_destinationArr;
    output_destinationArr.Add(_("Drawing area"));
    output_destinationArr.Add(_("Separate window"));
    output_destinationArr.Add(_(".txt file"));
    wxRadioBox* output_destination = new wxRadioBox(this, ID_OUTPUTTYPE_DESTINATION, _("Output destination"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), output_destinationArr, 3, wxRA_SPECIFY_COLS);
    output_destination->SetSelection(0);

    boxSizer->Add(output_destination, 0, wxALL, 5);

    wxBoxSizer* buttons_sizer = new wxBoxSizer(wxHORIZONTAL);

    boxSizer->Add(buttons_sizer, 0, wxALL | wxEXPAND, 5);

    wxButton* button_ok = new wxButton(this, wxID_OK, _("OK"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    buttons_sizer->Add(button_ok, 0, wxALL, 5);

    wxButton* button_cancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    buttons_sizer->Add(button_cancel, 0, wxALL, 5);

    SetSizerAndFit(top_sizer);
    SetSize(wxSize(400, -1));
    TransferDataToWindow();
}

ProcessGraphDialog::~ProcessGraphDialog()
{
}

bool ProcessGraphDialog::GetCalculateEarlyEventDate()
{
    return m_calculate_t_early;
}

bool ProcessGraphDialog::GetCalculateLateEventDate()
{
    return m_calculate_t_late;
}

bool ProcessGraphDialog::GetCalculateEvenTimeReserne()
{
    return m_calculate_R;
}

bool ProcessGraphDialog::GetDrawCriticalPath()
{
    return m_draw_critical_path;
}

OutputDestination ProcessGraphDialog::GetOutputDestination()
{
    return m_output_destination;
}

void ProcessGraphDialog::OnOK(wxCommandEvent& evt)
{
    if (TransferDataFromWindow())
    {
        if (IsModal())
        {
            EndModal(wxID_OK); // if modal
        }
        else
        {
            SetReturnCode(wxID_OK);
            this->Show(false); // if modeless
        }
    }
    else wxLogError("Can't transfer data from window.");
}

bool ProcessGraphDialog::TransferDataFromWindow()
{
    wxCheckBox* t_early_check = (wxCheckBox*)FindWindow(ID_EARLY_EVENT_DATE);
    wxCheckBox* t_late_check = (wxCheckBox*)FindWindow(ID_LATE_EVENT_DATE);
    wxCheckBox* t_R_check = (wxCheckBox*)FindWindow(ID_EVENT_TIME_RESERVE);
    wxCheckBox* critical_path_check = (wxCheckBox*)FindWindow(ID_CRITICAL_PATH);
    wxRadioBox* output_destination_selector = (wxRadioBox*)FindWindow(ID_OUTPUTTYPE_DESTINATION);

    m_calculate_t_early = t_early_check->GetValue();
    m_calculate_t_late = t_late_check->GetValue();
    m_calculate_R = t_R_check->GetValue();
    m_draw_critical_path = critical_path_check->GetValue();
    m_output_destination = (OutputDestination)output_destination_selector->GetSelection();

    return true;
}

bool ProcessGraphDialog::TransferDataToWindow()
{
    wxCheckBox* t_early_check = (wxCheckBox*)FindWindow(ID_EARLY_EVENT_DATE);
    wxCheckBox* t_late_check = (wxCheckBox*)FindWindow(ID_LATE_EVENT_DATE);
    wxCheckBox* t_R_check = (wxCheckBox*)FindWindow(ID_EVENT_TIME_RESERVE);
    wxCheckBox* critical_path_check = (wxCheckBox*)FindWindow(ID_CRITICAL_PATH);
    wxRadioBox* output_destination_selector = (wxRadioBox*)FindWindow(ID_OUTPUTTYPE_DESTINATION);

    t_early_check->SetValue(m_calculate_t_early);
    t_late_check->SetValue(m_calculate_t_late);
    t_R_check->SetValue(m_calculate_R);
    critical_path_check->SetValue(m_draw_critical_path);
    output_destination_selector->SetSelection(m_output_destination);

    return true;
}
