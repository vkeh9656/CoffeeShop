// MyListBox.cpp: 구현 파일
//

#include "pch.h"
#include "CoffeeShop.h"
#include "MyListBox.h"


// MyListBox

IMPLEMENT_DYNAMIC(MyListBox, CCheckListBox)

MyListBox::MyListBox()
{

}

MyListBox::~MyListBox()
{
}


BEGIN_MESSAGE_MAP(MyListBox, CCheckListBox)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// MyListBox 메시지 처리기

void MyListBox::DrawItem(LPDRAWITEMSTRUCT lpds)
{
	CCheckListBox::DrawItem(lpds);
	
	CDC* p_dc = CDC::FromHandle(lpds->hDC); // 나는 간편하게 mfc 쓰고 싶을때 ownerDraw의 
	CString str;
	
	/*ItemInfo* p = (ItemInfo*)GetItemDataPtr(lpds->itemID);*/
	ItemInfo* p = (ItemInfo*)lpds->itemData;
	if (p->count > 1)
	{
		str.Format(L"(%d원)%d개", p->price*p->count, p->count);
	}
	else
	{
		str.Format(L"%d개", p->count);
	}
	
	p_dc->SetBkMode(TRANSPARENT);
	if(lpds->itemState & ODS_SELECTED) p_dc->SetTextColor(RGB(255, 255, 0));
	else p_dc->SetTextColor(RGB(0, 180, 0));
	p_dc->DrawText(str, &lpds->rcItem, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

}


void MyListBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CCheckListBox::OnKeyDown(nChar, nRepCnt, nFlags);

	GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), LBN_SELCHANGE), (LPARAM)m_hWnd);
}
