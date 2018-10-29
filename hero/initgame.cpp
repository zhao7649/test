#include <graphics.h>
#include<time.h>//日期与时间头文件
#include "card.h"

void initGameInfo(GameInfo *myGame)//初始化游戏的关卡，分数，倒计时
{
    myGame->level=1;
    myGame->score=0;
    myGame->timeDown=100;//倒计时180秒
}

void initCard(Card *myCard,int i,int j)
{
    myCard->row=i;
    myCard->col=j;
    myCard->img=newimage();
    myCard->id=0;
}
void initCardMap(CardMap *myCardMap)
{
    int i,j;
    myCardMap->cardNum=(ROW-2)*(COL-2)/2;
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            initCard(&myCardMap->cards[i][j],i,j);
        }
    }
    int x,y,id=1;
    srand((int )time(NULL));
    for(i=0; i<(ROW-2)*(COL-2)/2; i++)
    {
        for(j=0; j<2; j++)
        {
            do
            {
                x=rand()%(ROW-2)+1;
                y=rand()%(COL-2)+1;
            }
            while(myCardMap->cards[x][y].id!=0);
            myCardMap->cards[x][y].id=id;
        }
        id++;
        if(id>20)
            id=1;
    }
}
int reInitCardMap(CardMap *myCardMap)//重排
{
    struct
    {
        int x;
        int y;
    }cardXY[100];
    int cardId[100]={0};
    int K=1,w;
    myCardMap->link.num=0;
    srand((int)time(NULL));

    for(int i=1;i<ROW-1;i++)
    {
        for(int j=1;j<COL-1;j++)
        {
            if(myCardMap->cards[i][j].id!=0)
            {
                cardXY[K].x=i;
                cardXY[K].y=j;
                cardId[K]=myCardMap->cards[i][j].id;
                myCardMap->cards[i][j].id=0;
                K++;
            }
        }
    }
    for(int i=1;i<K;i++)
    {
        w=rand()%K+1;
        while(cardId[w]==0)
        {
            w=rand()%K+1;
        }
        myCardMap->cards[cardXY[i].x][cardXY[i].y].id=cardId[w];
        cardId[w]=0;
    }
}

