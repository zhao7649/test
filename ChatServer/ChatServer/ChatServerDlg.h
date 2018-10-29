
// ChatServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


class CServerSocket;  //监听套接字
class CClientSocket;   //与客户端通信的套接字类

// CChatServerDlg 对话框
class CChatServerDlg : public CDialogEx
{
// 构造
public:
	CChatServerDlg(CWnd* pParent = NULL);	// 标准构造函数

	CServerSocket *m_pSocket;
	CClientSocket *clientSocket;
	void UpdateUser(CClientSocket *pSocket);

// 对话框数据
	enum { IDD = IDD_CHATSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Admin;
	CString m_strName;
	CIPAddressCtrl ServerIP;
	CEdit ServerPort;
	CString sPort;
	CButton m_Start;
	CButton m_Stop;
	CButton m_Exit;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CListBox m_UserList;
	CEdit m_MessageList;
	CString m_history;
};
