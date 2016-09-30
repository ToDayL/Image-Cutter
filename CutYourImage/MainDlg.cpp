// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CutYourImage.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include <opencv2\opencv.hpp>

// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
{
	if (!m_show.empty())
	{
		m_show.release();
	}

	m_drawRect = cv::Rect(0, 0, 0, 0);
}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	//ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_NEXT, &CMainDlg::OnBnClickedNext)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序

void CMainDlg::DrawPicToHDC(const cv::Mat &cvImg, CDC *pDC, const cv::Point &insert)
{
	// Get the HDC handle information from the ID passed
	HDC hDCDst = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(IDC_IMAGEAREA)->GetClientRect(&rect);
	cv::Size winSize(rect.right, rect.bottom);
	cv::Size deltwinSize(rect.right, rect.bottom);
	int lineByte = (winSize.width * 3 + 3) / 4 * 4;
	unsigned char* pdata = new unsigned char[winSize.height*lineByte];
	unsigned char* ppdata = pdata;
	
	// Resize the source to the size of the destination image if necessary
	int i_cols = cvImg.cols;
	int i_rows = cvImg.rows;

	cv::Mat cvImgTmp(deltwinSize, CV_8UC3);
	cvImgTmp.setTo(cv::Scalar(240, 240, 240));

	for (int i = 0, m = insert.y; i < i_rows; i++, m++)
	{
		for (int j = 0, n = insert.x; j < i_cols; j++, n++)
		{
			if (m >= 0 && n >= 0 && m < winSize.height &&n < winSize.width)
			{
				cvImgTmp.at<cv::Vec3b>(i, j) = cvImg.at<cv::Vec3b>(i, j);
			}
		}
	}

	// Rotate the image
	cv::flip(cvImgTmp, cvImgTmp, 0);

	for (int i = 0; i < winSize.height; i++)
	{
		memcpy(ppdata, (cvImgTmp.data + i*winSize.width * 3), lineByte);
		ppdata += lineByte;
	}
	
	// Initialize the BITMAPINFO structure
	BITMAPINFO bitInfo;
	bitInfo.bmiHeader.biBitCount = 24;
	bitInfo.bmiHeader.biWidth = winSize.width;
	bitInfo.bmiHeader.biHeight = winSize.height;
	bitInfo.bmiHeader.biPlanes = 1;
	bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo.bmiHeader.biCompression = BI_RGB;
	bitInfo.bmiHeader.biClrImportant = 0;
	bitInfo.bmiHeader.biClrUsed = 0;
	bitInfo.bmiHeader.biSizeImage = 0;
	bitInfo.bmiHeader.biXPelsPerMeter = 0;
	bitInfo.bmiHeader.biYPelsPerMeter = 0;

	// Add header and OPENCV image's data to the HDC
	StretchDIBits(hDCDst, 0, 0,
		winSize.width, winSize.height, 0, 0,
		winSize.width, winSize.height,
		pdata, &bitInfo, DIB_RGB_COLORS, SRCCOPY);

	delete[] pdata;
	ReleaseDC(pDC);
}


void CMainDlg::DBBuffering(CDC *pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	CBitmap memBitmap;

	CRect rect;
	GetDlgItem(IDC_IMAGEAREA)->GetClientRect(&rect);
	memBitmap.CreateCompatibleBitmap(pDC, rect.right, rect.bottom);
	CBitmap *pOldBit = memDC.SelectObject(&memBitmap);
	memDC.FillSolidRect(0, 0, rect.right, rect.bottom, RGB(240, 240, 240));
	DrawPicToHDC(m_show, &memDC, cv::Size(0, 0));
	pDC->BitBlt(0, 0, rect.right, rect.bottom, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBit);
	memBitmap.DeleteObject();
	memDC.DeleteDC();
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
		
	return 0;
}

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//SetWindowPos(&wndNoTopMost, 50, 50, 1000, 700, SWP_SHOWWINDOW);

	return true;
}

void CMainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(240, 240, 240));

	CWnd *p_image = GetDlgItem(IDC_IMAGEAREA);
	if (p_image != NULL)
	{
		CDC *pshow = p_image->GetDC();
		//drawToDC(m_show, pshow, m_drawRect);

		CRect CDCSize;
		GetDlgItem(IDC_IMAGEAREA)->GetClientRect(&CDCSize);

		m_show =  cv::imread("C:\\Users\\lijin\\Pictures\\lena.jpg");
		cv::resize(m_show, m_show, cv::Size(CDCSize.right - CDCSize.left, CDCSize.bottom - CDCSize.top));

		DBBuffering(pshow);
	}
}


void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码

	CRect rWindow;
	GetClientRect(&rWindow);

	CWnd *p_image = GetDlgItem(IDC_IMAGEAREA);

	CRect rImage = rWindow;
	if (p_image != NULL)
	{
		rImage.bottom = rImage.bottom - 50;
		p_image->MoveWindow(rImage);
	}
	
	CRect rnext = rWindow;
	CWnd *p_next = GetDlgItem(IDC_NEXT);
	if (p_next != NULL)
	{
		rnext.top = rImage.bottom + 10;
		rnext.bottom = rnext.top + 30;
		rnext.right = rImage.right - 10;
		rnext.left = rnext.right - 60;
		p_next->MoveWindow(rnext);
	}
	
}


void CMainDlg::OnBnClickedNext()
{
	// TODO:  在此添加控件通知处理程序代码
	//cv::imshow("m",m_show);
	CDC* pDC = GetDlgItem(IDC_IMAGEAREA)->GetDC();
	DBBuffering(pDC);
}
