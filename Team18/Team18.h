// Team18.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"

class CTeam18App : public CWinApp
{
public:
	CTeam18App();

// 재정의
	public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};

extern CTeam18App theApp;