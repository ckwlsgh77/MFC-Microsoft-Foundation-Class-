// LoginDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Diary.h"
#include "DiaryView.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// LoginDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(LoginDlg, CDialogEx)

LoginDlg::LoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_strPassword(_T(""))
{

}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
	ON_BN_CLICKED(ID_BUTTON_OK, &LoginDlg::OnClickedButtonOk)
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// LoginDlg �޽��� ó�����Դϴ�.


void LoginDlg::OnClickedButtonOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CDiaryView *pView = (CDiaryView *)pFrame->GetActiveView();
	//CDiaryView *pView = ((CMainFrame *)AfxGetMainWnd())->GetActiveView();

	pView->Check(m_strPassword);
}


void LoginDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CDialogEx::OnClose();
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->OnClose();
	//CDiaryView *pView=(CDiaryView *)pFrame->GetActiveView();;
	//pView->OnClose();
}


BOOL LoginDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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


HBRUSH LoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
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
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


void LoginDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CDiaryView *pView = (CDiaryView *)pFrame->GetActiveView();
	int r = 255, g = 213, b = 210;

	if (pView->color == "0") {
		r = 154;
		g = 218;
		b = 255;
	}
	CDC dc;
	RECT rect;
	dc.Attach(lpDrawItemStruct->hDC);   // Get the Button DC to CDC

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


BOOL LoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if (pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
