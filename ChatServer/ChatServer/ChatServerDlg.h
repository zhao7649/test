
// ChatServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


class CServerSocket;  //�����׽���
class CClientSocket;   //��ͻ���ͨ�ŵ��׽�����

// CChatServerDlg �Ի���
class CChatServerDlg : public CDialogEx
{
// ����
public:
	CChatServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

	CServerSocket *m_pSocket;
	CClientSocket *clientSocket;
	void UpdateUser(CClientSocket *pSocket);

// �Ի�������
	enum { IDD = IDD_CHATSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
