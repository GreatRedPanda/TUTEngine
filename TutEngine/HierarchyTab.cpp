#include "HierarchyTab.h"
#include "WindowsOle.h"

void HierarchyTab::Update()
{

  //  ImGui::SetNextWindowPos(ImVec2(ScaleX*posX, ScaleY * posY));
    ImGui::Begin("Hierarchy");
    //ImGui::SetWindowSize(ImVec2(ScaleX * sizeX, ScaleY * sizeY));
    ImGui::Button("DnD", ImVec2(30, 20));
    if (ImGui::BeginDragDropSource())
    {
       
        ImGui::SetDragDropPayload("FILE", nullptr, 0);
        ImGui::BeginTooltip();
        ImGui::Text("DND");
        ImGui::EndTooltip();
      //  WindowsOle::WindowsOleInstance->DragDocument();
        ImGui::EndDragDropSource();
    }
    //ImGui::Text("FILE1");
    //if (ImGui::IsItemHovered())
    //{

    //   // hoveredObject = "FILE_1";
    //}
    //ImGui::Text("FILE2");
    //if (ImGui::IsItemHovered())
    //{

    //    //hoveredObject = "FILE_2";
    //}

    ImGui::End();
}
