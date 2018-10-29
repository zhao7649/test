// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ClientSocket.h"

#include "tagHeader.h"
// CClientSocket

CClientSocket::CClientSocket(CPtrList *list):m_dlgServer(NULL)
{
	clist = list;
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 成员函数


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	char buffl[sizeof(Header)];
	memset (buffl,0,sizeof(Header));
	Receive(buffl,sizeof(buffl));   //接收消息的头部
	this->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);

	Header *header = (Header *)buffl;
	int lenght = header->len;
	char type = header->type;   //解析头部内容
	if (type ==LOGIN_IO)
	{
		char buff[1000];
		memset(buff,0,sizeof(buff));
		Receive(buff,lenght); 
		this->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);
		m_dlgServer->UpdateData();
		CTime time = CTime::GetCurrentTime();
		CString t = time.Format("%H:%M:%S");
		CEdit *p_Edit = (CEdit *)::AfxGetMainWnd()->GetDlgItem(IDC_EDIT_INFO);
		CString strTemp = t +"   "+ CString(buff) + "  进入聊天室\r\n";

		p_Edit->ReplaceSel(strTemp);
		m_strName = buff;
		Header head;
		head.type = SEND_MESSAGE;
		head.len = strTemp.GetLength();

		Header head_history;
		head_history.type = SEND_MESSAGE;
		m_dlgServer->m_history += m_strName + ",  欢迎你加入\r\n";
		head_history.len = m_dlgServer->m_history.GetLength();

		CClientSocket *curr = NULL;
		POSITION pos = clist->GetHeadPosition();
		while(pos !=NULL)
		{
			curr = (CClientSocket *)clist->GetNext(pos);
			if (curr->m_strName == m_strName)
			{
				curr->Send((char *)&head_history,sizeof(Header));
				curr->Send(m_dlgServer->m_history,m_dlgServer->m_history.GetLength());

			} 
			else
			{
				curr->Send((char *)&head,sizeof(Header));
				curr->Send(strTemp,strTemp.GetLength());
			}
		}
		m_dlgServer->UpdateUser(this);//更新用户列表
	}
	if (type == SEND_MESSAGE) //头部为SEND_MESSAGE，成员之间的聊天信息
	{
		char buff[1000];
		memset(buff,0,sizeof(buff));
		Receive(buff,sizeof(buff));
		this->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);
		CTime time = CTime::GetCurrentTime();
		CString t = time.Format("%H:%M:%S");
		CString nikeName = this->m_strName;
		CString strTemp = t + "   " + nikeName + "  说: " + CString(buff) + "\r\n";

		CString str = nikeName + "   " + t +"\r\n   " + CString(buff) + "\r\n";

		CEdit *p_Edit = (CEdit *)::AfxGetMainWnd()->GetDlgItem(IDC_EDIT_INFO);
		p_Edit->ReplaceSel(strTemp);

		CClientSocket *curr = NULL;
		POSITION pos = clist->GetHeadPosition();
		while (pos !=NULL)
		{
			curr = (CClientSocket *)clist->GetNext(pos);
			curr->Send((char *)header,sizeof(Header));
			curr->Send(str,str.GetLength());
		}
	}

	CSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	POSITION pos = clist->Find(this);
	if (pos != NULL)
	{
		clist->RemoveAt(pos);
		CTime time = CTime::GetCurrentTime();
		CString t = time.Format("%H:%M:%S");
		CEdit *p_Edit = (CEdit *)m_dlgServer->GetDlgItem(IDC_EDIT_INFO);
		CString strTemp = t + "   "+ this->m_strName + "  离开聊天室\r\n";
		p_Edit->ReplaceSel(strTemp);

		Header head;
		head.type = SEND_MESSAGE;
		head.len = strTemp.GetLength();
		CClientSocket *curr = NULL;
		POSITION pos = clist->GetHeadPosition();
		while(pos != NULL)
		{
			curr = (CClientSocket *)clist->GetNext(pos);
			curr -> Send((char *)&head,sizeof(Header));
			curr -> Send(strTemp,strTemp.GetLength());
		}
		m_dlgServer->UpdateUser(this);
		this->Close();
		delete this;
	}
	CSocket::OnClose(nErrorCode);
}
