// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CutYourImage.h"
#include "MainDlg.h"
#include "afxdialogex.h"


// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
{

}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMainDlg 消息处理程序

void CMainDlg::drawToDC(const cv::Mat &src, CDC *LPDC, const cv::Rect & pos)
{
	CBitmap memBitmap;
	CDC memDC;
	Gdiplus::Bitmap bitmap(src.cols, src.rows, src.cols*src.channels(), PixelFormat24bppRGB, (BYTE*)src.data);
	memDC.CreateCompatibleDC(LPDC);
	CBitmap *pOldBit = memDC.SelectObject(&memBitmap);
	Gdiplus::Graphics g(memDC.m_hDC);
	Gdiplus::Image *i = &bitmap;
	Gdiplus::Rect r(pos.x,pos.y,pos.width,pos.height);
	g.DrawImage(i, r);
	g.ReleaseHDC(memDC.m_hDC);
}

BOOL CMainDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}
