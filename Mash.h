// Mash.h : main header file for the MASH application
//

#if !defined(AFX_MASH_H__E53430A3_39B5_4499_A1EB_4C1FE5A0629F__INCLUDED_)
#define AFX_MASH_H__E53430A3_39B5_4499_A1EB_4C1FE5A0629F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMashApp:
// See Mash.cpp for the implementation of this class
//

class CMashApp : public CWinApp
{
public:
	CMashApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMashApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMashApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MASH_H__E53430A3_39B5_4499_A1EB_4C1FE5A0629F__INCLUDED_)
