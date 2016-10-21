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
	// The Dialog information
	int m_window_width;
	int m_window_height;
	int m_HDC_width;
	int m_HDC_height;

	// Image data
	cv::Mat m_origin;
	cv::Mat m_show;
	cv::Rect m_drawRect;
	int m_percentage = 100;

	// The bounding box data
	std::vector<cv::Rect> m_rects;

public:
	// Public information got from CutYourImageDlg
	std::string m_singlePath;
	std::vector<std::string> m_multyPath;
	bool m_positive;

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
private:


};
