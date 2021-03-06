// OrPSFDlg.cpp : implementation file
//

#include "stdafx.h"
#include "windows.h"
#include "OrPSF.h"
#include "OrPSFDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COrPSFDlg dialog




COrPSFDlg::COrPSFDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COrPSFDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COrPSFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_EDIT2, edit2);
	DDX_Control(pDX, IDC_EDIT3, edit3);
	DDX_Control(pDX, IDC_EDIT4, edit4);
	DDX_Control(pDX, IDC_EDIT5, edit5);
	DDX_Control(pDX, IDC_EDIT6, edit6);
	DDX_Control(pDX, IDC_EDIT7, edit7);
}

BEGIN_MESSAGE_MAP(COrPSFDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON5, &COrPSFDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &COrPSFDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &COrPSFDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &COrPSFDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &COrPSFDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// COrPSFDlg message handlers

BOOL COrPSFDlg::OnInitDialog()
{
	BOOL ret;

	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_IsLogin = false;

	m_SecAttIn.nLength = sizeof(SECURITY_ATTRIBUTES);
	m_SecAttIn.bInheritHandle = TRUE;
	m_SecAttIn.lpSecurityDescriptor = NULL;

	memset( &m_si, 0, sizeof(STARTUPINFO) );
	memset( &m_pi, 0, sizeof(PROCESS_INFORMATION) );

	m_SecAttOut.nLength = sizeof(SECURITY_ATTRIBUTES);
	m_SecAttOut.bInheritHandle = TRUE;
	m_SecAttOut.lpSecurityDescriptor = NULL;
	m_hPsftpStdInR = NULL;
	m_hPsftpStdInW = NULL;
	m_hPsftpStdOutR = NULL;
	m_hPsftpStdOutR = NULL;

	// pipe create
	ret = CreatePipe( &m_hPsftpStdInR, &m_hPsftpStdInW, &m_SecAttIn, 0 );
	if( ret != 0 )
	{
		ret = CreatePipe( &m_hPsftpStdOutR, &m_hPsftpStdOutW, &m_SecAttOut, 0 );
	}

	if( ret != 0 )
	{
		edit1.SetWindowTextW(L"输入远程服务器地址、用户名、及密码后，点击 Login 登录。");

		m_si.cb = sizeof(m_si);
		m_si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
		m_si.wShowWindow = FALSE;
		m_si.hStdInput = m_hPsftpStdInR;
		m_si.hStdError = m_hPsftpStdOutW;
		m_si.hStdOutput = m_hPsftpStdOutW;
	}
	else {
		edit1.SetWindowTextW(L"启动失败！！！");
		if( m_hPsftpStdInR != NULL )
		{
			CloseHandle(m_hPsftpStdInR);
			m_hPsftpStdInR = NULL;
		}
		if( m_hPsftpStdInW != NULL )
		{
			CloseHandle(m_hPsftpStdInW);
			m_hPsftpStdInW = NULL;
		}
		if( m_hPsftpStdOutR != NULL )
		{
			CloseHandle(m_hPsftpStdOutR);
			m_hPsftpStdOutR = NULL;
		}
		if( m_hPsftpStdOutW != NULL )
		{
			CloseHandle(m_hPsftpStdOutW);
			m_hPsftpStdOutW = NULL;
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COrPSFDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COrPSFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COrPSFDlg::OnBnClickedButton5()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	if( m_IsLogin == false )
	{
		return;
	}

	CString path;

    path = BootOpenDialog();
	edit5.SetWindowTextW(path);
}

CString COrPSFDlg::BootOpenDialog()
{
    CString strFile = _T("");

    CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("All Files (*.*)||"), NULL);

    if (dlgFile.DoModal())
    {
        strFile = dlgFile.GetPathName();
    }

    return strFile;
}

/*
 * wchar -> char 変換
 * 
 */
int COrPSFDlg::WcharToChar( wchar_t* swchar, char* dchar, int dlen )
{
	int			nbytes;
	int			ret;

	// wchar_t -> char
	nbytes = WideCharToMultiByte( 0, 0, swchar, -1, NULL, 0,NULL, NULL );
	if( nbytes <= dlen )
	{
		ret = WideCharToMultiByte( 0, 0, swchar, -1, dchar, nbytes, NULL, NULL );
	}
	else
	{
		ret = WideCharToMultiByte( 0, 0, swchar, -1, dchar, dlen, NULL, NULL );
	}

	if( ret == 0 )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 * char -> wchar 変換
 * 
 */
int COrPSFDlg::CharToWchar( char* schar, wchar_t* dwchar, int dlen )
{
	int			nbytes;
	int			ret;

	// char -> wchar_t
	nbytes = MultiByteToWideChar( 0, 0, schar, -1, NULL, 0);
	if( nbytes <= dlen )
	{
		ret = MultiByteToWideChar( 0, 0, schar, -1, dwchar, nbytes);
	}
	else
	{
		ret = MultiByteToWideChar( 0, 0, schar, -1, dwchar, nbytes);
	}

	if( ret == 0 )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void COrPSFDlg::OnBnClickedButton2()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	wchar_t		tmp[256];
	char		command[256];
	bool		ret;

	// host
	edit2.GetWindowTextW( tmp, sizeof(tmp) );
	WcharToChar( tmp, m_host, sizeof(m_host) );
	// user
	edit3.GetWindowTextW( tmp, sizeof(tmp) );
	WcharToChar( tmp, m_user, sizeof(m_host) );
	// pw
	edit4.GetWindowTextW( tmp, sizeof(tmp) );
	WcharToChar( tmp, m_pw, sizeof(m_host) );

	sprintf( command, "psftp -pw %s %s@%s", m_pw, m_user, m_host );

	ret = Login( command );
	if( ret == false )
	{
		edit1.SetWindowTextW(L"登录失败！\n 请确地址、用户名、密码。");
		m_IsLogin = false;
		return;
	}

	m_IsLogin = true;
	edit1.SetWindowTextW(L"登录成功！\n 可以获取或上传文件。");
}

bool COrPSFDlg::Login(char* command)
{
	BOOL bRet;
	char buf[1024];
	wchar_t comd[256];
	DWORD readsize;

	CharToWchar( command, comd, sizeof(comd) );

	// psftp thread start
	bRet = CreateProcessW(
		L"psftp.dat",
		comd,
		NULL,   
        NULL,   
        TRUE,   
        CREATE_NEW_CONSOLE,   // CREATE_NO_WINDOW,CREATE_NEW_CONSOLE
        NULL,   
        NULL,   
        &m_si,   
        &m_pi
		);

	if( bRet == 0 ){
		DWORD err = ::GetLastError();
		return ( false );
	}

	bRet = ReadFile( m_hPsftpStdOutR, buf, sizeof(buf), &readsize, NULL );
	// ReadFile error
	if( bRet == 0 ){
		return ( false );
	}
	// login error
	if( strstr( buf, "Remote working directory is" ) == NULL ){
		return ( false );
	}

	return ( true );
}

void COrPSFDlg::OnBnClickedButton4()
{
	BOOL bRet;
	char buf[1024];
	DWORD readsize;
	DWORD writesize;
	wchar_t tmp[512];
	char tmpfile[512];
	char command[1024];

	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	if( m_IsLogin == false )
	{
		return;
	}

	edit6.GetWindowTextW( tmp, sizeof(tmp) );
	if( tmp[0] == L'\0' )
	{
		return;
	}
	WcharToChar( tmp, tmpfile, sizeof(tmpfile) );
	sprintf( command, "mget %s\r\n", tmpfile );

	// command write
	bRet = WriteFile( m_hPsftpStdInW, command, strlen(command), &writesize, NULL );
	// WriteFile error
	if( bRet == 0 ){
		edit1.SetWindowTextW(L"获取文件失败！");
		return;
	}

	bRet = ReadFile( m_hPsftpStdOutR, buf, sizeof(buf), &readsize, NULL );
	// ReadFile error
	if( bRet == 0 ){
		edit1.SetWindowTextW(L"获取文件失败！");
		return;
	}
	// command succeed
	if( strstr( buf, "local:" ) != NULL ){
		edit1.SetWindowTextW(L"获取文件成功！\r\n请到根目录下查看。");
		return;
	}

	// if( strstr( buf, "nothing matched" ) != NULL ){
	// 	edit1.SetWindowTextW(L"获取文件失败！");
	//	return;
	// }
	
	edit1.SetWindowTextW(L"获取文件失败！");
}

void COrPSFDlg::OnBnClickedButton3()
{
	BOOL bRet;
	DWORD readsize;
	DWORD writesize;
	wchar_t tmp[512];
	char buf[1024];
	char localfile[512];
	char remotefile[512];
	char command[1024];

	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	if( m_IsLogin == false )
	{
		return;
	}

	tmp[0] = L'\0';
	edit5.GetWindowTextW( tmp, sizeof(tmp) );
	if( tmp[0] == L'\0' )
	{
		return;
	}
	WcharToChar( tmp, localfile, sizeof(localfile) );
	tmp[0] = L'\0';
	edit7.GetWindowTextW( tmp, sizeof(tmp) );
	if( tmp[0] == L'\0' )
	{
		return;
	}
	WcharToChar( tmp, remotefile, sizeof(remotefile) );

	// put
	sprintf( command, "put %s %s\r\n", localfile, remotefile );
	// command write
	bRet = WriteFile( m_hPsftpStdInW, command, strlen(command), &writesize, NULL );
	// WriteFile error
	if( bRet == 0 ){
		edit1.SetWindowTextW(L"文件上传失败！");
		return;
	}
	// result read
	bRet = ReadFile( m_hPsftpStdOutR, buf, sizeof(buf), &readsize, NULL );
	// ReadFile error
	if( bRet == 0 ){
		edit1.SetWindowTextW(L"文件上传失败！");
		return;
	}
	// command succeed
	if( strstr( buf, "remote:" ) != NULL ){
		edit1.SetWindowTextW(L"文件上传成功！");
		return;
	}

	edit1.SetWindowTextW(L"文件上传失败！");
}

void COrPSFDlg::OnBnClickedButton1()
{
	DWORD writesize;

	m_IsLogin = false;

	// exit command write
	WriteFile( m_hPsftpStdInW, "exit\r\n", strlen("exit\r\n"), &writesize, NULL );

	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	if( m_hPsftpStdInR != NULL )
	{
		CloseHandle(m_hPsftpStdInR);
		m_hPsftpStdInR = NULL;
	}
	if( m_hPsftpStdInW != NULL )
	{
		CloseHandle(m_hPsftpStdInW);
		m_hPsftpStdInW = NULL;
	}
	if( m_hPsftpStdOutR != NULL )
	{
		CloseHandle(m_hPsftpStdOutR);
		m_hPsftpStdOutR = NULL;
	}
	if( m_hPsftpStdOutW != NULL )
	{
		CloseHandle(m_hPsftpStdOutW);
		m_hPsftpStdOutW = NULL;
	}

	// thread end
	// SendMessageA((HWND)m_pi.hProcess, WM_DESTROY, 0, 0);

	edit1.SetWindowTextW(L"连接已关闭！");

	PostQuitMessage(0);
}
