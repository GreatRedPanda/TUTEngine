#include "WindowsOle.h"
//#include <shellapi.h>
#include "DataDragNDrop.h"
#include <wtypes.h>
#include <tchar.h>
//#include <algorithm>
//#include <numeric>
#include <future>
//#include <string>
//#include <mutex>
using namespace std;
WindowsOle* WindowsOle::WindowsOleInstance = nullptr;

bool WindowsOle::isInDragProcess=false;
void WindowsOle::dragTask()
{
    IDataObject* pdto = new CTinyDataObject();
    if (pdto) {
        IDropSource* pds = new CDropSource();
        if (pds) {
            DWORD dwEffect;
            DoDragDrop(pdto, pds, DROPEFFECT_COPY, &dwEffect);
            pds->Release();
        }
        pdto->Release();
       isInDragProcess = false;
    }
}
WindowsOle::WindowsOle()
{
    WindowsOleInstance = this;
    OleInitialize(NULL);

}
void WindowsOle::dragTest()
{}
WindowsOle::~WindowsOle()
{
    OleUninitialize();

}

void WindowsOle::DragDocument()
{
    if (!isInDragProcess)
    {
        isInDragProcess = true;
       
       // auto a3 = async( &WindowsOle::dragTest, this);
       // std::thread t(dragTask);
       // t.join();
    }
}

