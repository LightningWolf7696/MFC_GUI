#pragma once

#include "WifiTest.h"
#include "ZigbeeTest.h"
// CMySheet

class CMySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMySheet)

public:
	CMySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CMySheet();

   CZigbeeTest m_CZigbeeTest;
   CWifiTest   m_CWifiTest;
   // Overrides

public:
   virtual BOOL OnInitDialog();

//public:
//   virtual BOOL InitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


