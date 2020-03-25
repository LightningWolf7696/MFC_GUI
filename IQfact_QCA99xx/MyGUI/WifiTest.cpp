// WifiTest.cpp : implementation file
//

#include "../stdafx.h"
#include "../IQfact_QCA99xx.h"
#include "WifiTest.h"
#include "afxdialogex.h"


// CWifiTest dialog

IMPLEMENT_DYNAMIC(CWifiTest, CPropertyPage)

CWifiTest::CWifiTest()
	: CPropertyPage(CWifiTest::IDD)
{

}

CWifiTest::~CWifiTest()
{
}

void CWifiTest::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}

//BOOL CWifiTest::OnInitDialog()
//{
//   CPropertyPage::OnInitDialog();
//   return TRUE;  // return TRUE unless you set the focus to a control
//}


BEGIN_MESSAGE_MAP(CWifiTest, CPropertyPage)
END_MESSAGE_MAP()


// CWifiTest message handlers
