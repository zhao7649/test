
// ChatServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "tagHeader.h"
#include "ServerSocket.h"
#include "ClientSocket.h"
#include <atltime.h>
#include <afxwin.h>

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CChatServerDlg 对话框




CChatServerDlg::CChatServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatServerDlg::IDD, pParent)
{
	 m_strName = _T("");
	 sPort = _T("");
	 m_history = _T("");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Admin);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Control(pDX, IDC_IPADDRESS1, ServerIP);
	DDX_Control(pDX, IDC_EDIT2, ServerPort);
	DDX_Text(pDX, IDC_EDIT2, sPort);
	DDX_Control(pDX, IDC_EDIT3, m_MessageList);
	DDX_Text(pDX, IDC_EDIT3, m_history);
	DDX_Control(pDX, IDC_LIST1, m_UserList);
	DDX_Control(pDX, IDC_BUTTON1, m_Start);
	DDX_Control(pDX, IDC_BUTTON2, m_Stop);
	DDX_Control(pDX, IDCANCEL, m_Exit);
	DDX_Control(pDX, IDC_LIST1, m_UserList);
	DDX_Control(pDX, IDC_EDIT_INFO, m_MessageList);
	DDX_Text(pDX, IDC_EDIT_INFO, m_history);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CChatServerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CChatServerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CChatServerDlg 消息处理程序

BOOL CChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_pSocket = NULL;
	clientSocket = NULL;
	//初始界面
	m_Admin.SetFocus();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatServerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_pSocket = new CServerSocket;
	BYTE nFild[4];
	CString sIP;
	ServerIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]); //获取管理员配置IP
	CTime time = CTime::GetCurrentTime();

	if (m_strName.IsEmpty())
	{
		AfxMessageBox("请登记管理员名");
		return;
	}
	if (sIP.IsEmpty())
	{
		AfxMessageBox("请配置IP地址");
		return;
	}
	if (sPort.IsEmpty())
	{
		AfxMessageBox("请配置开放端口");
		return;
	}

	if(m_pSocket->Create(atoi(sPort),1,sIP))   //开放聊天室，创建监视套接字
	{
 		m_MessageList.SetWindowTextA("");
		m_MessageList.ReplaceSel("聊天室开启成功\r\n");
		CString t = time.Format("%Y-%m-%d");
		m_MessageList.ReplaceSel("日期:" + t + "\r\n" );
		t = time.Format("%H:%M:%S");
		theApp.m_strName = m_strName;
		m_MessageList.ReplaceSel(t + "管理员 " +theApp.m_strName +" 开放聊天室\r\n");
	}	
	else
	{
		m_MessageList.ReplaceSel("聊天室开启失败。\r\n");
	}
	if (m_pSocket->Listen())
	{
		m_MessageList.ReplaceSel("等待成员加入...\r\n");
	}
	m_UserList.ResetContent();
	m_UserList.AddString(theApp.m_strName);
}

void CChatServerDlg::UpdateUser(CClientSocket *pSocket)
{
	m_UserList.ResetContent();
	m_UserList.AddString(theApp.m_strName);
	CString user_info;
	user_info = theApp.m_strName + "&";
	if (pSocket != NULL)
	{
		CClientSocket *pSock = NULL;
		POSITION pos = pSocket->clist->GetHeadPosition();
		while(pos != NULL)
		{
			pSock = (CClientSocket *)pSocket->clist->GetNext(pos);
			m_UserList.AddString(pSock->m_strName);
			user_info += (pSock->m_strName +"&");
		}
		Header head;
		head.type = LOGIN_IO;
		head.len = user_info.GetLength();

		POSITION po = pSocket->clist->GetHeadPosition();
		while(po != NULL)                   //将最新用户列表转发给各用户
		{
			pSock = (CClientSocket *)pSocket->clist->GetNext(po);
			pSock->Send((char *)&head,sizeof(Header));
			pSock->Send((LPCTSTR)user_info,user_info.GetLength());
		}
	}
}

void CChatServerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pSocket->Close();
	m_pSocket = NULL;
	CTime time = CTime::GetCurrentTime();
	CString t = time.Format("%H:%M:%S");
	CString strTemp = t + " 管理员 " + theApp.m_strName +" 关闭聊天室\r\n";
	m_MessageList.ReplaceSel(strTemp);
	m_UserList.ResetContent();
}
