#pragma once
#include <Windows.h>

bool CMSTPLUA(PCCH ExecutableFilePathA);

// Microsoft Connection Manager Profile Installer (CMSTP.exe)

// OleView.NET displays the following Interface Name for CMSTPLUA
typedef interface ICMLuaUtil ICMLuaUtil;

// Virtual Method Table for Interface {6EDD6D74-C007-4E75-B76A-E5740995E24C}
struct ICMLuaUtilVtbl {
    BEGIN_INTERFACE
    // IUnknown
    HRESULT(STDMETHODCALLTYPE* QueryInterface)(ICMLuaUtil* This, REFIID riid, _COM_Outptr_  void** ppvObject);
    ULONG(STDMETHODCALLTYPE* AddRef)(ICMLuaUtil* This);
    ULONG(STDMETHODCALLTYPE* Release)(ICMLuaUtil* This);
    // ICMLuaUtil
    HRESULT(STDMETHODCALLTYPE* Method1)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method2)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method3)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method4)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method5)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method6)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* ShellExec)(ICMLuaUtil* This, LPCTSTR lpFile, LPCTSTR lpParameters, LPCTSTR lpDirectory, ULONG fMask, ULONG nShow);
    HRESULT(STDMETHODCALLTYPE* Method8)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method9)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method10)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method11)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method12)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method13)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method14)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method15)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method16)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method17)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method18)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method19)(ICMLuaUtil* This);
    HRESULT(STDMETHODCALLTYPE* Method20)(ICMLuaUtil* This);
    END_INTERFACE
};
using PICMLuaUtilVtbl = ICMLuaUtilVtbl*;

interface ICMLuaUtil
{
    CONST_VTBL struct ICMLuaUtilVtbl* lpVtbl;
};