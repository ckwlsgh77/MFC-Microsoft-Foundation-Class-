
#pragma once
#include "DataSet.h"
//#include "DiaryView.h"


// CChange ��ȭ �����Դϴ�.

class CChange : public CDialogEx
{
	DECLARE_DYNAMIC(CChange)

public:
	CChange(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChange();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonChange();
	CString m_strChange;
//	DbCommand m_command2;
//	CDataSet m_dbSet2;
//	CDiaryView* pdlgView;
//	CDiaryView pdlgView;
//	CDiaryView pdlgView;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
