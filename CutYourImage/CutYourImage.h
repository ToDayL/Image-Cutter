
// CutYourImage.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCutYourImageApp: 
// �йش����ʵ�֣������ CutYourImage.cpp
//

class CCutYourImageApp : public CWinApp
{
public:
	CCutYourImageApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCutYourImageApp theApp;