// MySheet.cpp : implementation file
//

#include "../stdafx.h"
#include "../IQfact_QCA99xx.h"
#include "MySheet.h"


// CMySheet

IMPLEMENT_DYNAMIC(CMySheet, CPropertySheet)

CMySheet::CMySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
  
}

CMySheet::CMySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CMySheet::~CMySheet()
{
}

//BOOL CMySheet::InitInstance()
//{
//   AddPage(&m_CZigbeeTest);
//   AddPage(&m_CWifiTest);
//
//   return TRUE;
//}

BOOL CMySheet::OnInitDialog()
{
   BOOL bResult = CPropertySheet::OnInitDialog();
   return bResult;
}

BEGIN_MESSAGE_MAP(CMySheet, CPropertySheet)
END_MESSAGE_MAP()


// CMySheet message handlers
