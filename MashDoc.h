// MashDoc.h : interface of the CMashDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MASHDOC_H__84F4BE31_2BAC_4DCA_BF70_2B00D8713A45__INCLUDED_)
#define AFX_MASHDOC_H__84F4BE31_2BAC_4DCA_BF70_2B00D8713A45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMashDoc : public CDocument
{
protected: // create from serialization only
	CMashDoc();
	DECLARE_DYNCREATE(CMashDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMashDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMashDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMashDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MASHDOC_H__84F4BE31_2BAC_4DCA_BF70_2B00D8713A45__INCLUDED_)
