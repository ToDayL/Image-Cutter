#pragma once


// CMainDlg �Ի���

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainDlg();

// �Ի�������
	enum { IDD = IDD_MAINDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	int m_window_width;
	int m_window_height;
	int m_HDC_width;
	int m_HDC_height;
};
