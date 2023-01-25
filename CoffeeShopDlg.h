
// CoffeeShopDlg.h: 헤더 파일
//

#pragma once
#include "MyListBox.h"
#define MAX_ITEM_COUNT		8

// CCoffeeShopDlg 대화 상자
class CCoffeeShopDlg : public CDialogEx
{
private:
	MyListBox m_item_list;
	CRect m_spin_rect;
	CFont m_my_font;

// 생성입니다.
public:
	CCoffeeShopDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	
	void CalcTotalPrice();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COFFEESHOP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeItemList();
	CSpinButtonCtrl m_count_spin;
	afx_msg void OnDeltaposCountSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
};
