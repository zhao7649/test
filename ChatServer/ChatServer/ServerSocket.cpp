// ServerSocket.cpp : ʵ���ļ�
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


// CServerSocket ��Ա����



void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CClientSocket *clientSocket = new CClientSocket(&connectList);//����socket���нṹ
	Accept(*clientSocket);  //��������
	clientSocket->m_dlgServer = (CChatServerDlg *)::AfxGetMainWnd();
	connectList.AddTail(clientSocket);  //�ڶ���������³�Ա��socket

	CSocket::OnAccept(nErrorCode);
}
