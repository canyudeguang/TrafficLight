
// TrafficLight.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTrafficLightApp:
// �йش����ʵ�֣������ TrafficLight.cpp
//

class CTrafficLightApp : public CWinApp
{
public:
	CTrafficLightApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTrafficLightApp theApp;