#include "ProjectTab.h"
#include "Asset.h"
void ProjectTab::drawDirectory(Asset* directoryAsset)
{

    std::vector<Asset*> folder = currentAssets->GetDirectoryContent(directoryAsset);

    if (folder.size() != 0)
    {

        if (ImGui::TreeNode(directoryAsset->filename.c_str()))
        {
            for (std::vector<Asset*>::iterator i = folder.begin(); i != folder.end(); i++)
            {

                if ((*i)->isDirectory)
                {
                    drawDirectory(*i);
                }
                else
                {
                    ImGui::Text((*i)->filename.c_str());

                }
            }
            ImGui::TreePop();

        }

    }
    else
    {
        ImGui::Text(directoryAsset->filename.c_str());
    }
}
void ProjectTab::Update()
{
    ImGui::SetNextWindowPos(ImVec2(ScaleX * posX, ScaleY * posY));
    ImGui::Begin("Project", &isOpen, flags);
    ImGui::SetWindowSize(ImVec2(ScaleX * sizeX, ScaleY * sizeY));
    drawDirectory(currentAssets->GetAssetsRoot());
    ImGui::End();
  //  drawDirectory(Asset * directoryAsset);
    //if (ImGui::TreeNode("Assets"))
    //{
    //    std::vector<Asset*> folder = currentAssets->GetDirectoryContent();
    //    for (std::vector<Asset*>::iterator i = folder.begin(); i != folder.end(); i++)
    //    {
    //         
    //        if ((*i)->isDirectory)
    //        {


    //            if (ImGui::TreeNode((*i)->filename.c_str()))
    //            {
    //                ImGui::Text("1");
    //                ImGui::TreePop();
    //            }
    //           

    //        }
    //        else
    //        {
    //            ImGui::Text((*i)->filename.c_str());
    //        }
    //        //ImGui::BulletText(i->c_str());
    //        
    //    }
    //    ImGui::TreePop();
    //}
  
    //for (size_t i = 0; i < 10; i++)
    //{
    //    if (ImGui::TreeNode("233"))
    //    {
    //      
    //        ImGui::BulletText("Sections below are demonstrating many aspects of the library.");
    //        ImGui::TreePop();
    //        ImGui::Separator();
    //    }
    //}
   // ImGui::End();
    //ImGui::SetNextWindowPos(ImVec2(0, ScaleY * sizeY));
    //ImGui::Begin("Project", &isOpen, flags);
    //ImGui::SetWindowSize(ImVec2(ScaleX * sizeX, ScaleY * sizeY));

    //if (ImGui::IsWindowHovered() && ImGui::IsMouseReleased(0))
    //{

    //    projectItems.push_back(hoveredObject);
    //}
  
    //for (auto i = projectItems.begin(); i != projectItems.end(); i++)
    //{
    //    ImGui::Text(i->c_str());
    //}
}
