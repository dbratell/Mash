// MashView.h : interface of the CMashView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MASHVIEW_H__278C1BB6_A133_4BD7_A3CA_34646DB9DB75__INCLUDED_)
#define AFX_MASHVIEW_H__278C1BB6_A133_4BD7_A3CA_34646DB9DB75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMashView : public CView
{
protected: // create from serialization only
	CMashView();
	DECLARE_DYNCREATE(CMashView)

// Attributes
public:
	CMashDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMashView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMashView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMashView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MashView.cpp
inline CMashDoc* CMashView::GetDocument()
   { return (CMashDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MASHVIEW_H__278C1BB6_A133_4BD7_A3CA_34646DB9DB75__INCLUDED_)
