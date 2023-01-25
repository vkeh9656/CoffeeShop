
// CoffeeShopDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CoffeeShop.h"
#include "CoffeeShopDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoffeeShopDlg 대화 상자



CCoffeeShopDlg::CCoffeeShopDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COFFEESHOP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCoffeeShopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COUNT_SPIN, m_count_spin);
}

BEGIN_MESSAGE_MAP(CCoffeeShopDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_ITEM_LIST, &CCoffeeShopDlg::OnLbnSelchangeItemList)
	ON_NOTIFY(UDN_DELTAPOS, IDC_COUNT_SPIN, &CCoffeeShopDlg::OnDeltaposCountSpin)
//	ON_WM_DESTROY()
ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCoffeeShopDlg 메시지 처리기

BOOL CCoffeeShopDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	wchar_t* p_item_name[MAX_ITEM_COUNT] =
	{
		L"아메리카노         1900원", L"카페라떼           2500원",
		L"카페모카           2800원", L"카라멜마끼아또     3200원",
		L"에스프레소         1800원", L"바닐라라떼         3500원",
		L"카푸치노           3300원", L"비엔나             3500원",
	};

	int price[MAX_ITEM_COUNT] = { 1900,2500,2800,3200,1800,3500,3300,3500 };

	

	m_item_list.SubclassDlgItem(IDC_ITEM_LIST, this);

	m_my_font.CreatePointFont(96, L"굴림체");
	m_item_list.SetFont(&m_my_font);

	m_item_list.SetItemHeight(0, 24);

	ItemInfo* p;
	for (int i = 0; i < MAX_ITEM_COUNT; i++)
	{
		m_item_list.InsertString(i, p_item_name[i]);
		p = new ItemInfo;
		p->price = price[i];
		p->count = 0;

		m_item_list.SetItemDataPtr(i, p);
	}

	m_count_spin.GetWindowRect(&m_spin_rect);
	ScreenToClient(&m_spin_rect);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCoffeeShopDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCoffeeShopDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCoffeeShopDlg::CalcTotalPrice()
{
	int count = m_item_list.GetCount();
	int total_price = 0;
	ItemInfo* p;

	for (int i = 0; i < count; i++)
	{
		if (m_item_list.GetCheck(i))
		{
			p = (ItemInfo*)m_item_list.GetItemDataPtr(i);

			total_price += p->price * p->count;
		}
	}

	SetDlgItemInt(IDC_TOTAL_PRICE_EDIT, total_price);
}


void CCoffeeShopDlg::OnLbnSelchangeItemList()
{
	int index = m_item_list.GetCurSel();
	ItemInfo* p = (ItemInfo*)m_item_list.GetItemDataPtr(index);

	if (m_item_list.GetCheck(index)) {
		if (p->count == 0) p->count = 1;
	} 
	else {
		if (p->count != 0) p->count = 0;
	}
	m_item_list.SetCurSel(index);
	m_count_spin.SetWindowPos(NULL, m_spin_rect.left, m_spin_rect.top + index * 24, 0, 0, SWP_NOSIZE);

	CalcTotalPrice();
}


void CCoffeeShopDlg::OnDeltaposCountSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	*pResult = 0;

	int index = m_item_list.GetCurSel();
	if (LB_ERR != index && m_item_list.GetCheck(index))
	{
		ItemInfo* p = (ItemInfo*)m_item_list.GetItemDataPtr(index);
		
		if (pNMUpDown->iDelta > 0) {
			if (p->count > 1)p->count--;
		}
		else {
			if (p->count < 100)p->count++;
		}
		m_item_list.SetCurSel(index);
		CalcTotalPrice();
	}
}

void CCoffeeShopDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	int count = m_item_list.GetCount();
	ItemInfo* p;
	for (int i = 0; i < count; i++)
	{
		p = (ItemInfo*)m_item_list.GetItemDataPtr(i);
		delete p;
	}
	m_item_list.ResetContent();
}
