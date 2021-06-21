// TutEngine.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
//#ifndef IMGUI
//#define IMGUI
//#endif
#include<iostream>
#include <imgui.h>


//#include<GL/glew.h>
#include<glm.hpp>
#include<gtc/matrix_inverse.hpp>
//#include<GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>            // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
#include <glad/gl.h>            // Initialize with gladLoadGL(...) or gladLoaderLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h>  // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>// Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>
#include "StageRenderer.h"
#include "Object.h"
#include "FreeLookCamera.h"
#include "StageViewTab.h"
#include "HierarchyTab.h"
#include "ProjectTab.h"
#include "ToolsTab.h"
#include "PropertiesTab.h"
#include "ProjectInit.h"
#include "WindowsOle.h"


// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif



void mainThread(GLFWwindow* window);
int width = 800;
int height = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


const char* glsl_version;

int main()
{
   // SendInput();
    glfwSetErrorCallback(glfw_error_callback);
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
     glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

  
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(width, height, "TutEngine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
    bool err = gladLoadGL(glfwGetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
    bool err = false;
    glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
    bool err = false;
    glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)glfwGetProcAddress(name); });
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }
    IMGUI_CHECKVERSION();
   // static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGui::CreateContext();

    //COleDataObject* o;
  //COleData
  //  CF_HDROP 
    WindowsOle wo = WindowsOle();
    mainThread(window);
    wo.~WindowsOle();
}


void mainThread(GLFWwindow* window)
{
   

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
   //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
   // ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
//    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
 //   ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
  //  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    int actualWindowWidth = width, actualWindowHeight = height;
    float gridX = actualWindowWidth / 10.0f;
    float gridY = actualWindowHeight / 10.0f;
    ProjectInit project = ProjectInit();
    AssetsDatabase assetsBase = AssetsDatabase("D:/TutProject/Assets");
    assetsBase.LoadProject("D:/TutProject/Assets");
    Input input = Input(*window);
    StageViewTab svTab = StageViewTab(1,0.5f,6,9.5f );
    HierarchyTab hTab = HierarchyTab(7,0,3,4);
    ProjectTab prTab = ProjectTab(assetsBase,0,0.5f, 1,9.5f);
    ToolsTab toolsTab = ToolsTab(0,0, 7, 0.5f);
    PropertiesTab propTab = PropertiesTab(7, 4, 3, 6);
    ImGuiWindowFlags flags = 
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration| ImGuiWindowFlags_DockNodeHost;
   // ImGuiID dockingSpace= ImGui::GetID("MyDockspace");
   // HWND hwnd= FindWindow( NULL,L"TutEngine");
   
    bool isOpen = true;
    while (!glfwWindowShouldClose(window))
    {
    /*    DWORD len = 256;
        TCHAR* t=new TCHAR[256];
        DWORD dw = GetCurrentDirectory(len, t);
    GLFWwindow *ert=    glfwGetCurrentContext();
        std::cout << ert<<"\n";*/
        
      /* 
        if (ImGui::BeginDragDropTarget())
        {

            ImGui::EndDragDropTarget();
        }*/

       //GetWindowsDirectory
        
     /*   DWORD threadprocessId = 0;
        DWORD PID;
        PID = GetWindowThreadProcessId(GetForegroundWindow(), &threadprocessId);

        printf("pid: %d\n", PID);

        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_QUERY_INFORMATION |
            PROCESS_VM_READ,
            FALSE, threadprocessId);
        if (NULL != hProcess) {
            std::cout << "hProcess" << hProcess << "\n";
            TCHAR nameProc[1024];
            if (GetProcessImageFileName(hProcess, nameProc, sizeof(nameProc) / sizeof(*nameProc)) == 0) {
                std::cout << "GetProcessImageFileName Error";
            }
            else {
                std::wcout << "nameProcess " << nameProc;
            }

        }
        else {
            printf("OpenProcess(%i) failed, error: %i\n",
                PID, (int)GetLastError());
        }*/
        EditorTab::ScaleX = gridX;
        EditorTab::ScaleY = gridY;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
      
        glfwPollEvents();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        ImGui::BeginMainMenuBar();
        ImGui::EndMainMenuBar();

            input.Update();
            svTab.Update();
             hTab.Update();
            prTab.Update();
            toolsTab.Update();
            propTab.Update();


       
           ImGui::Begin("ShaderEditor");
       
            ImGui::PushStyleColor(ImGuiCol_ChildBg, (ImVec4)ImColor::HSV( 7.0f, 0.6f, 0.6f));
            ImGui::BeginChild("Node", ImVec2(50,80), true);
            ImGui::Button("AAAAAAAAa", ImVec2(100, 30));
            if (ImGui::BeginDragDropTarget())
            {


                ImGui::EndDragDropTarget();
            }

            ImGui::PopStyleColor();
            ImGui::EndChild();
            ImGui::End();
       
        ImGui::Render();
        glfwGetWindowSize(window, &actualWindowWidth, &actualWindowHeight);        
      /*  stageRenderer->Render(*cam, 800, 600);*/
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, actualWindowWidth, actualWindowHeight);
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // --- rendering loop
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        glfwSwapBuffers(window);

        gridX = actualWindowWidth / 10.0f;
        gridY = actualWindowHeight / 10.0f;
    }
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    if (window != NULL) { glfwDestroyWindow(window); }
    glfwTerminate();

}
