#include "AppPreferences/AppPreferences.h"
#include "AppPreferences.h"

AppPreferences::AppPreferences(const std::string& preference_file)
{
	if (!preference_file.empty())
	{
		m_preference_file = preference_file;
		LoadDataFromFile();
	}
}

void AppPreferences::SetPreferenceFile(const std::string& value)
{
	m_preference_file = value;
	LoadDataFromFile();
}

std::string AppPreferences::GetPreferenceFile()
{
	return m_preference_file;
}

void AppPreferences::SetDuplicationWarning(bool value)
{
	m_dupl_warning = value;
}

bool AppPreferences::GetDuplicationWarning()
{
	return m_dupl_warning;
}

void AppPreferences::SetShowTooltip(bool value)
{
	m_show_tip = value;
}

bool AppPreferences::GetShowTooltip()
{
	return m_show_tip;
}

void AppPreferences::SetColourScheme(ColourSchemes value)
{
	m_colour_scheme_type = value;
}

ColourSchemes AppPreferences::GetColourScheme()
{
	return m_colour_scheme_type;
}

void AppPreferences::SetDynamicGraphProcessing(bool value)
{
	m_dynamic_graph_processing = value;
}

bool AppPreferences::GetDynamicGraphProcessing()
{
    return m_dynamic_graph_processing;
}

bool AppPreferences::SaveDataToFile()
{
	mINI::INIFile otf(m_preference_file);
	mINI::INIStructure ini;
	if (!otf.read(ini))
	{
		wxLogError("Unable to read preference file \"%s\".", m_preference_file);
		return false;
	}

	std::string m_dupl_warning_str = std::to_string(m_dupl_warning);
	std::string m_show_tip_str = std::to_string(m_show_tip);
	std::string m_colour_scheme_type_str = std::to_string(m_colour_scheme_type);
	std::string m_dynamic_graph_processing_str = std::to_string(m_dynamic_graph_processing);

	ini["general"].set({
		{ "dupl_warning", m_dupl_warning_str },
		{ "show_tip", m_show_tip_str },
		{ "dynamic_graph_processing", m_dynamic_graph_processing_str }
		});

	ini["appearance"]["colour_scheme_type"] = m_colour_scheme_type_str;

	if (!otf.write(ini))
	{
		wxLogError("Unable to write data to %s.", m_preference_file);
		return false;
	}
	else return true;
}

bool AppPreferences::LoadDataFromFile()
{
	mINI::INIFile otf(m_preference_file);
	mINI::INIStructure ini;
	if (!otf.read(ini))
	{
		wxLogError("Unable to read preference file \"%s\".", m_preference_file);
		return false;
	}

	std::string m_dupl_warning_str = ini.get("general").get("dupl_warning");
	std::string m_show_tip_str = ini.get("general").get("show_tip");
	std::string m_colour_scheme_type_str = ini.get("appearance").get("colour_scheme_type");
	std::string m_dynamic_graph_processing_str = ini.get("general").get("dynamic_graph_processing");

	std::istringstream(m_dupl_warning_str) >> m_dupl_warning;
	std::istringstream(m_show_tip_str) >> m_show_tip;
	std::istringstream(m_dynamic_graph_processing_str) >> m_dynamic_graph_processing;
	
	switch (std::stoi(m_colour_scheme_type_str))
	{
	case ColourSchemes::COLOURED:
		m_colour_scheme_type = ColourSchemes::COLOURED;
		break;
	case ColourSchemes::BLACK_WHITE:
		m_colour_scheme_type = ColourSchemes::BLACK_WHITE;
		break;
	default:
		wxLogError("Unable load convert colour_scheme_type. There is no such type %i. File: AppPreference.cpp.", std::stoi(m_colour_scheme_type_str));
		return false;
		break;
	}
	
	return true;
}
