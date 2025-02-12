// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

// MSMoneyDemo.h : main header file for the MSMONEY application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMSMoneyDemoApp:
// See MSMoneyDemo.cpp for the implementation of this class
//

class CMSMoneyDemoApp : public CWinAppEx
{
public:
	CMSMoneyDemoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();

	DECLARE_MESSAGE_MAP()
};


extern CMSMoneyDemoApp theApp;
