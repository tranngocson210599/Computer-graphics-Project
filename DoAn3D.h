
// DoAn3D.h : main header file for the DoAn3D application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// DoAn3DApp:
// See DoAn3D.cpp for the implementation of this class
//

class DoAn3DApp : public CWinAppEx
{
public:
	DoAn3DApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern DoAn3DApp theApp;
