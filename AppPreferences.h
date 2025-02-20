#pragma once
#include "wx/wx.h"
#include "mini/ini.h"


// represents colours scheme types
enum ColourSchemes 
{
	COLOURED = 0,
	BLACK_WHITE = 1
};


// stores app preferenfes, provides an interface to load/write them into file
class AppPreferences
{
public:
	AppPreferences(const std::string& preference_file);

	void SetPreferenceFile(const std::string& value);
	std::string GetPreferenceFile();

	void SetDuplicationWarning(bool value);
	bool GetDuplicationWarning();

	void SetShowTooltip(bool value);
	bool GetShowTooltip();

	void SetColourScheme(ColourSchemes value);
	ColourSchemes GetColourScheme();


	bool SaveDataToFile();
	bool LoadDataFromFile();

private:
	std::string m_preference_file; // path to file with app's preferences




	// show warning message if the user tries to add a new node with existing index
	bool m_dupl_warning = true;
	// show tooltip at startup of the app
	bool m_show_tip = true;
	// sets the colour scheme of the drawint area
	ColourSchemes m_colour_scheme_type = ColourSchemes::COLOURED;

};

