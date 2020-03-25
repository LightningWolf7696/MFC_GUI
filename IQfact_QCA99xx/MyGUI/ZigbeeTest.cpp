// ZigbeeTest.cpp : implementation file
//

#include "../stdafx.h"
#include "../IQfact_QCA99xx.h"
#include "ZigbeeTest.h"
#include "afxdialogex.h"


// CZigbeeTest dialog

IMPLEMENT_DYNAMIC(CZigbeeTest, CPropertyPage)

CZigbeeTest::CZigbeeTest()
	: CPropertyPage(CZigbeeTest::IDD)
{

}

CZigbeeTest::~CZigbeeTest()
{
}

void CZigbeeTest::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZigbeeTest, CPropertyPage)
END_MESSAGE_MAP()


// CZigbeeTest message handlers
