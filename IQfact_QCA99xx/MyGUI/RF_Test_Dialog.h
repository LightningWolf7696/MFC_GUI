#pragma once

#include "afxcmn.h"
#include "afxwin.h"
#include "afxeditbrowsectrl.h"
#include "afxvslistbox.h"
#include "afxdialogex.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;
// RF_Test_Dialog dialog

class RF_Test_Dialog : public CDialog
{
   typedef struct _ThreadParam 
   {
      LPVOID lpParam;
      char* m_DLL;
      char* m_process;
      char* m_ActionData;
      char* m_INIPath;
      BOOL (CALLBACK *funcSetAction)(LPSTR dll, LPSTR process, LPSTR data, LPSTR lpszRunInfo);
   }ThreadParam;

	DECLARE_DYNAMIC(RF_Test_Dialog)
   typedef struct _ListParameter
   {
      string Key;
      string value;
   }ListParameter;

public:
	RF_Test_Dialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~RF_Test_Dialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
   virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
   funcGetMessage m_cbXmlMessage;
   funcGetMessage m_cbListMessage;
   BOOL (CALLBACK *m_funcSetAction)(LPSTR dll, LPSTR process, LPSTR data, LPSTR lpszRunInfo);
   HWND m_HParentWnd;

   CString m_DLL;
   CString m_process;
   CString m_ListData;
   CString m_INIPath;
   char PN98[32];
   
   CEdit m_DLL_CEdit;
   CListCtrl m_CListCtrl;
   CButton m_Start_Button;
   CMFCEditBrowseCtrl m_File_BrowseCtrl;
   CListCtrl m_RF_Para_CListCtrl;
   CEdit m_PARAMETER_CEdit; 

   string rtnMsg;
   string m_ACTION_LIST;
   vector<string> tetsList;
   vector<ListParameter> actionParameter;
 //  vector<vector<action>> action_List;

   afx_msg void OnCbnSelchangeMfcfontcombo20();
   afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg void OnInfoTip( NMHDR * pNMHDR, LRESULT * pResult );
   afx_msg void OnBnClickedButton1();
   afx_msg void OnEnChangeDllEdit1();
   afx_msg void OnEnChangeMfceditbrowse1();
   afx_msg void OnCbnSelchangeActionCombobox();
   afx_msg void OnCbnSelchangeTxChainCombobox();
   afx_msg void OnEnChangeRfParameterEdit1();

   BOOL SectionKey_Read(char *lpszFileName, char *section, char *key, string &lpszRunInfo);
   BOOL SectionList_Read(char *lpszFileName, char *section, string &lpszRunInfo);
   void InsertItem(char *lpszFileName, string &lpszRunInfo);
   void RFTestInfo_Show();
   BOOL SetToDutParameter(LPSTR ActionName, LPSTR ParameterName,LPSTR ParameterValue);
};
