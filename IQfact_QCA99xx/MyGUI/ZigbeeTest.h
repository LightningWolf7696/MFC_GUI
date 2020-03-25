#pragma once


// CZigbeeTest dialog

class CZigbeeTest : public CPropertyPage
{
	DECLARE_DYNAMIC(CZigbeeTest)

public:
	CZigbeeTest();
	virtual ~CZigbeeTest();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_ZIGBEE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
