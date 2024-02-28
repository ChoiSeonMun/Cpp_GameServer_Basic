#include "stdafx.h"

using namespace tinyxml2;

int main()
{
	tinyxml2::XMLDocument configDoc;
	
	if (false == LoadConfig(configDoc))
	{
		return 1;
	}

	auto root = configDoc.FirstChildElement("App")->FirstChildElement("Server");
	auto elem = root->FirstChildElement("IP");
	printf("%s", elem->GetText());

	return 0;
}