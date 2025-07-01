#pragma once
#include "wx/wx.h"
#include "mini/ini.h"

// In case the app can't open setting file, it will use 
// the default settings
//
//	To add new settings:
// 1) add a new variable and necessary set/get methods
// 2) add it's key and value to setting file
// 3) add necessary controls and their handlers in preference window class
//

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

	void SetDynamicGraphProcessing(bool value);
	bool GetDynamicGraphProcessing();

	bool SaveDataToFile();
	bool LoadDataFromFile();

	bool operator != (AppPreferences& obj)
	{
		if (m_dupl_warning != obj.m_dupl_warning || 
			m_show_tip != obj.m_show_tip || 
			m_colour_scheme_type != obj.m_colour_scheme_type ||
			m_dynamic_graph_processing != obj.m_dynamic_graph_processing
		)
		{
			return true;
		}
		return false;
	}



private:
	std::string m_preference_file; // path to file with app's preferences

	// show warning message if the user tries to add a new node with existing index
	bool m_dupl_warning;
	// show tooltip at startup of the app
	bool m_show_tip;
	// sets the colour scheme of the drawint area
	ColourSchemes m_colour_scheme_type = ColourSchemes::COLOURED;
	// process the graph after any change in it
	bool m_dynamic_graph_processing;

};

