// OrPSFDlg.h : header file
//

#pragma once


// COrPSFDlg dialog
class COrPSFDlg : public CDialog
{
// Construction
public:
	COrPSFDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ORPSF_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// user
	int WcharToChar( wchar_t* swchar, char* dchar, int dlen );
	int CharToWchar( char* schar, wchar_t* dwchar, int dlen );
	bool Login(char* command);


	CEdit edit1;
	CEdit edit2;
	CEdit edit3;
	CEdit edit4;
	CEdit edit5;
	CEdit edit6;
	CEdit edit7;
	char m_host[256];
	char m_user[256];
	char m_pw[256];
	bool m_IsLogin;

	// pipe
	HANDLE m_hPsftpStdInR;
	HANDLE m_hPsftpStdInW;
	HANDLE m_hPsftpStdOutR;
	HANDLE m_hPsftpStdOutW;
	STARTUPINFOW m_si;
	PROCESS_INFORMATION m_pi;
	SECURITY_ATTRIBUTES m_SecAttIn;
	SECURITY_ATTRIBUTES m_SecAttOut;
	// pipe buffer
	char m_buf[1024];
	DWORD m_readsize;
	DWORD m_writesize;

public:
	afx_msg void OnBnClickedButton5();
	afx_msg CString BootOpenDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
};
