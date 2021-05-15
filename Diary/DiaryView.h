
// DiaryView.h : CDiaryView Ŭ������ �������̽�
//

#pragma once
#include "resource.h"
#include "DataSet.h"
#include "DiaryDoc.h"
#include "Change.h"
#include "LoginDlg.h"
#include "Diary.h"
#include "MainFrm.h"
#include "afxdtctl.h"
#include "afxwin.h"
#include "atlimage.h"



#define MOVE_FIRST_RECORD 1
#define MOVE_PREV_RECORD 2
#define MOVE_NEXT_RECORD 3
#define MOVE_LAST_RECORD 4

class CDiaryView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CDiaryView();
	DECLARE_DYNCREATE(CDiaryView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_DIARY_FORM };
#endif

// Ư���Դϴ�.
public:
	CDiaryDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CDiaryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CDataSet m_dbSet;
	DbCommand m_command;
	afx_msg void OnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult);
	CMonthCalCtrl m_ctrlCalender;
	bool m_bMoveRecord;
	int m_nTotal;
	int m_nMoveCount;
	void GetDataFromDb(int nMoveRecord);
	CString m_strText;
	CString strday;
	afx_msg void OnEnChangeEditText();
	afx_msg void OnClickedButtonSave();
	BOOL PreTranslateMessage(MSG * pMsg);
	CEdit m_Text;
	CString m_strDBID;
	CString m_strDay;
	bool m_bSave = false;
	afx_msg void OnChangepassword();
	bool m_bViewChange;
	CChange m_dlgChange;
	void Change(CString strQuery);
	void Check(CString m_strPassword);
	CStatic m_Img;
	afx_msg void OnClickedButtonInsert();
	afx_msg void OnClickedButtonDelete();
	virtual void OnDraw(CDC* /*pDC*/);
	bool m_bSelectImg;
	CString m_strImgPath;
	CImage m_bmpBitmap;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CStatic m_WeatherC;
	CStatic m_WeatherLC;
	CStatic m_WeatherR;
	CStatic m_WeatherS;
	CStatic m_WeatherSUNNY;
	CStatic m_WeatherW;
//	CString m_WeatherState;
	afx_msg void OnRadioCloudy();
	afx_msg void OnRadioLcloudy();
	afx_msg void OnRadioRain();
	afx_msg void OnRadioSnow();
	afx_msg void OnRadioSunny();
	afx_msg void OnRadioWindy();
//	int m_nWeatherState;
	CString m_WeatherState;
	afx_msg void OnButtonPink();
	afx_msg void OnButtonBlue();
	CString color;
	void refresh();
	afx_msg void OnClose();
};

#ifndef _DEBUG  // DiaryView.cpp�� ����� ����
inline CDiaryDoc* CDiaryView::GetDocument() const
   { return reinterpret_cast<CDiaryDoc*>(m_pDocument); }
#endif

