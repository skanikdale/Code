
// MultiView.cpp : implementation of the CMultiView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Multi.h"
#endif

#include "MultiDoc.h"
#include "MultiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMultiView

IMPLEMENT_DYNCREATE(CMultiView, CView)

BEGIN_MESSAGE_MAP(CMultiView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMultiView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMultiView construction/destruction

CMultiView::CMultiView()
{
	// TODO: add construction code here

}

CMultiView::~CMultiView()
{
}

BOOL CMultiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMultiView drawing

void CMultiView::OnDraw(CDC* /*pDC*/)
{
	CMultiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMultiView printing


void CMultiView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMultiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMultiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMultiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMultiView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMultiView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMultiView diagnostics

#ifdef _DEBUG
void CMultiView::AssertValid() const
{
	CView::AssertValid();
}

void CMultiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMultiDoc* CMultiView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMultiDoc)));
	return (CMultiDoc*)m_pDocument;
}
#endif //_DEBUG


// CMultiView message handlers
