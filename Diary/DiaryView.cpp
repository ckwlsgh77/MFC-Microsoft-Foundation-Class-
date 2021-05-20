
// DiaryView.cpp : CDiaryView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Diary.h"
#endif

#include "DiaryDoc.h"
#include "DiaryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDiaryView

IMPLEMENT_DYNCREATE(CDiaryView, CFormView)

BEGIN_MESSAGE_MAP(CDiaryView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &CDiaryView::OnSelchangeMonthcalendar1)
//	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDiaryView::OnBnClickedButtonSave)
ON_EN_CHANGE(IDC_EDIT_TEXT, &CDiaryView::OnEnChangeEditText)
ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDiaryView::OnClickedButtonSave)
ON_COMMAND(ID_CHANGEPASSWORD, &CDiaryView::OnChangepassword)
ON_BN_CLICKED(IDC_BUTTON_INSERT, &CDiaryView::OnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDiaryView::OnClickedButtonDelete)
ON_WM_ERASEBKGND()
ON_WM_CTLCOLOR()
//ON_WM_DRAWITEM()
ON_WM_DRAWITEM()
ON_COMMAND(IDC_RADIO_CLOUDY, &CDiaryView::OnRadioCloudy)
ON_COMMAND(IDC_RADIO_LCLOUDY, &CDiaryView::OnRadioLcloudy)
ON_COMMAND(IDC_RADIO_RAIN, &CDiaryView::OnRadioRain)
ON_COMMAND(IDC_RADIO_SNOW, &CDiaryView::OnRadioSnow)
ON_COMMAND(IDC_RADIO_SUNNY, &CDiaryView::OnRadioSunny)
ON_COMMAND(IDC_RADIO_WINDY, &CDiaryView::OnRadioWindy)
ON_COMMAND(ID_BUTTON_PINK, &CDiaryView::OnButtonPink)
ON_COMMAND(ID_BUTTON_BLUE, &CDiaryView::OnButtonBlue)
ON_WM_CLOSE()
END_MESSAGE_MAP()

// CDiaryView ����/�Ҹ�

CDiaryView::CDiaryView()
	: CFormView(IDD_DIARY_FORM)
	, m_bMoveRecord(false)
	, m_nTotal(0)
	, m_nMoveCount(0)
	, m_strText(_T(""))
	, strday(_T(""))
	, m_strDBID(_T(""))
	, m_strDay(_T(""))
	, m_bSave(false)
	, m_bViewChange(false)
	, m_bSelectImg(false)
	, m_strImgPath(_T(""))
	, m_WeatherState(_T(""))
	, color(_T("1"))
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	CString strQuery;
	CString check_color;
	check_color = "1";
	strQuery.Format(_T("SELECT * FROM dayimage"));
	m_command.Close();
	if (m_dbSet.Query(strQuery, &m_command))
	{
		m_command.MoveFirst();
		if (check_color == m_command.GetString(7))
			color = "1";
		else
			color = "0";
	}

}

CDiaryView::~CDiaryView()
{
}

void CDiaryView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_ctrlCalender);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_Text);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_Img);
	DDX_Control(pDX, IDC_STATIC_CLOUDY, m_WeatherC);
	DDX_Control(pDX, IDC_STATIC_LCOUDY, m_WeatherLC);
	DDX_Control(pDX, IDC_STATIC_RAIN, m_WeatherR);
	DDX_Control(pDX, IDC_STATIC_SNOW, m_WeatherS);
	DDX_Control(pDX, IDC_STATIC_SUNNY, m_WeatherSUNNY);
	DDX_Control(pDX, IDC_STATIC_WINDY, m_WeatherW);
}

BOOL CDiaryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.


	return CFormView::PreCreateWindow(cs);
}

void CDiaryView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	/*CString strQuery;
	strQuery.Format(_T("SELECT * FROM dayimage"));
	m_command.Close();

	if (m_dbSet.Query(strQuery, &m_command))
	{
		m_nTotal = 0;
		while (m_command.MoveNext() == S_OK)
		{
			m_nTotal++;
		}
		m_nMoveCount = 1;
		GetDataFromDb(MOVE_FIRST_RECORD);
		m_bMoveRecord = true;
	}*/

}

void CDiaryView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDiaryView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDiaryView ����

#ifdef _DEBUG
void CDiaryView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDiaryView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDiaryDoc* CDiaryView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDiaryDoc)));
	return (CDiaryDoc*)m_pDocument;
}
#endif //_DEBUG


// CDiaryView �޽��� ó����

void CDiaryView::refresh() {

	CTime select;
	CButton* pBt;
	m_strImgPath = "";
	pBt = (CButton*)GetDlgItem(IDC_RADIO_CLOUDY);
	pBt->SetCheck(FALSE);
	pBt = (CButton*)GetDlgItem(IDC_RADIO_LCLOUDY);
	pBt->SetCheck(FALSE);
	pBt = (CButton*)GetDlgItem(IDC_RADIO_RAIN);
	pBt->SetCheck(FALSE);
	pBt = (CButton*)GetDlgItem(IDC_RADIO_SNOW);
	pBt->SetCheck(FALSE);
	pBt = (CButton*)GetDlgItem(IDC_RADIO_SUNNY);
	pBt->SetCheck(FALSE);
	pBt = (CButton*)GetDlgItem(IDC_RADIO_WINDY);
	pBt->SetCheck(FALSE);
	UpdateData(TRUE);

	m_ctrlCalender.GetCurSel(select);
	CString strQuery;
	//strday.Format(_T("%d/%d%d"), select.GetMonth(), select.GetDay(), select.GetYear());
	strday.Format(_T("%d.%d.%d"), select.GetYear(), select.GetMonth(), select.GetDay());
	strQuery.Format(_T("SELECT * FROM dayimage"));
	m_command.Close();
	if (m_dbSet.Query(strQuery, &m_command))
	{
		m_nTotal = 0;
		while (m_command.MoveNext() == S_OK)
		{
			m_nTotal++;
		}
		m_nMoveCount = 1;

		GetDataFromDb(MOVE_NEXT_RECORD);
		m_bMoveRecord = true;
	}

	if (m_bSave) {
		m_WeatherState = m_command.GetString(6);
		m_strText = m_command.GetString(4);
		m_strDBID = m_command.GetString(1);
		m_strImgPath = m_command.GetString(2);
		if (m_strImgPath != "") {
			m_bmpBitmap.Destroy();
			m_bmpBitmap.Load(m_strImgPath);
			m_bSelectImg = true;
		}
		else {
			m_bmpBitmap.Destroy();
			m_bSelectImg = false;
		}
		if (m_WeatherState == "1") {
			pBt = (CButton*)GetDlgItem(IDC_RADIO_CLOUDY);
			pBt->SetCheck(TRUE);
		}
		else if (m_WeatherState == "2") {
			pBt = (CButton*)GetDlgItem(IDC_RADIO_LCLOUDY);
			pBt->SetCheck(TRUE);
		}
		else if (m_WeatherState == "3") {
			pBt = (CButton*)GetDlgItem(IDC_RADIO_RAIN);
			pBt->SetCheck(TRUE);
		}
		else if (m_WeatherState == "4") {
			pBt = (CButton*)GetDlgItem(IDC_RADIO_SNOW);
			pBt->SetCheck(TRUE);
		}
		else if (m_WeatherState == "5") {
			pBt = (CButton*)GetDlgItem(IDC_RADIO_SUNNY);
			pBt->SetCheck(TRUE);
		}
		else if (m_WeatherState == "6") {
			pBt = (CButton*)GetDlgItem(IDC_RADIO_WINDY);
			pBt->SetCheck(TRUE);
		}
	}
	else {
		m_strText = "";
		m_bmpBitmap.Destroy();
		m_bSelectImg = false;
	}

	UpdateData(FALSE);
	Invalidate();

}

void CDiaryView::OnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	refresh();
	*pResult = 0;
}


void CDiaryView::GetDataFromDb(int nMoveRecord)
{
	m_command.MoveFirst();
	m_command.MoveNext();
	switch (nMoveRecord)
	{
	case MOVE_FIRST_RECORD:
		m_command.MoveFirst();
		break;
	case MOVE_PREV_RECORD:
		m_command.MovePrev();
		break;
	case MOVE_NEXT_RECORD:
		for(int i = 0; i<m_nTotal-1; i++)
			if (m_command.GetString(3) != strday) {
					m_command.MoveNext();
					m_bSave = false;
			}
			else {
				m_bSave = true;
				break;
			}
			break;
	case MOVE_LAST_RECORD:
		m_command.MoveLast();
		break;
	}

	UpdateData(FALSE);

}




void CDiaryView::OnEnChangeEditText()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CFormView::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CDiaryView::OnClickedButtonSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString strQuery;
	if (m_bSave)
		strQuery.Format(_T("UPDATE dayimage SET imagepath = '%s', Contents = '%s' , weather = '%s' WHERE ID = %s"), m_strImgPath, m_strText, m_WeatherState, m_strDBID);
	else {
		strQuery.Format(_T("INSERT INTO dayimage(imagepath, test, Contents, weather) VALUES('%s','%s','%s','%s');"), m_strImgPath, strday, m_strText, m_WeatherState);
	}
	m_command.Close();
	if (m_dbSet.Query(strQuery, &m_command))
	{
		CString temp;
		temp.Format(_T("����Ǿ����ϴ�. -%s"),strday);
		AfxMessageBox(temp);
	}
}

// ������ �κ� ���̾�α׿� m_Text ���� �߰�
BOOL CDiaryView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->hwnd == m_Text)            // ����Ʈ �ڽ�
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			if ((::GetKeyState(VK_CONTROL) < 0 && pMsg->wParam == 86))    // Ctrl + V �� 
				pMsg->message = WM_PASTE;                                               // �޽����� �ش� �߻� �޽�����
																						// �־��ְ� ���۽�ŵ�ϴ�.

			else if (::GetKeyState(VK_CONTROL) < 0 && pMsg->wParam == 67)  // Ctrl + C
				pMsg->message = WM_COPY;
			
			else if (::GetKeyState(VK_CONTROL) < 0 && pMsg->wParam == 65) {
				m_Text.SetSel(0, -1);
			}
		}
	}
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CView::PreTranslateMessage(pMsg);
}

void CDiaryView::OnChangepassword()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (m_bViewChange == false)
	{
		m_dlgChange.Create(IDD_DIALOG1, this);
		CRect rectMain, rectHelp;
		GetWindowRect(&rectMain);

		m_dlgChange.GetWindowRect(&rectHelp);
		m_dlgChange.MoveWindow(rectMain.right, rectMain.top, rectHelp.Width(), rectHelp.Height());

		m_dlgChange.ShowWindow(SW_SHOW);
		m_bViewChange = true;
	}
	else{
		m_dlgChange.ShowWindow(SW_HIDE);

	m_dlgChange.DestroyWindow();
	m_bViewChange = false;
}
}


void CDiaryView::Change(CString strQuery)
{
	
	CString temp1, strQ;
	strQ = strQuery;

	m_command.Close();
	if (m_dbSet.Query(strQ, &m_command))
	{
		CString temp;
		temp.Format(_T("����Ǿ����ϴ�."), strQ);
		AfxMessageBox(temp);
	}
}


void CDiaryView::Check(CString m_strPassword)
{
	CString strQuery;

	CDiaryApp *pApp = (CDiaryApp*)AfxGetApp();

	
	strQuery.Format(_T("SELECT * FROM dayimage"));
	m_command.Close();
	if (m_dbSet.Query(strQuery, &m_command))
	{
		m_command.MoveFirst();
		if (m_command.GetString(5) != m_strPassword)
			AfxMessageBox(_T("��"));
		else {
			pApp->dlg.EndDialog(IDOK);
			refresh(); //ȭ�� ǥ��
		}

		m_bMoveRecord = true;
	}
}


void CDiaryView::OnClickedButtonInsert()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString szFilter = _T("All Files(*.*)|*.*|");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal())
	{
		m_strImgPath = dlg.GetPathName();
		m_bmpBitmap.Destroy();
		m_bmpBitmap.Load(m_strImgPath);
		m_bSelectImg = true;
	}
	Invalidate();
}


void CDiaryView::OnClickedButtonDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_bSelectImg = false;
	m_strImgPath = "";
	m_bmpBitmap.Destroy();
	Invalidate();
}


void CDiaryView::OnDraw(CDC* pDC)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CDC memdc;
	CStatic* size;
	CRect rect;
	int wid, hei;
	CImage WSun;
	CImage WSnow;
	CImage WCloud;
	CImage WLCloud;
	CImage WRain;
	CImage WWind;

	WSun.Destroy();
	WSnow.Destroy();
	WCloud.Destroy();
	WLCloud.Destroy();
	WRain.Destroy();
	WWind.Destroy();

	HRESULT hr = CoInitialize(NULL);

	// DB ���� ��θ� ���� exe���� ��ġ�� ã�� �ڵ�(DB�� exe������ ���� ���� �� ��)
	TCHAR programpath[_MAX_PATH];
	int index;
	CString strPath;
	GetModuleFileName(NULL, programpath, _MAX_PATH);
	strPath = programpath;
	index = strPath.ReverseFind('\\');
	strPath = strPath.Left(index + 1);
	CString strWSun, strWSnow, strWCloud, strWLCloud, strWRain, strWWind;
	strWSun.Format(_T("%ssun.png"), strPath);
	strWSnow.Format(_T("%ssnow.png"), strPath);
	strWCloud.Format(_T("%scloud.png"), strPath);
	strWLCloud.Format(_T("%slcloud.png"), strPath);
	strWRain.Format(_T("%srain.png"), strPath);
	strWWind.Format(_T("%sthunder.png"), strPath);
	WSun.Load(strWSun);
	WSnow.Load(strWSnow);
	WCloud.Load(strWCloud);
	WLCloud.Load(strWLCloud);
	WRain.Load(strWRain);
	WWind.Load(strWWind);
	pDC = m_WeatherSUNNY.GetWindowDC();
	wid = WSun.GetWidth();
	hei = WSun.GetHeight();
	WSun.Draw(pDC->m_hDC, 0, 0, wid, hei);

	pDC = m_WeatherS.GetWindowDC();
	wid = WSnow.GetWidth();
	hei = WSnow.GetHeight();
	WSnow.Draw(pDC->m_hDC, 0, 0, wid, hei);

	pDC = m_WeatherR.GetWindowDC();
	wid = WCloud.GetWidth();
	hei = WCloud.GetHeight();
	WCloud.Draw(pDC->m_hDC, 0, 0, wid, hei);

	pDC = m_WeatherC.GetWindowDC();
	wid = WLCloud.GetWidth();
	hei = WLCloud.GetHeight();
	WLCloud.Draw(pDC->m_hDC, 0, 0, wid, hei);

	pDC = m_WeatherLC.GetWindowDC();
	wid = WRain.GetWidth();
	hei = WRain.GetHeight();
	WRain.Draw(pDC->m_hDC, 0, 0, wid, hei);

	pDC = m_WeatherW.GetWindowDC();
	wid = WWind.GetWidth();
	hei = WWind.GetHeight();
	WWind.Draw(pDC->m_hDC, 0, 0, wid, hei);

	if (m_bSelectImg) {
		pDC = m_Img.GetWindowDC();
		size = (CStatic*)GetDlgItem(IDC_STATIC_IMAGE);
		size->GetClientRect(rect);
		memdc.CreateCompatibleDC(pDC);
		m_bmpBitmap.Draw(pDC->m_hDC, 0, 0, rect.Width(), rect.Height());
		pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
	}

}


BOOL CDiaryView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�
	int r=255, g=228, b=225;
	
	if (color == "0") {
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
}


HBRUSH CDiaryView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	int r = 255, g = 228, b = 225;

	if (color == "0") {
		r = 181;
		g = 215;
		b = 255;
	}
	CBrush* m_Brush;
	m_Brush = new CBrush(RGB(r, g, b));

	if (nCtlColor == CTLCOLOR_EDIT) {
		if (color == "1") {
			pDC->SetBkColor(RGB(255, 213, 210));
		}
		else if(color == "0"){
			pDC->SetBkColor(RGB(154, 218, 255));
		}
		return hbr = (HBRUSH)(m_Brush->GetSafeHandle());
	}
	/*if (nCtlColor == CTLCOLOR_BTN) {
		pDC->SetBkColor(RGB(255, 213, 210));
		pDC->SetTextColor(RGB(255, 255, 255));
		return hbr = (HBRUSH)(m_Brush->GetSafeHandle());
	}*/
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


//void CDiaryView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
//{
//	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
//	CFormView::OnDrawItem(nIDCtl, lpDrawItemStruct);
//}


void CDiaryView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CDC dc;
	RECT rect;

	int r = 255, g = 213, b = 210;

	if (color == "0") {
		r = 154;
		g = 218;
		b = 255;
	}

	dc.Attach(lpDrawItemStruct->hDC);   
	rect = lpDrawItemStruct->rcItem;    
	dc.Draw3dRect(&rect, RGB(255, 255, 255), RGB(0, 0, 0));
	dc.FillSolidRect(&rect, RGB(r, g, b));
	UINT state = lpDrawItemStruct->itemState; 
	if ((state & ODS_SELECTED))
		dc.DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);
	else
		dc.DrawEdge(&rect, EDGE_RAISED, BF_RECT);
		
	dc.SetBkColor(RGB(r, g, b));   
	dc.SetTextColor(RGB(0, 0, 0));    

	TCHAR buffer[MAX_PATH];           
	ZeroMemory(buffer, MAX_PATH);     
	::GetWindowText(lpDrawItemStruct->hwndItem, buffer, MAX_PATH);
		
	dc.DrawText(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc.Detach();  // Detach the Button DC
	CFormView::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CDiaryView::OnRadioCloudy()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_WeatherState.Format(_T("1"));
}


void CDiaryView::OnRadioLcloudy()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_WeatherState.Format(_T("2"));
}


void CDiaryView::OnRadioRain()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_WeatherState.Format(_T("3"));
}


void CDiaryView::OnRadioSnow()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_WeatherState.Format(_T("4"));
}


void CDiaryView::OnRadioSunny()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_WeatherState.Format(_T("5"));
}


void CDiaryView::OnRadioWindy()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_WeatherState.Format(_T("6"));
}


void CDiaryView::OnButtonPink()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	color = "1";
	CString strQuery;
	strQuery.Format(_T("UPDATE dayimage SET color = '%s' WHERE test = '9999.99.99'"), color);
	m_command.Close();
	if (m_dbSet.Query(strQuery, &m_command))
	{
		CString temp;
		temp.Format(_T("����Ǿ����ϴ�."), strQuery);
	}
	Invalidate();
}


void CDiaryView::OnButtonBlue()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	color = "0";
	CString strQuery;
	strQuery.Format(_T("UPDATE dayimage SET color = '%s' WHERE test = '9999.99.99'"), color);
	m_command.Close();
	if (m_dbSet.Query(strQuery, &m_command))
	{
		CString temp;
		temp.Format(_T("����Ǿ����ϴ�."), strQuery);
	}
	Invalidate();
}


void CDiaryView::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_command.Close();
	m_dbSet.~CDataSet();
	CFormView::OnClose();
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->OnClose();
	//exit(1);

}
