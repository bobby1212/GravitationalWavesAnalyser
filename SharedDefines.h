#pragma once
#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/glcanvas.h>
#include <wx/sizer.h>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include <math.h>
#include "boost\lexical_cast.hpp"
#include "boost\range\algorithm_ext\erase.hpp"
#include "boost\random.hpp"
#include "boost\tokenizer.hpp"
#include <boost/iostreams/device/mapped_file.hpp>
#include <future>
#include <mutex>
#include <chrono>
#include <set>

enum IDs
{
	ID_PANEL_OPTIONS,
	ID_PANEL_RENDER,

	ID_FILE_OPEN,
	ID_FILE_EXIT,
	ID_EDIT_NOTHING,
    ID_EXPORT_HEIGHTMAP,
	ID_INFO_ABOUT,
    ID_MOUSE_MOTION,

	ID_OPTION_TEXTCHANGED,
	ID_OPTION_HEIGHTDIVISOR,
	ID_OPTION_DIVISOR,
    ID_OPTION_MAX_HEIGHT,
    ID_OPTION_MIN_HEIGHT,
    ID_OPTION_REMOVE_DUPLICATES,
    ID_OPTION_TRIANGULATE,
    ID_OPTION_MAX_RADIUS,
    ID_OPTION_MIN_RADIUS,
    
    ID_INFO_NMB_POINTS,
};

enum MENU
{
	MENU_OPEN_FILE,
	MENU_SAVE,
	MENU_EXPORT,
};

enum ERROR_ID
{
	ERROR_NAN,
	ERROR_ONE_POINT,
    ERROR_UNKNOWN,
};
