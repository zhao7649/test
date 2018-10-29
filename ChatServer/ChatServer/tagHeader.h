typedef struct tagHeader
{
	char type; 
	int len;   //消息长度
}Header,*pHeader;

#define LOGIN_IO    1    //登录
#define SEND_MESSAGE    3     //发送信息