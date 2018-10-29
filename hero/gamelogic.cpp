#include "card.h"
#include "drawgame.h"
#include "initgame.h"
#include<time.h>
#include "start.h"

int isRemove(CardMap *myCardMap,Card*first,Card*second);
int isDirectLink(CardMap *myCardMap,Card*first,Card*second);
int OnebendLink(CardMap *myCardMap,Card*first,Card*second);
int TwoBendLinks(CardMap *myCardMap,Card*first,Card*second);
int allRemove(CardMap *myCardMap);

void gameLogics(GameInfo *myGame,CardMap *myCardMap,Card *first,Card *second)
{

    if(first->id==second->id&&first->id!=0)//����ͼƬ�Ƿ�Ϊͬһ��ͼƬ
    {
         if(isRemove(myCardMap,first,second))
         {
             myGame->score+=10;
         myCardMap->cardNum--;
        myCardMap->cards[first->row][first->col].id=0;
        myCardMap->cards[second->row][second->col].id=0;
        if(myGame->score==(ROW-2)*(COL-2)/2*10)//���ȫ���꣬������һ��
          {
              myGame->level++;
              initCardMap(myCardMap);
              myGame->timeDown=120;
          }
          if(myGame->level>10)
        {
           myGame->level=1;
        }

         }

    }
}
void recordSpot(CardMap *myCardMap,Card *card)
{
    //��¼��һ����
    int i=myCardMap->link.num;
    myCardMap->link.spot[i].x=card->row*CARDWIDTH+CARDWIDTH/2;//x,y�ֱ���col��row����row��col��
    myCardMap->link.spot[i].y=card->col*CARDHEIGHT+CARDHEIGHT/2;
    myCardMap->link.num++;
}

int isRemove(CardMap *myCardMap,Card*first,Card*second)
{
    recordSpot(myCardMap,first);
    if(isDirectLink(myCardMap,first,second)||
       OnebendLink(myCardMap,first,second)||
       TwoBendLinks(myCardMap,first,second))
       {

        return 1;
       }

    else
        myCardMap->link.num=0;
        return 0;
}
int isDirectLink(CardMap *myCardMap,Card*first,Card*second)
{
    if(first->row==second->row)//ͬ��
    {
        int startCard,endCard;
        startCard=first->col<second->col?first->col:second->col;
        endCard=first->col>second->col?first->col:second->col;
        for(int i=startCard+1;i<endCard;i++)
        {
            if(myCardMap->cards[first->row][i].id!=0)
                return 0;
        }
    recordSpot(myCardMap,second);
        return 1;
    }
    if(first->col==second->col)//ͬ��
    {
        int startCard,endCard;
        startCard=first->row<second->row?first->row:second->row;
        endCard=first->row>second->row?first->row:second->row;
        for(int i=startCard+1;i<endCard;i++)
        {
            if(myCardMap->cards[i][first->col].id!=0)
                return 0;
        }
        recordSpot(myCardMap,second);
        return 1;
    }
    return 0;
}
int OnebendLink(CardMap *myCardMap,Card*first,Card*second)//��һ���յ�
{
    if(first->row!=second->row&&first->col!=second->col)//����ͼƬ����ͬһ�л���ͬһ��
  {
      recordSpot(myCardMap,first);
        if(myCardMap->cards[first->row][second->col].id==0)
    {
        if(isDirectLink(myCardMap,first,&myCardMap->cards[first->row][second->col])&&
           isDirectLink(myCardMap,&myCardMap->cards[first->row][second->col],second))
        return 1;
        else
            myCardMap->link.num--;
    }
    if(myCardMap->cards[second->row][first->col].id==0)
    {
        if(isDirectLink(myCardMap,first,&myCardMap->cards[second->row][first->col])&&
           isDirectLink(myCardMap,&myCardMap->cards[second->row][first->col],second))
        return 1;
        else
            myCardMap->link.num--;
    }
    myCardMap->link.num--;
 }
    return 0;
}
int TwoBendLinks(CardMap *myCardMap,Card*first,Card*second)//�������յ�
{
    recordSpot(myCardMap,first);
    int x,y;
    for(x=first->row;x++;x<ROW)//���⣺��x<ROW����x<=ROW?
    {
        if(myCardMap->cards[x][first->col].id!=0)
            break;
        if(OnebendLink(myCardMap,&myCardMap->cards[x][first->col],second))
            return 1;
    }
    for(x=first->row;x--;x>=0)//����:x--��x>=0��˳���Ƿ�ߵ���
    {
        if(myCardMap->cards[x][first->col].id!=0)
            break;
        if(OnebendLink(myCardMap,&myCardMap->cards[x][first->col],second))
            return 1;
    }
    for(y=first->col;y++;y<COL)
    {
        if(myCardMap->cards[first->row][y].id!=0)
            break;
        if(OnebendLink(myCardMap,&myCardMap->cards[first->row][y],second))
            return 1;
    }
    for(y=first->col;y--;y>=0)
    {
        if(myCardMap->cards[first->row][y].id!=0)
            break;
        if(OnebendLink(myCardMap,&myCardMap->cards[first->row][y],second))
            return 1;
    }
    return 0;
}

void updataGameInfo(GameInfo *myGame,CardMap *myCardMap)
{
    static time_t last=0;
    time_t cur;
    time(&cur);
    if(last!=0)
    {
        if(difftime(cur,last)>=1.0)
        {
            myGame->timeDown--;
            cleardevice();//������Ҫ����drawBG2()��ǰ��
            drawBG2();//���»���

            drawGameInfo(myGame);
            drawCardMap(myCardMap);//���ƿ�Ƭ��ͼ����
             if(myGame->timeDown<0)//����涨ʱ����û���������˳���Ϸ��������Ϸ����
                    start();
        }
    }
    last=cur;
}

int allRemove(CardMap *myCardMap)//��ʾ

{
    Card myCard1;
    Card myCard2;
    int i,j,a,b;
    for(i=1;i<=ROW-2;i++)
      for(j=1;j<=COL-2;j++)
        for(a=i;a<=ROW-2;a++)
          for(b=1;b<=COL-2;b++)
    {
        myCard1=myCardMap->cards[i][j];
        myCard2=myCardMap->cards[a][b];
        if((myCard1.row!=myCard2.row||myCard1.col!=myCard2.col)&&
           myCard1.id==myCard2.id&&myCard2.id!=0
           &&(isRemove(myCardMap,&myCard1,&myCard2)))
        {
            setlinewidth(4);
            setcolor(BLUE);
            int x=myCard1.row*CARDHEIGHT,y=myCard1.col*CARDWIDTH;
            rectangle(x,y,x+CARDHEIGHT,y+CARDWIDTH);
            x=myCard2.row*CARDHEIGHT,y=myCard2.col*CARDWIDTH;
            rectangle(x,y,x+CARDHEIGHT,y+CARDWIDTH);
            drawLink(myCardMap);
            delay_ms(60);
            return 1;
      }
    }
    return 0;
}

