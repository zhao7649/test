// ServerSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ServerSocket.h"

#include "ClientSocket.h"
// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 成员函数



void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CClientSocket *clientSocket = new CClientSocket(&connectList);//创建socket队列结构
	Accept(*clientSocket);  //接受请求
	clientSocket->m_dlgServer = (CChatServerDlg *)::AfxGetMainWnd();
	connectList.AddTail(clientSocket);  //在队列中添加新成员的socket

	CSocket::OnAccept(nErrorCode);
}
