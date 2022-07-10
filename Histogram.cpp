
#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Histogram.h"
#include "MainFrm.h"
#include "iostream"

#include "HistogramDoc.h"
#include "HistogramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CHistogramApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CHistogramApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


CHistogramApp::CHistogramApp() noexcept
{
	m_bHiColorIcons = TRUE;


	m_nAppLook = 0;
	SetAppID(_T("Histogram.AppID.NoVersion"));

}


CHistogramApp theApp;

BOOL CHistogramApp::InitInstance()
{
	CWinAppEx::InitInstance();


	EnableTaskbarInteraction(FALSE);

	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));
	LoadStdProfileSettings(4);


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHistogramDoc),
		RUNTIME_CLASS(CMainFrame), 
		RUNTIME_CLASS(CHistogramView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	CMFCToolBar::m_bExtCharTranslation = TRUE;

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void CHistogramApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CHistogramApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CHistogramApp::LoadCustomState()
{
}

void CHistogramApp::SaveCustomState()
{
}

