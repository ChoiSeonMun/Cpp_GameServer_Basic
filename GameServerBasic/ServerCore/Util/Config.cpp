#include "stdafx.h"
#include "Config.h"

using namespace tinyxml2;

bool LoadConfig(tinyxml2::XMLDocument& doc)
{
	if (XML_SUCCESS != doc.LoadFile("./Config.xml"))
	{
		return false;
	}
	
	return true;
}