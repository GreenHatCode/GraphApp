#include "ProcessGraph/ProcessGraphDialog.h"

enum {
    ID_EARLY_EVENT_DATE,
    ID_LATE_EVENT_DATE,
    ID_EVENT_TIME_RESERVE,
    ID_CRITICAL_PATH,
    ID_OUTPUTTYPE_DESTINATION,
    ID_COMPLEXITY_FACTOR,
    ID_SELECT_ALL
};

ProcessGraphDialog::ProcessGraphDialog(
    wxWindow* parent, 
    wxWindowID id, 
    const wxString& title, 
    ProcessGraphSettings& process_settings,
    const wxPoint& pos, 
    const wxSize& size, 
    long style, 
    const wxString& name
)
    :m_process_settings{process_settings},wxDialog(parent, id, title, pos, size, style, name)
{

    wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

    top_sizer->Add(boxSizer, 1, wxALL | wxEXPAND, 5);

    wxStaticBoxSizer* options_sizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Calculate")), wxVERTICAL);

    boxSizer->Add(options_sizer, 2, wxALL | wxEXPAND, 5);

    wxCheckBox* m_checkBox51 = new wxCheckBox(this, ID_EARLY_EVENT_DATE, _("Early event date (t eraly)"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBox51->SetValue(false);

    options_sizer->Add(m_checkBox51, 0, wxALL, 5);

    wxCheckBox* m_checkBox52 = new wxCheckBox(this, ID_LATE_EVENT_DATE, _("Late event date (t late)"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBox52->SetValue(false);

    options_sizer->Add(m_checkBox52, 0, wxALL, 5);

    wxCheckBox* m_checkBox53 = new wxCheckBox(this, ID_EVENT_TIME_RESERVE, _("Event time reserve (R)"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBox53->SetValue(false);

    options_sizer->Add(m_checkBox53, 0, wxALL, 5);

    wxCheckBox* complexity_factor_check = new wxCheckBox(this, ID_COMPLEXITY_FACTOR, _("Coplexity factor"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);
    complexity_factor_check->SetValue(false);

    options_sizer->Add(complexity_factor_check, 0, wxALL, 5);

    wxStaticBoxSizer* staticBoxSizer62 = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Draw")), wxVERTICAL);

    boxSizer->Add(staticBoxSizer62, 1, wxALL | wxEXPAND, 5);

    wxCheckBox* m_checkBox63 = new wxCheckBox(this, ID_CRITICAL_PATH, _("Critical path"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBox63->SetValue(false);

    staticBoxSizer62->Add(m_checkBox63, 0, wxALL, 5);

    wxBoxSizer* special_controls_sizer = new wxBoxSizer(wxVERTICAL);
    
    boxSizer->Add(special_controls_sizer, 0, wxALL | wxEXPAND, 5);
    
    wxCheckBox* select_all_check = new wxCheckBox(this, ID_SELECT_ALL, _("Select all"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);
    select_all_check->SetValue(false);
    
    special_controls_sizer->Add(select_all_check, 0, wxALL | wxALIGN_RIGHT, 5);

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
    wxCheckBox* complexity_factor_check = (wxCheckBox*)FindWindow(ID_COMPLEXITY_FACTOR);
    wxRadioBox* output_destination_selector = (wxRadioBox*)FindWindow(ID_OUTPUTTYPE_DESTINATION);


    m_process_settings.SetCalculateEarlyEventDate(t_early_check->GetValue());
    m_process_settings.SetCalculateLateEventDate(t_late_check->GetValue());
    m_process_settings.SetCalculateEvenTimeReserne(t_R_check->GetValue());
    m_process_settings.SetDrawCriticalPath(critical_path_check->GetValue());
    m_process_settings.SetOutputDestination((OutputDestination)output_destination_selector->GetSelection());

    return true;
}

bool ProcessGraphDialog::TransferDataToWindow()
{
    wxCheckBox* t_early_check = (wxCheckBox*)FindWindow(ID_EARLY_EVENT_DATE);
    wxCheckBox* t_late_check = (wxCheckBox*)FindWindow(ID_LATE_EVENT_DATE);
    wxCheckBox* t_R_check = (wxCheckBox*)FindWindow(ID_EVENT_TIME_RESERVE);
    wxCheckBox* critical_path_check = (wxCheckBox*)FindWindow(ID_CRITICAL_PATH);
    wxRadioBox* output_destination_selector = (wxRadioBox*)FindWindow(ID_OUTPUTTYPE_DESTINATION);

    t_early_check->SetValue(m_process_settings.GetCalculateEarlyEventDate());
    t_late_check->SetValue(m_process_settings.GetCalculateLateEventDate());
    t_R_check->SetValue(m_process_settings.GetCalculateEvenTimeReserne());
    critical_path_check->SetValue(m_process_settings.GetDrawCriticalPath());
    output_destination_selector->SetSelection(m_process_settings.GetOutputDestination());

    return true;
}
