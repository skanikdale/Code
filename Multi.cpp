
// Multi.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Multi.h"
#include "MainFrm.h"

#include "MultiDoc.h"
#include "MultiView.h"
#include "Common.h"

#include "stdio.h"
#include "stdlib.h"

#include <iostream>

#include <process.h>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMultiApp

BEGIN_MESSAGE_MAP(CMultiApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMultiApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


void excel_column_converter(std::string& source);

#define MAX 10
int shared_value = 0;

CRITICAL_SECTION cs;

unsigned _stdcall even_thread_cs(void *p)
{

    for( int i = 0 ; i < MAX ; i++ )
    {
        EnterCriticalSection(&cs);

        if( shared_value % 2 == 0 )
        {
          printf("\n%d", i);

          wchar_t buffer[256];
          wsprintfW(buffer, L"%d", i);

          ::MessageBox(NULL, buffer , L"Even Dlg title", MB_OK);
        }
        
        LeaveCriticalSection(&cs);
    }
    return 0;
}

unsigned _stdcall odd_thread_cs(void *p)
{
    for( int i = 0 ; i < MAX ; i++ )
    {
        EnterCriticalSection(&cs);

        if( shared_value % 2 != 0 )
        {
            printf("\n%d", i);

            wchar_t buffer[256];
          wsprintfW(buffer, L"%d", i);

          ::MessageBox(NULL, buffer , L"ODD Dlg title", MB_OK);
        }

        LeaveCriticalSection(&cs);  

    }

    return 0;
}
// CMultiApp construction

CMultiApp::CMultiApp()
{
	m_bHiColorIcons = TRUE;

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Multi.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CMultiApp object
CMultiApp theApp;

class two;

class one {

public:
  one();
  ~one();

  int *nOne;

  friend two;
};

one::one()
{
  nOne = (int*)malloc(sizeof(int));

  this->~one();
}

one::~one()
{
  int* temp = nOne;
  printf("test");
}

class two {

  public:
   two() {}

   // virtual int absMethod() = 0;

public:
  void test();
  ~two();

  int nTwo;
};

class derived:public two
{
public:
  int test();
};

int derived::test()
{
  two* a = new two();
  nTwo = 220;

  return nTwo;
}

void two::test()
  {
    one* a = new one();
    a->nOne;
  }


two::~two()
{
  printf("test2");
}


BOOL CMultiApp::InitInstance()
{
  one a;
  //two b;
  //b.test();

  // testSmartPtrs();
	test_duplicate();
  /*testFunctors();
  test_decorator();*/
  /*testLambada();
  testTemplates();
  testGarbageCollector();
  test_tuple();*/

  //int tt = 7;
  //int* a = &tt;
  //int*b = &tt;

  
 //multiThreadTest();

  // stringTest();

 // stackTest();


 // testBFS();
 // testDFS();

 // binaryTreeTest();

 // subProcessTest();

 // multiThreadingTest();

 // oddEvenTest();

  producerConsumerTest();

  excel_column_converter(std::string("AA"));
  excel_column_converter(std::string("27"));


  // other method for odd even printing ... doesn't work... 
  // {
  //InitializeCriticalSection(&cs);

  //_beginthreadex(NULL, NULL, even_thread_cs, 0,0, 0);
  //_beginthreadex(NULL, NULL, odd_thread_cs, 0,0, 0);

  //getchar();
  //}

  return TRUE;

  

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMultiDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMultiView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

int CMultiApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMultiApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CMultiApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMultiApp customization load/save methods

void CMultiApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CMultiApp::LoadCustomState()
{
}

void CMultiApp::SaveCustomState()
{
}

// CMultiApp message handlers



