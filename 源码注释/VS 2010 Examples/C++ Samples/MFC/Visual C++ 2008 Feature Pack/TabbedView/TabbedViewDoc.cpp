// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "TabbedView.h"

#include "TabbedViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabbedViewDoc

IMPLEMENT_DYNCREATE(CTabbedViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CTabbedViewDoc, CDocument)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabbedViewDoc construction/destruction

CTabbedViewDoc::CTabbedViewDoc()
{
	// TODO: add one-time construction code here

}

CTabbedViewDoc::~CTabbedViewDoc()
{
}

BOOL CTabbedViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTabbedViewDoc serialization

void CTabbedViewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTabbedViewDoc diagnostics

#ifdef _DEBUG
void CTabbedViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTabbedViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabbedViewDoc commands
