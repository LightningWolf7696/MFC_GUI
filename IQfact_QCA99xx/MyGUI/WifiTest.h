#pragma once


// CWifiTest dialog

class CWifiTest : public CPropertyPage
{
	DECLARE_DYNAMIC(CWifiTest)

public:
	CWifiTest();
	virtual ~CWifiTest();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_WIFI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

//protected:
 //  virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
