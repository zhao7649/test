#pragma once

// CClientSocket 命令目标

#pragma once

#include "ChatServerDlg.h"

// CclientSocket 命令目标

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


