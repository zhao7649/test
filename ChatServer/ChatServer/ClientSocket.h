#pragma once

// CClientSocket ����Ŀ��

#pragma once

#include "ChatServerDlg.h"

// CclientSocket ����Ŀ��

class CClientSocket : public CSocket
{
public:
CString m_strName;
	CPtrList *clist;
	CChatServerDlg *m_dlgServer;
	CClientSocket(CPtrList *list);
public:
	CClientSocket();
	virtual ~CClientSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


