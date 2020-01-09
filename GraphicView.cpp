
// GraphicView.cpp: CGraphicView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "resource.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Graphic.h"
#endif

#include "GraphicDoc.h"
#include "GraphicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CGraph.h"


// CGraphicView

IMPLEMENT_DYNCREATE(CGraphicView, CScrollView)

BEGIN_MESSAGE_MAP(CGraphicView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(IDM_DOT, &CGraphicView::OnDot)
	ON_COMMAND(IDM_LINE, &CGraphicView::OnLine)
	ON_COMMAND(IDM_RECTANGLE, &CGraphicView::OnRectangle)
	ON_COMMAND(IDM_ELLIPSE, &CGraphicView::OnEllipse)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(IDM_SETTING, &CGraphicView::OnSetting)
	ON_COMMAND(IDM_COLOR, &CGraphicView::OnColor)
	ON_COMMAND(IDM_FONT, &CGraphicView::OnFont)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
//	ON_COMMAND(ID_FILE_SAVE, &CGraphicView::OnFileSave)
//	ON_COMMAND(ID_FILE_OPEN, &CGraphicView::OnFileOpen)
	ON_COMMAND(IDM_FILE_READ, &CGraphicView::OnFileRead)
	ON_COMMAND(IDM_FILE_WRITE, &CGraphicView::OnFileWrite)
END_MESSAGE_MAP()

// CGraphicView 构造/析构

CGraphicView::CGraphicView() noexcept
{
	m_ptOrigin = 0;
	m_nDrawType = 0;
	m_nLineWidth = 0;
	m_clr = RGB(255, 0, 0);
	m_strFontName = "";
	
	m_dcMetaFile.CreateEnhanced(NULL, NULL, NULL, NULL);
}

CGraphicView::~CGraphicView()
{
	for (int i = 0; i < m_ptrArray.GetSize(); i++) {
		delete m_ptrArray.GetAt(i);
	}
}

BOOL CGraphicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CGraphicView 绘图

void CGraphicView::OnDraw(CDC* pDC)
{
	CGraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	/*
	CFont* pOldFont = pDC->SelectObject(&m_font);
	pDC->TextOut(0, 0, m_strFontName);
	*/
	/*CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush* pOldBrush = pDC->SelectObject(pBrush);

	for (int i = 0; i < m_ptrArray.GetSize(); i++) {
		switch (((CGraph*)m_ptrArray.GetAt(i))->m_nDrawType)
		{
		case 1:
			pDC->SetPixel(((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd, RGB(0, 0, 0));
			break;

		case 2:
			pDC->MoveTo(((CGraph*)m_ptrArray.GetAt(i))->m_ptOrign);
			pDC->LineTo(((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd);
			break;
		case 3:
			pDC->Rectangle(CRect(((CGraph*)m_ptrArray.GetAt(i))->m_ptOrign, ((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd));
			break;
		case 4:
			pDC->Ellipse(CRect(((CGraph*)m_ptrArray.GetAt(i))->m_ptOrign, ((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd));
			break;
		}
	}
	pDC->SelectObject(pOldBrush);
	*/

	//HENHMETAFILE hmetaFile;
	//hmetaFile = m_dcMetaFile.CloseEnhanced();

	CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcCompatible, 0, 0, SRCCOPY);
	/*
	rect.left = rect.right / 4;
	rect.right = 3 * rect.right / 4;
	rect.top = rect.bottom / 4;
	rect.bottom = 3 * rect.bottom / 4;

	pDC->PlayMetaFile(hmetaFile, &rect);
	m_dcMetaFile.CreateEnhanced(NULL, NULL, NULL, NULL);
	m_dcMetaFile.PlayMetaFile(hmetaFile, &rect);
	DeleteEnhMetaFile(hmetaFile);
	*/
}


// CGraphicView 打印

BOOL CGraphicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGraphicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGraphicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CGraphicView 诊断

#ifdef _DEBUG
void CGraphicView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphicView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGraphicDoc* CGraphicView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicDoc)));
	return (CGraphicDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicView 消息处理程序


void CGraphicView::OnDot()
{
	m_nDrawType = 1;
	m_nLineStyle = 0;

}


void CGraphicView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 2;

}


void CGraphicView::OnRectangle()
{
	m_nDrawType = 3;

}


void CGraphicView::OnEllipse()
{
	m_nDrawType = 4;

}


void CGraphicView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_ptOrigin = point;

	CScrollView::OnLButtonDown(nFlags, point);
}


void CGraphicView::OnLButtonUp(UINT nFlags, CPoint point)
{

	CClientDC dc(this);

	//CPen pen(m_nLineStyle, m_nLineWidth, m_clr); //修改画笔的颜色和宽度
	//CPen* oldPen = dc.SelectObject(&pen);//修改后要选用
	//m_dcMetaFile.SelectObject(&pen);

	CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//设置画刷为透明
	//CBrush* POldBrush = dc.SelectObject(pBrush);
	//m_dcMetaFile.SelectObject(pBrush);

	if (!m_dcCompatible.m_hDC) {
		m_dcCompatible.CreateCompatibleDC(&dc);
		CRect rect;
		GetClientRect(&rect);
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		m_dcCompatible.SelectObject(&bitmap);
		m_dcCompatible.BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);
		m_dcCompatible.SelectObject(pBrush);
	
	}

	switch (m_nDrawType)
	{
	case 1:
		m_dcCompatible.SetPixel(point,m_clr);
		break;

	case 2:
		m_dcCompatible.MoveTo(m_ptOrigin);
		m_dcCompatible.LineTo(point);
		break;

	case 3:
		m_dcCompatible.Rectangle(CRect(m_ptOrigin, point));
		break;

	case 4:
		m_dcCompatible.Ellipse(CRect(m_ptOrigin, point));
		break;
	
	}
	//dc.SelectObject(oldPen);
	//dc.SelectObject(POldBrush);
	/* 这样定义会存在析构，然后数据丢失，并没有保存到图形
	CGraph graph(m_nDrawType, m_ptOrigin, point);
	m_ptrArray.Add(&graph); */

	//这样做就是直接绑定 数据本身的地址，就算析构了也能找到该数据
	//CGraph* pGraph = new CGraph(m_nDrawType, m_ptOrigin, point);
//	m_ptrArray.Add(pGraph);

	//OnPrepareDC(&dc);
	//dc.DPtoLP(&m_ptOrigin);
	//dc.DPtoLP(&point);
	//CGraph* pGraph = new CGraph(m_nDrawType, m_ptOrigin, point);
	//	m_ptrArray.Add(pGraph);

	CScrollView::OnLButtonUp(nFlags, point);
}


void CGraphicView::OnSetting()
{
	CSettingDlg dlg; //通过新建的对话框添加新的类，然后用这个新的类为对象，
	//在处理事件的时候弹出新的对话框
	dlg.m_nLineWidth = m_nLineWidth;// 将视类保存的线宽数据传回给新打开的设置窗口，就不用每次都初始化
	dlg.m_clr = m_clr;
	dlg.m_nLineStyle = m_nLineStyle; //跟上面的一样
	if (IDOK == dlg.DoModal()) {
		m_nLineWidth = dlg.m_nLineWidth;
		m_nLineStyle = dlg.m_nLineStyle;
	}

}


void CGraphicView::OnColor()
{
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_RGBINIT; //这里要设置回用户选定的默认颜色 不能像线条宽度那样的方法，
	//这个类他有自己独特的标记符，所以需要用这种方式来保存用户的diy
	if (IDOK == dlg.DoModal()) {
		m_clr = dlg.m_cc.rgbResult;
	}
}


void CGraphicView::OnFont()
{
	CFontDialog dlg;
	if (IDOK == dlg.DoModal()) { 
		//要先判断新建的字体对象有没有与别的字体关联，如果有关联的话就要先解绑
		if(m_font.m_hObject){
			m_font.DeleteObject();
		m_font.CreateFontIndirect(dlg.m_cf.lpLogFont);
		m_strFontName = dlg.m_cf.lpLogFont->lfFaceName;
		Invalidate();
		}
	}

}


BOOL CGraphicView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);

	BITMAP bmp;
	bitmap.GetBitmap(&bmp);

	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);

	dcCompatible.SelectObject(&bitmap);

	CRect rect;
	GetClientRect(&rect);
	//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcCompatible, 0, 0, SRCCOPY);
	
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dcCompatible, 0, 0,bmp.bmWidth,bmp.bmHeight, SRCCOPY);
	//用这个方法实现的位图 可以拉伸*/
	return TRUE;
}


void CGraphicView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CScrollView::OnPaint()

	OnPrepareDC(&dc);
	OnDraw(&dc);
}


void CGraphicView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT, CSize(3000,3000));
	// TODO: 在此添加专用代码和/或调用基类
}


//void CGraphicView::OnFileSave()
//{
//	HENHMETAFILE hmetaFile;
//	hmetaFile = m_dcMetaFile.CloseEnhanced();
//	HENHMETAFILE hemfCopy = CopyEnhMetaFile(hmetaFile, L"meta.emf");
//	m_dcMetaFile.CreateEnhanced(NULL, NULL, NULL, NULL);
//	DeleteEnhMetaFile(hmetaFile);
//	DeleteEnhMetaFile(hemfCopy);
//
//
//}


//void CGraphicView::OnFileOpen()
//{
//
//	CRect rect;
//	GetClientRect(&rect);
//	rect.left = rect.right / 4;
//	rect.right = 3 * rect.right / 4;
//	rect.top = rect.bottom / 4;
//	rect.bottom = 3 * rect.bottom / 4;
//
//	HENHMETAFILE hmetaFile;
//	hmetaFile = GetEnhMetaFile(L"meta.emf");
//	m_dcMetaFile.PlayMetaFile(hmetaFile, &rect);
//	DeleteEnhMetaFile(hmetaFile);
//	Invalidate();
//
//}


void CGraphicView::OnFileRead()
{
//构造cfile文件对象
	CFile file(L"1.txt", CFile::modeRead);
	//构造存档对象
	CArchive ar(&file, CArchive::load);
	int i;
	char ch;
	float f;
	CString str;
	CString strResult;

	//读取数据
	ar >> i >> ch >> f >> str;
	strResult.Format(L"%d,%c,%f,%s", i, ch, f, str);
	MessageBox(strResult);

}


void CGraphicView::OnFileWrite()
{
//构造CFile文件对象
	CFile file(L"1.txt", CFile::modeCreate | CFile::modeWrite);

	CArchive ar(&file, CArchive::store);

	int i = 4;
	char ch = 'a';
	float f = 1.3f;
	CString str("www.baidu.com");
	//保存数据
	ar << i << ch <<f<< str;
}
