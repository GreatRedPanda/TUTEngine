#include "DataDragNDrop.h"
#include <iostream>

CDropSource::CDropSource() :m_cRef(1)
{

}
HRESULT  CDropSource::QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState)
{
    if (fEscapePressed) return DRAGDROP_S_CANCEL;
    if (!(grfKeyState & (MK_LBUTTON | MK_RBUTTON)))
        return DRAGDROP_S_DROP;


    return S_OK;
}
HRESULT  CDropSource::GiveFeedback(DWORD dwEffect)
{
    return DRAGDROP_S_USEDEFAULTCURSORS;
}
ULONG  CDropSource::AddRef()
{
    return ++m_cRef;
}
ULONG  CDropSource::Release()
{
    ULONG cRef = --m_cRef;
    if (cRef == 0) delete this;
    return cRef;

}
HRESULT  CDropSource::QueryInterface(REFIID riid, void** ppvObj)
{
    IUnknown* punk = NULL;
    if (riid == IID_IUnknown) {
        punk = static_cast<IUnknown*>(this);
    }
    else if (riid == IID_IDataObject) {
        punk = static_cast<IDropSource*>(this);
    }
    *ppvObj = punk;
    if (punk) {
        punk->AddRef();
        return S_OK;
    }
    else {
        return E_NOINTERFACE;
    }


}









int CTinyDataObject::GetDataIndex(const FORMATETC* pfe)
{
    for (int i = 0; i < ARRAYSIZE(m_rgfe); i++) {
        if (pfe->cfFormat == m_rgfe[i].cfFormat &&
            (pfe->tymed & m_rgfe[i].tymed) &&
            pfe->dwAspect == m_rgfe[i].dwAspect &&
            pfe->lindex == m_rgfe[i].lindex) {
            return i;
        }
    }
    return DATA_INVALID;
}

HRESULT CreateHGlobalFromBlob(const void* pvData, SIZE_T cbData, UINT uFlags, HGLOBAL* phglob)
{
    HGLOBAL hglob = GlobalAlloc(uFlags, cbData);
    if (hglob) {
        void* pvAlloc = GlobalLock(hglob);
        if (pvAlloc) {
            CopyMemory(pvAlloc, pvData, cbData);
            GlobalUnlock(hglob);
        }
        else {
            GlobalFree(hglob);
            hglob = NULL;
        }
    }
    *phglob = hglob;
    return hglob ? S_OK : E_OUTOFMEMORY;
}

HRESULT CTinyDataObject::QueryInterface(REFIID riid, void** ppvObj)
{
    IUnknown* punk = NULL;
    if (riid == IID_IUnknown) {
        punk = static_cast<IUnknown*>(this);
    }
    else if (riid == IID_IDataObject) {
        punk = static_cast<IDataObject*>(this);
    }
    *ppvObj = punk;
    if (punk) {
        punk->AddRef();
        return S_OK;
    }
    else {
        return E_NOINTERFACE;
    }
}
ULONG CTinyDataObject::AddRef()
{
    return ++m_cRef;

}
ULONG CTinyDataObject::CTinyDataObject::Release()
{

    ULONG cRef = --m_cRef;
    if (cRef == 0) delete this;
    return cRef;

}
// IDataObject
CHAR c_szURL[] = "http://www.microsoft.com/";
HRESULT CTinyDataObject::GetData(FORMATETC* pfe, STGMEDIUM* pmed)
{
    // CHAR c_szURL[] = "http://www.microsoft.com/";
    ZeroMemory(pmed, sizeof(*pmed));
    switch (GetDataIndex(pfe)) {
    case DATA_TEXT:
        pmed->tymed = TYMED_HGLOBAL;
        return CreateHGlobalFromBlob(c_szURL, sizeof(c_szURL),
            GMEM_MOVEABLE, &pmed->hGlobal);
    }
    return DV_E_FORMATETC;
}
HRESULT CTinyDataObject::GetDataHere(FORMATETC* pfe, STGMEDIUM* pmed)
{
    return E_NOTIMPL;
}
HRESULT CTinyDataObject::QueryGetData(FORMATETC* pfe)
{
    return GetDataIndex(pfe) == DATA_INVALID ? S_FALSE : S_OK;

}
HRESULT CTinyDataObject::GetCanonicalFormatEtc(FORMATETC* pfeIn, FORMATETC* pfeOut)
{
    *pfeOut = *pfeIn;
    pfeOut->ptd = NULL;
    return DATA_S_SAMEFORMATETC;

}
HRESULT CTinyDataObject::SetData(FORMATETC* pfe, STGMEDIUM* pmed, BOOL fRelease)
{
    return E_NOTIMPL;
}
HRESULT CTinyDataObject::EnumFormatEtc(DWORD dwDirection, LPENUMFORMATETC* ppefe)
{
    if (dwDirection == DATADIR_GET) {
        return SHCreateStdEnumFmtEtc(ARRAYSIZE(m_rgfe), m_rgfe, ppefe);
    }
    *ppefe = NULL;
    return E_NOTIMPL;
}
HRESULT CTinyDataObject::DAdvise(FORMATETC* pfe, DWORD grfAdv, IAdviseSink* pAdvSink, DWORD* pdwConnection)
{
    return OLE_E_ADVISENOTSUPPORTED;
}
HRESULT CTinyDataObject::DUnadvise(DWORD dwConnection)
{
    return OLE_E_ADVISENOTSUPPORTED;
}
HRESULT CTinyDataObject::EnumDAdvise(LPENUMSTATDATA* ppefe)
{
    return OLE_E_ADVISENOTSUPPORTED;
}
void SetFORMATETC(FORMATETC* pfe, UINT cf, TYMED tymed = TYMED_HGLOBAL, LONG lindex = -1,
    DWORD dwAspect = DVASPECT_CONTENT, DVTARGETDEVICE* ptd = NULL)
{
    pfe->cfFormat = (CLIPFORMAT)cf;
    pfe->tymed = tymed;
    pfe->lindex = lindex;
    pfe->dwAspect = dwAspect;
    pfe->ptd = ptd;
}
CTinyDataObject::CTinyDataObject() : m_cRef(1)
{
    SetFORMATETC(&m_rgfe[DATA_TEXT], CF_TEXT);
}