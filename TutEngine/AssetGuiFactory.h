#pragma once
#include <string>
#include <map>
#include "Texture.h"

struct AssetGUI
{




};
class AssetGuiFactory
{
	static std::map<std::string, AssetGUI> assetsView;

public:

	static AssetGUI  GetAssetTexture(std::string extension);


};

