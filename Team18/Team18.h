// Team18.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� ����

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"

class CTeam18App : public CWinApp
{
public:
	CTeam18App();

// ������
	public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};

extern CTeam18App theApp;