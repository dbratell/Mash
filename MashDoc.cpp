// MashDoc.cpp : implementation of the CMashDoc class
//

#include "stdafx.h"
#include "Mash.h"

#include "MashDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMashDoc

IMPLEMENT_DYNCREATE(CMashDoc, CDocument)

BEGIN_MESSAGE_MAP(CMashDoc, CDocument)
	//{{AFX_MSG_MAP(CMashDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMashDoc construction/destruction

CMashDoc::CMashDoc()
{
	// TODO: add one-time construction code here

}

CMashDoc::~CMashDoc()
{
}

BOOL CMashDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	// Open file dialog
	CFileDialog filedialog(TRUE, NULL, NULL, 
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, 
		NULL, NULL);
	if(filedialog.DoModal()) 
	{
		CString path = filedialog.GetPathName();
		// CString file = filedialog.GetFileName();
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMashDoc serialization

void CMashDoc::Serialize(CArchive& ar)
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
// CMashDoc diagnostics

#ifdef _DEBUG
void CMashDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMashDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMashDoc commands
