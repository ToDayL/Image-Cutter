#pragma once
#include <opencv2\core.hpp>

// CMainDlg 对话框

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDlg();

// 对话框数据
	enum { IDD = IDD_MAINDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	int m_window_width;
	int m_window_height;
	int m_HDC_width;
	int m_HDC_height;

	cv::Mat m_show;
	cv::Rect m_drawRect;

private:
	void CMainDlg::DrawPicToHDC(const cv::Mat &cvImg, CDC *pDC, const cv::Point &insert);
	void DBBuffering(CDC *pDC);
	BOOL OnInitDialog();
public:
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedNext();
};
