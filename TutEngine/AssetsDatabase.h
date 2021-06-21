//#pragma once
#ifndef ASSETSBASE_H_
#define ASSETSBASE_H_
#include <map>
#include <string>
#include <filesystem>
//#include <fstream>
#include <vector>
#include "Asset.h"

class AssetsDatabase
{
	Asset* assetsFolder = new Asset();
	std::map<Asset*, std::vector< Asset*>> assetsTree = std::map<Asset*, std::vector< Asset*>>();
	std::vector< Asset*> assets = std::vector< Asset*>();
	std::string projectDirectory;

public:
	AssetsDatabase(std::string mainDirectory)
	{
		projectDirectory = mainDirectory.c_str();
	}

	Asset* GetAssetsRoot();
	void LoadProject(std::string path);
	void LoadDirectoryContent(Asset* prevDirectoryAsset,std::string parentDirectory);
	std::vector< Asset*> GetDirectoryContent(Asset* directoryAsset);
	std::vector< Asset*> GetDirectoryContent(std::string directoryName="");
};

#endif