
// Diary.h : Diary ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "LoginDlg.h"


// CDiaryApp:
// �� Ŭ������ ������ ���ؼ��� Diary.cpp�� �����Ͻʽÿ�.
//

class CDiaryApp : public CWinAppEx
{
public:
	CDiaryApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	LoginDlg dlg;
	DECLARE_MESSAGE_MAP()
//	LoginDlg dlg;
	void hidedlg();
	
	int a;
};

extern CDiaryApp theApp;
