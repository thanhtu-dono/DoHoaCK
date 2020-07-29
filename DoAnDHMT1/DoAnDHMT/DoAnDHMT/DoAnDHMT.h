
// DoAnDHMT.h : main header file for the DoAnDHMT application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDoAnDHMTApp:
// See DoAnDHMT.cpp for the implementation of this class
//

class CDoAnDHMTApp : public CWinAppEx
{
public:
	CDoAnDHMTApp() noexcept;


	// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDoAnDHMTApp theApp;
