// Change.cpp : 구현 파일입니다.
//

#include "stdafx.h"

#include "Diary.h"

#include "Change.h"

#include "afxdialogex.h"

#include "DiaryView.h"

#include "MainFrm.h"

// CChange 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChange, CDialogEx)
CChange::CChange(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_strChange(_T(""))
	//, pdlgView(NULL)
{

}

CChange::~CChange()
{
}

void CChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CHANGE, m_strChange);
}


BEGIN_MESSAGE_MAP(CChange, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CChange::OnClickedButtonChange)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CChange 메시지 처리기입니다.


void CChange::OnClickedButtonChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString temp,temp2;
	temp = m_strChange;
	temp2 = "9999.99.99";
	CString strQuery;
	strQuery.Format(_T("UPDATE dayimage SET pass = '%s' WHERE test = '9999.99.99'"),temp);



	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CDiaryView *pView = (CDiaryView *)pFrame->GetActiveView();
	//CDiaryView *pView = ((CMainFrame *)AfxGetMainWnd())->GetActiveView();
	CDiaryApp *pApp = (CDiaryApp*)AfxGetApp();


	pView->Change(strQuery);

	
	//AfxMessageBox(temp3);

	//if (pView->m_dbSet.Query(strQuery, &pView->m_command))
	//{
	//	CString temp;
	//	temp.Format(_T("변경되었습니다."));
	//	AfxMessageBox(temp);
	//	}

}


BOOL CChange::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CDiaryView *pView = (CDiaryView *)pFrame->GetActiveView();
	int r = 255, g = 228, b = 225;

	if (pView->color == "0") {
		r = 181;
		g = 215;
		b = 255;
	}
	CBrush backBrush(RGB(r, g, b));
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH CChange::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CDiaryView *pView = (CDiaryView *)pFrame->GetActiveView();
	int r = 255, g = 228, b = 225;

	if (pView->color == "0") {
		r = 181;
		g = 215;
		b = 255;
	}
	CBrush* m_Brush;
	m_Brush = new CBrush(RGB(r, g, b));

	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkColor(RGB(r, g, b));
		return hbr = (HBRUSH)(m_Brush->GetSafeHandle());
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CChange::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDC dc;
	RECT rect;
	dc.Attach(lpDrawItemStruct->hDC);   // Get the Button DC to CDC

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CDiaryView *pView = (CDiaryView *)pFrame->GetActiveView();
	int r = 255, g = 213, b = 210;

	if (pView->color == "0") {
		r = 154;
		g = 218;
		b = 255;
	}

	rect = lpDrawItemStruct->rcItem;     //Store the Button rect to our local rect.
	dc.Draw3dRect(&rect, RGB(255, 255, 255), RGB(0, 0, 0));
	dc.FillSolidRect(&rect, RGB(r, g, b));//Here you can define the required color to appear on the Button.

	UINT state = lpDrawItemStruct->itemState;  //This defines the state of the Push button either pressed or not. 
	if ((state & ODS_SELECTED))
		dc.DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);
	else
		dc.DrawEdge(&rect, EDGE_RAISED, BF_RECT);

	dc.SetBkColor(RGB(r, g, b));   //Setting the Text Background color
	dc.SetTextColor(RGB(0, 0, 0));     //Setting the Text Color

	TCHAR buffer[MAX_PATH];           //To store the Caption of the button.
	ZeroMemory(buffer, MAX_PATH);     //Intializing the buffer to zero
	::GetWindowText(lpDrawItemStruct->hwndItem, buffer, MAX_PATH); //Get the Caption of Button Window 

	dc.DrawText(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//Redraw the  Caption of Button Window 
	dc.Detach();  // Detach the Button DC
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


BOOL CChange::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if (pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
