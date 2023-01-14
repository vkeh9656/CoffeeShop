
// CoffeeShop.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "CoffeeShop.h"
#include "CoffeeShopDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoffeeShopApp

BEGIN_MESSAGE_MAP(CCoffeeShopApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCoffeeShopApp 생성

CCoffeeShopApp::CCoffeeShopApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CCoffeeShopApp 개체입니다.

CCoffeeShopApp theApp;


// CCoffeeShopApp 초기화

BOOL CCoffeeShopApp::InitInstance()
{
	CWinApp::InitInstance();

	CCoffeeShopDlg dlg;
	dlg.DoModal();
	return FALSE;
}

