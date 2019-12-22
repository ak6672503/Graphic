
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


// CGraphicView

IMPLEMENT_DYNCREATE(CGraphicView, CView)

BEGIN_MESSAGE_MAP(CGraphicView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
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
END_MESSAGE_MAP()

// CGraphicView 构造/析构

CGraphicView::CGraphicView() noexcept
{
	m_ptOrigin = 0;
	m_nDrawType = 0;
	m_nLineWidth = 0;
	m_clr = RGB(255, 0, 0);
	m_strFontName = "";
	
}

CGraphicView::~CGraphicView()
{
}

BOOL CGraphicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGraphicView 绘图

void CGraphicView::OnDraw(CDC* pDC)
{
	CGraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFont* pOldFont = pDC->SelectObject(&m_font);
	pDC->TextOut(0, 0, m_strFontName);
	pDC->SelectObject(pOldFont);

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
	CView::AssertValid();
}

void CGraphicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
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

	CView::OnLButtonDown(nFlags, point);
}


void CGraphicView::OnLButtonUp(UINT nFlags, CPoint point)
{

	CClientDC dc(this);

	CPen pen(m_nLineStyle, m_nLineWidth, m_clr); //修改画笔的颜色和宽度
	CPen* oldPen = dc.SelectObject(&pen);//修改后要选用


	CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//设置画刷为透明
	CBrush* POldBrush = dc.SelectObject(pBrush);

	switch (m_nDrawType)
	{
	case 1:
		dc.SetPixel(point,m_clr);
		break;

	case 2:
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		break;

	case 3:
		dc.Rectangle(CRect(m_ptOrigin, point));
		break;

	case 4:
		dc.Ellipse(CRect(m_ptOrigin, point));
		break;
	default:
		break;
	}
	dc.SelectObject(oldPen);
	dc.SelectObject(POldBrush);
	CView::OnLButtonUp(nFlags, point);
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
	CBitmap bitmap;
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
	//用这个方法实现的位图 可以拉伸
	return TRUE;
}
