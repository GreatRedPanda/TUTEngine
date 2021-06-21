#pragma once
#include <string>
class Asset
{

public: 
	bool isDirectory = true;
	
	std::string extension;
	std::string filename;
	std::string parentDirectory;
};

