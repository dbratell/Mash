// MashView.cpp : implementation of the CMashView class
//

#include "stdafx.h"
#include "Mash.h"

#include "MashDoc.h"
#include "MashView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMashView

IMPLEMENT_DYNCREATE(CMashView, CView)

BEGIN_MESSAGE_MAP(CMashView, CView)
	//{{AFX_MSG_MAP(CMashView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMashView construction/destruction

CMashView::CMashView()
{
	// TODO: add construction code here

}

CMashView::~CMashView()
{
}

BOOL CMashView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMashView drawing

void CMashView::OnDraw(CDC* pDC)
{
	CMashDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMashView printing

BOOL CMashView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMashView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMashView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMashView diagnostics

#ifdef _DEBUG
void CMashView::AssertValid() const
{
	CView::AssertValid();
}

void CMashView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMashDoc* CMashView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMashDoc)));
	return (CMashDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMashView message handlers
