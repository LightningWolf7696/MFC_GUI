// RF_Test_Dialog.cpp : implementation file
//
#include "..\stdafx.h"
#include "..\IQfact_QCA99xx.h"
#include "RF_Test_Dialog.h"
#include "windows.h"

// RF_Test_Dialog dialog
IMPLEMENT_DYNAMIC(RF_Test_Dialog, CDialog)

RF_Test_Dialog::RF_Test_Dialog(CWnd* pParent /*=NULL*/)
	: CDialog(RF_Test_Dialog::IDD, pParent)
{
   m_DLL      = "";
   m_process  = "";
   m_ListData = "";
   m_INIPath  = "";
   rtnMsg     = "";
   memset(PN98, '\0', sizeof(PN98));
   m_ACTION_LIST = "";
   tetsList.clear();
   actionParameter.clear();
}

RF_Test_Dialog::~RF_Test_Dialog()
{
}

BOOL RF_Test_Dialog::SetToDutParameter(LPSTR ActionName, LPSTR ParameterName, LPSTR ParameterValue)
{
   string tmpActionName,tmpParameterName,tmpParameterValue;

   tmpActionName     = ActionName;
   tmpParameterName  = ParameterName;
   tmpParameterValue = ParameterValue;

   if(ParameterName == "ACTION_LIST")
      m_ACTION_LIST = ParameterValue;

   return TRUE;
}

void RF_Test_Dialog::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST1, m_CListCtrl);
   DDX_Control(pDX, IDC_BUTTON1, m_Start_Button);
   DDX_Control(pDX, IDC_DLL_EDIT1, m_DLL_CEdit);
   DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_File_BrowseCtrl);
   DDX_Control(pDX, IDC_RF_PARAMETER_EDIT1, m_PARAMETER_CEdit);
}

BEGIN_MESSAGE_MAP(RF_Test_Dialog, CDialog)
   ON_CBN_SELCHANGE(IDC_MFCFONTCOMBO20, &RF_Test_Dialog::OnCbnSelchangeMfcfontcombo20)
   ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &RF_Test_Dialog::OnLvnItemchangedList1)
   ON_NOTIFY(LVN_GETINFOTIP , IDC_LIST1, &RF_Test_Dialog::OnInfoTip)
   ON_BN_CLICKED(IDC_BUTTON1, &RF_Test_Dialog::OnBnClickedButton1)
   ON_EN_CHANGE(IDC_DLL_EDIT1, &RF_Test_Dialog::OnEnChangeDllEdit1)
   ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &RF_Test_Dialog::OnEnChangeMfceditbrowse1)
   ON_EN_CHANGE(IDC_RF_PARAMETER_EDIT1, &RF_Test_Dialog::OnEnChangeRfParameterEdit1)
END_MESSAGE_MAP()


/*
*  ACTION insert to GUI.  
*/
/* m_CListCtrl.InsertColumn( 
 0,              // Rank/order of item 
 "",       // Caption for this header 
 LVCFMT_LEFT,    // Relative position of items under header 
 -1,
 -1); 
 */
void RF_Test_Dialog::InsertItem(char *lpszFileName, string &lpszRunInfo)
{
   CFileFind finder; 
   char TestList_ReturnedString[1000000];
   char tmpACTION[1024]={'\0'};
   LVCOLUMN m_LVCOLUMN;
   DWORD    ItemData  = 0;

   CRect rect;
   m_CListCtrl.GetClientRect(&rect);
   m_CListCtrl.InsertColumn(0, _T("ACTION"), LVCFMT_LEFT, rect.Width());
   memset(TestList_ReturnedString, '\0',sizeof(TestList_ReturnedString));

   for(int i=0; i<tetsList.size(); i++)
   {
      int returnValue = ::GetPrivateProfileSection(tetsList.at(i).c_str(), TestList_ReturnedString, sizeof(TestList_ReturnedString), lpszFileName);
     
      for(int j=0,k=0; j<returnValue; j++)
      {
         int nPos = max(m_CListCtrl.GetItemCount(),0);
         if(TestList_ReturnedString[j] != 0)
            tmpACTION[k++] = TestList_ReturnedString[j];
         else
         {
           // string var = tmpACTION;
            nPos = m_CListCtrl.InsertItem(nPos, tmpACTION);
            m_CListCtrl.SetItemData(nPos, ItemData);
            k = 0;
            ItemData++;
            memset(tmpACTION, '\0',sizeof(tmpACTION));
         } 
      }
   }

   // Use macro to set check state
   //ListView_SetItemState(m_CListCtrl.m_hWnd, nPos, UINT((int(bState) + 1) << 12), LVIS_STATEIMAGEMASK);
   return ;  
}

/*
*  ini Value read.  
*/
/*
DWORD GetPrivateProfileString(
LPCTSTR lpAppName,
LPCTSTR lpKeyName,
LPCTSTR lpDefault,
LPTSTR  lpReturnedString,
DWORD   nSize,
LPCTSTR lpFileName
);
*/
BOOL RF_Test_Dialog::SectionKey_Read(char *lpszFileName, char *section, char *key, string &lpszRunInfo)
{
   CFileFind finder; 
   char ReturnedString[DLL_INFO_SIZE];

   memset(ReturnedString, '\0',sizeof(ReturnedString));
   BOOL ifFind = finder.FindFile(lpszFileName);
   if( ifFind )
   {
      int returnValue = ::GetPrivateProfileString(section, key, NULL, ReturnedString, sizeof(ReturnedString), lpszFileName);
     // if(returnValue != 0)
     //    m_DLL = ReturnedString;
      lpszRunInfo = ReturnedString;
      printf("1111");
   }
   return TRUE;
}
/*
*  ini Test section read.  
*/
BOOL RF_Test_Dialog::SectionList_Read(char *lpszFileName, char *section, string &lpszRunInfo)
{
   CFileFind finder; 
   char TestList_ReturnedString[DLL_INFO_SIZE];

   memset(TestList_ReturnedString, '\0',sizeof(TestList_ReturnedString));
   BOOL ifFind = finder.FindFile(lpszFileName);
   if( ifFind )
   {
     int returnValue = ::GetPrivateProfileSection(section, TestList_ReturnedString, sizeof(TestList_ReturnedString), lpszFileName);
     char tmpList[64]={'\0'};
     string var;
   
     for(int i=0,j=0; i<returnValue; i++)
     {
         if(TestList_ReturnedString[i] != 0)
            tmpList[j++] = TestList_ReturnedString[i];
         else
         {
            var = tmpList;
            tetsList.push_back(var);
            j = 0;
            memset(tmpList, '\0',sizeof(tmpList));
         } 
     }
   }
   else
   {
      lpszRunInfo = "FindFile Fail!!\n";
      return FALSE;
   }
   lpszRunInfo = "TestList_Read Pass!!\n";
   return TRUE;
}

BOOL RF_Test_Dialog::OnInitDialog()
{
   CDialog::OnInitDialog();
   string Dll_msg, ListMsg, msg;
   
   char Dir[DLL_INFO_SIZE];
   char InIFile[DLL_INFO_SIZE];
   char strMsg[DLL_INFO_SIZE];

   GetLocalDirectory(Dir, strMsg);
   m_INIPath.Format(_T("%sCustomer\\%s.ini"),Dir, PN98);
   strcpy_s(InIFile, sizeof(InIFile), m_INIPath);
   SectionKey_Read(InIFile, "PRODUCT_CONFIG", "DUT_DLL", Dll_msg);
   m_DLL.Format("%s",Dll_msg);
  //SectionList_Read(InIFile, "TEST_LIST",msg);
   ListView_SetExtendedListViewStyle(m_CListCtrl.m_hWnd, LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP);
   if(m_ACTION_LIST == "")
   {
      int index = 0, start = 0;
      SectionKey_Read(InIFile, "TEST_FUNCTION", "ACTION", ListMsg);
      if((index = ListMsg.find("ACTION_LIST=")) != string::npos)
      {
         start = index+12;
         if( ((index = ListMsg.find(",",start)) != string::npos) ||
             ((index = ListMsg.find(")",start)) != string::npos) )
            ListMsg = ListMsg.substr(start,index - start);
      }
      tetsList.push_back(ListMsg);
   } 
   else
      tetsList.push_back(m_ACTION_LIST);
   InsertItem(InIFile, msg);

   m_File_BrowseCtrl.SetWindowText(m_INIPath);
   m_DLL_CEdit.SetWindowText(m_DLL);
   
   return TRUE;  // return TRUE unless you set the focus to a control
}

// RF_Test_Dialog message handlers
void RF_Test_Dialog::OnCbnSelchangeMfcfontcombo20()
{
   // TODO: Add your control notification handler code here
}

void RF_Test_Dialog::RFTestInfo_Show()
{
   CString tmpMsg;
   string msg;
   int start=0,tail=0;

   m_PARAMETER_CEdit.SetWindowText(_T(""));
  
   for(int i=0; i < actionParameter.size(); i++)
   {
      start = actionParameter.at(i).Key.find_first_not_of(" ");
      tail =  actionParameter.at(i).Key.find_last_not_of(" ");
      actionParameter.at(i).Key = actionParameter.at(i).Key.substr(start, (tail+1) - start);

      start = actionParameter.at(i).value.find_first_not_of(" ");
      tail =  actionParameter.at(i).value.find_last_not_of(" ");
      actionParameter.at(i).value = actionParameter.at(i).value.substr(start, (tail+1) - start);
                  
      msg += actionParameter.at(i).Key + "=" + actionParameter.at(i).value + "\r\n";
     // printf("qqqq");
   }
      
   tmpMsg = _T(msg.c_str());
   m_PARAMETER_CEdit.SetWindowText(tmpMsg);
   m_PARAMETER_CEdit.UpdateWindow();   
 //  printf("111");
   return ;
}

void RF_Test_Dialog::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
   int m_iItem, m_iSubItem, m_ptAction;
   unsigned int m_uNewState, m_uOldState, m_uChanged; 
   POINT m_POINT;
   string tmpStr;
  // regex pattern("ACTION=.*\\(.*\\)");
  // regex Options_Pattern("\\.OPTIONS\\(.*\\)");
  // regex Parameter_Pattern("*=.*,");
  // regex Parameter2_Pattern("*=.*)");
   
   UpdateData();
   actionParameter.clear();

   LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
   // TODO: Add your control notification handler code here

   m_uNewState  = pNMLV->uNewState;

   if(m_uNewState != 0)
   {
       m_ListData =  m_CListCtrl.GetItemText(pNMLV->iItem,pNMLV->iSubItem);
       /* Action name parser.*/
       ListParameter tmp_Action;
       std::size_t index=0, start=0;
       string substring;
       tmpStr = m_ListData;

       /*.OPTIONS parameter filter.*/
       int OPTIONS_Start = 0, OPTIONS_Stop=0, OPTIONS_Index=0;
       while((OPTIONS_Index = tmpStr.find(".OPTIONS(", OPTIONS_Start)) != string::npos)
       {
          OPTIONS_Start = OPTIONS_Index;
          if((OPTIONS_Index = tmpStr.find(")", OPTIONS_Start)) != string::npos)
             OPTIONS_Stop = OPTIONS_Index;
          tmpStr.erase(OPTIONS_Start, (OPTIONS_Stop - OPTIONS_Start)+1);
       }

       do
       {
          if((index = tmpStr.find("=")) != string::npos)
          {
             ListParameter tmp_Action_Para;
             substring = tmpStr.substr(0,index);
             tmpStr.erase(0, (substring.length()+1));
             tmp_Action_Para.Key = substring;

             if((index = tmpStr.find("(")) != string::npos ||
                (index = tmpStr.find(",")) != string::npos ||
                (index = tmpStr.find(")")) != string::npos)
             {
                substring = tmpStr.substr(0,index);
                tmpStr.erase(0, (substring.length()+1));
                tmp_Action_Para.value = substring;
                actionParameter.push_back(tmp_Action_Para);
             }
          }         
       }while((index != string::npos));
       //printf("1111");
       /* Action name parser.*/
       /*index        = tmpStr.find("=", start);
       substring    = tmpStr.substr(start,index-start);
       if ((index != string::npos) && (substring == "ACTION"))
       {
          tmp_Action.Key = substring;
          tmpStr.erase(OPTIONS_Start, (OPTIONS_Stop - OPTIONS_Start)+1);
          start = index;
          

          if((index = tmpStr.find("(",start)) != string::npos)
          {
             substring = tmpStr.substr(start+1,index-start-1);
             tmp_Action.value = substring;
             start = index;
             actionParameter.push_back(tmp_Action);
          }
          else
          {
             tmp_Action.Key   = "List";
             tmp_Action.value = "Error";
             actionParameter.push_back(tmp_Action);
             if(m_uNewState != 0)
                RFTestInfo_Show();
             rtnMsg = "Parser ( Fail.";
             *pResult = 0;
             return ; 
          }
       }
       else
       {  
          tmp_Action.Key   = "Action";
          tmp_Action.value = "Error";
          actionParameter.push_back(tmp_Action);
          if(m_uNewState != 0)
             RFTestInfo_Show();
          *pResult = 0;
          return ; 
       } */

       /* Action parameter parser.*/
       //int tail = tmpStr.length()-1;
       //if(tmpStr[tail] == ')')
       //{

   }   
   printf("111");
   if(m_uNewState != 0)
      RFTestInfo_Show();
   *pResult = 0;
}

/*
* Action list Info tip display. 
*/
void RF_Test_Dialog::OnInfoTip( NMHDR * pNMHDR, LRESULT * pResult )
{
   NMLVGETINFOTIP* pInfoTip = reinterpret_cast<NMLVGETINFOTIP*>(pNMHDR);
   LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

   ASSERT(pInfoTip);

   // Get the item data for this unit
   DWORD dwData = m_CListCtrl.GetItemData(pInfoTip->iItem);
   CString strText;
   strText = m_CListCtrl.GetItemText(pNMLV->iItem,pNMLV->iSubItem);  
   _tcscpy(pInfoTip->pszText, (LPCTSTR)strText);
   return ;
}

static DWORD ThreadProcess(LPVOID lpParam)
{
   typedef struct _LpThreadParam 
   {
      LPVOID lpParam;
      char* m_DLL;
      char* m_process;
      char* m_ActionData;
      char* m_INIPath;
      BOOL (CALLBACK *funcSetAction)(LPSTR dll, LPSTR process, LPSTR data, LPSTR lpszRunInfo);
   }LpThreadParam;
   char strMsg[DLL_INFO_SIZE];
   LpThreadParam *m_ThreadParam = (LpThreadParam *)lpParam;

   int rtn = m_ThreadParam->funcSetAction(m_ThreadParam->m_DLL, m_ThreadParam->m_process, m_ThreadParam->m_ActionData, strMsg);
   if(!rtn)
      funcGetMessage(strMsg); 
   return 1;
}
//BOOL (CALLBACK *m_funcSetAction)(LPSTR dll, LPSTR process, LPSTR data, LPSTR lpszRunInfo);
void RF_Test_Dialog::OnBnClickedButton1()
{
   // TODO: Add your control notification handler code here
   char strMsg[DLL_INFO_SIZE];
   char tmpData[DLL_INFO_SIZE];
   CString EditData;
   CArray<CString> actionDataArray;
   CString actionData;
   BOOL rtn;
   int start = 0, index = 0;
   DWORD dwWaitResult;
   DWORD dwThreadID;
   HANDLE ghThreads;
   ThreadParam tmpThreadPara;

   m_process = "ALL";
   m_PARAMETER_CEdit.GetWindowText(EditData);

   while( ( index = EditData.Find("\r\n",start )) != -1 )
   {
      CString tmp = EditData.Mid(start, index - start);
      actionDataArray.Add(tmp);
      start = index + 2;
   }

   for(int i=0; i< actionDataArray.GetSize(); i++)
   {
      if((actionDataArray.GetAt(i).Find("ACTION=")) != -1)
      {
         CString tmp = actionDataArray.GetAt(i);
         actionData += tmp + "(";
         actionDataArray.RemoveAt(i);
      }
   }

   for(int i=0; i< actionDataArray.GetSize(); i++)
   {
      CString tmp = actionDataArray.GetAt(i);

      if(i == (actionDataArray.GetSize() - 1))
         actionData += tmp + ")";
      else
         actionData += tmp + ",";
   }

   // rtn = m_funcSetAction((char*)m_DLL.GetBuffer(0), (char*)m_process.GetBuffer(0), (char*)actionData.GetBuffer(0), strMsg);
   // if(!rtn)
   //    funcGetMessage(strMsg);
   tmpThreadPara.funcSetAction = m_funcSetAction;
   tmpThreadPara.m_DLL         = (char*)m_DLL.GetBuffer(0);
   tmpThreadPara.m_process     = (char*)m_process.GetBuffer(0);
   tmpThreadPara.m_ActionData  = (char*)actionData.GetBuffer(0);

   ghThreads= CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcess, (void *)&tmpThreadPara, 0, &dwThreadID);
   if ( ghThreads ) {
      DWORD dwRet = 0;
      MSG msg;
      HWND hwnd;
      hwnd = ::FindWindow(NULL,"RF Test");
      if(hwnd)
      {
         /*LONG SetWindowLongA(HWND hWnd, int  nIndex, LONG dwNewLong); */
         /*BOOL SetLayeredWindowAttributes(HWND hwnd,COLORREF crKey,BYTE bAlpha,DWORD dwFlags); */
         //::ShowWindow(hwnd, SW_SHOWNA);
         ::SetWindowLong (hwnd, GWL_EXSTYLE , GetWindowLong (hwnd , GWL_EXSTYLE ) | WS_EX_LAYERED) ;
         ::SetLayeredWindowAttributes(hwnd,0,(255*60)/100 , LWA_ALPHA ) ; 
      }
      //CloseHandle(ghThreads);
      while (TRUE)
      {
         //wait for ghThreads to be over¡Aand wait for
         //QS_ALLINPUT¡]Any message is in the queue¡^
         dwRet = MsgWaitForMultipleObjects (1, &ghThreads,   FALSE, INFINITE, QS_ALLINPUT);
         switch(dwRet)
         {
         case WAIT_OBJECT_0: 
            break; //break the loop
         case WAIT_OBJECT_0 + 1:
            //get the message from Queue
            //and dispatch it to specific window
            PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
            DispatchMessage(&msg); 
            continue;
         default:
            break; // unexpected failure
         }
         break;
      }
      CloseHandle(ghThreads);
      ::SetLayeredWindowAttributes(hwnd,0,(255*100)/100 , LWA_ALPHA) ;
   }
   //DWORD dwRet;
}

void RF_Test_Dialog::OnEnChangeDllEdit1()
{
   // TODO:  If this is a RICHEDIT control, the control will not
   // send this notification unless you override the CDialog::OnInitDialog()
   // function and call CRichEditCtrl().SetEventMask()
   // with the ENM_CHANGE flag ORed into the mask.

   // TODO:  Add your control notification handler code here
   m_DLL_CEdit.GetWindowText(m_DLL);   
//   printf("1111");
}

void RF_Test_Dialog::OnEnChangeMfceditbrowse1()
{
   // TODO:  If this is a RICHEDIT control, the control will not
   // send this notification unless you override the CDialog::OnInitDialog()
   // function and call CRichEditCtrl().SetEventMask()
   // with the ENM_CHANGE flag ORed into the mask.

   // TODO:  Add your control notification handler code here
   char InIFile[DLL_INFO_SIZE];
   string strMsg;

   m_CListCtrl.DeleteAllItems();
   m_CListCtrl.DeleteColumn(0);
   m_File_BrowseCtrl.GetWindowText(m_INIPath);
   strcpy(InIFile, m_INIPath);
   InsertItem(InIFile, strMsg);
   printf("1111");
}

void RF_Test_Dialog::OnCbnSelchangeActionCombobox()
{
   // TODO: Add your control notification handler code here
}


void RF_Test_Dialog::OnCbnSelchangeTxChainCombobox()
{
   // TODO: Add your control notification handler code here
}


void RF_Test_Dialog::OnEnChangeRfParameterEdit1()
{
   // TODO:  If this is a RICHEDIT control, the control will not
   // send this notification unless you override the CDialog::OnInitDialog()
   // function and call CRichEditCtrl().SetEventMask()
   // with the ENM_CHANGE flag ORed into the mask.

   // TODO:  Add your control notification handler code here
}