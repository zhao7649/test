typedef struct tagHeader
{
	char type; 
	int len;   //��Ϣ����
}Header,*pHeader;

#define LOGIN_IO    1    //��¼
#define SEND_MESSAGE    3     //������Ϣ