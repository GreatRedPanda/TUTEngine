#include "AssetsDatabase.h"
//#include <functional>




Asset* AssetsDatabase::GetAssetsRoot()
{
    return assetsFolder;
}

void AssetsDatabase::LoadProject(std::string path)
{
  
    assetsFolder->isDirectory = true;
    assetsFolder->filename = "";
    assetsTree.insert(std::pair(assetsFolder, std::vector<Asset*>()));
    LoadDirectoryContent(assetsFolder, projectDirectory);
}

void AssetsDatabase::LoadDirectoryContent(Asset* prevDirectoryAsset, std::string parentDirectory)
{
    //std::filesystem::path p = { parentDirectory };
    //std::string directory = "";
    //if(prevDirectoryAsset!=nullptr)
    //    directory= prevDirectoryAsset->filename;
    //p /= directory;
    //std::filesystem::directory_iterator di = std::filesystem::directory_iterator(p);
    //for (auto it = std::filesystem::begin(di); it != std::filesystem::end(di); ++it)
    //{
    //   
    //    std::filesystem::path root= (*it).path().c_str();
    //    Asset* newAsset = new Asset();
    //    newAsset->filename = root.filename().filename().string();
    //    newAsset->extension = root.filename().extension().string();
    //    newAsset->parentDirectory = directory;
    //    newAsset->isDirectory = std::filesystem::is_directory(root);
    //   // assets.push_back(newAsset);
    //    if(std::filesystem::is_directory(root))
    //    {
    //        assetsTree.insert(std::pair(newAsset,  std::vector<Asset*>()));
    //        LoadDirectoryContent(newAsset, p.string());
    //    }
    //    else
    //    {
    //        assetsTree.at(prevDirectoryAsset).push_back(newAsset);
    //    }       
    //}
}

std::vector<Asset*> AssetsDatabase::GetDirectoryContent(Asset* directoryAsset)
{
    std::vector<Asset*> result = {};
    
  /*auto it=  assetsTree.find(directoryAsset);
  if (it != assetsTree.end())
  {
      std::string directoryName = directoryAsset->filename;

      for (auto i = assetsTree.begin(); i != assetsTree.end(); i++)
      {
          if (i != it)
              if ((*i).first->parentDirectory == directoryName)
                  result.push_back((*i).first);
      }
      result.insert(result.end(), it->second.begin(), it->second.end());

      return result;
  }
  else*/
      return {  };
}

std::vector<Asset*> AssetsDatabase::GetDirectoryContent(std::string directoryName)
{
   /* std::vector<Asset*> result = {};
   

    auto result3 = std::find_if(assetsTree.begin(), assetsTree.end(), 
        [&](std::pair<Asset*, std::vector< Asset*>> p)  {return p.first->filename == directoryName; });
    if (result3 != assetsTree.end())
    {
        

        for (auto i = result3; i!= assetsTree.end(); i++)
        {
            if(i!=result3)
            if ((*i).first->parentDirectory == directoryName)
                result.push_back( (*i).first);
        }
        result.insert(result.end(), result3->second.begin(), result3->second.end());
        return result;
    }*/
    return {};
}
