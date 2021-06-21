#pragma once
#include <strsafe.h> 
#include <shlobj.h> 

class CDropSource : public IDropSource
{
private:
    ULONG m_cRef;
public:
    STDMETHODIMP QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState);
    STDMETHODIMP GiveFeedback(DWORD dwEffect);
    STDMETHODIMP QueryInterface(REFIID riid, void** ppvObj);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    CDropSource();


};
class CTinyDataObject : public IDataObject
{

private:
    enum {
        DATA_TEXT,
        DATA_NUM,
        DATA_INVALID = -1,
    };
    int GetDataIndex(const FORMATETC* pfe);


private:
    ULONG m_cRef;
    FORMATETC m_rgfe[DATA_NUM];

public:
    STDMETHODIMP QueryInterface(REFIID riid, void** ppvObj);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    // IDataObject
    STDMETHODIMP GetData(FORMATETC* pfe, STGMEDIUM* pmed);
    STDMETHODIMP GetDataHere(FORMATETC* pfe, STGMEDIUM* pmed);
    STDMETHODIMP QueryGetData(FORMATETC* pfe);
    STDMETHODIMP GetCanonicalFormatEtc(FORMATETC* pfeIn,
        FORMATETC* pfeOut);
    STDMETHODIMP SetData(FORMATETC* pfe, STGMEDIUM* pmed,
        BOOL fRelease);
    STDMETHODIMP EnumFormatEtc(DWORD dwDirection,
        LPENUMFORMATETC* ppefe);
    STDMETHODIMP DAdvise(FORMATETC* pfe, DWORD grfAdv,
        IAdviseSink* pAdvSink, DWORD* pdwConnection);
    STDMETHODIMP DUnadvise(DWORD dwConnection);
    STDMETHODIMP EnumDAdvise(LPENUMSTATDATA* ppefe);
    CTinyDataObject();
};
