#pragma once

#include "ServerSocket.h"
// CServerSocket ����Ŀ��

class CServerSocket : public CSocket
{
public:
	CPtrList connectList;

public:
	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnAccept(int nErrorCode);
};


