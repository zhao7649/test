#include "card.h"
#include "initgame.h"
#include "drawgame.h"
#include "gamelogic.h"
#include "start.h"

void frameLoop(GameInfo *myGame,CardMap *myCardMap);
Card getCardInfo(CardMap *myCardMap,mouse_msg msg);
void gameFrame()
{
    CardMap myCardMap;
    GameInfo myGame;

    drawBG();
    initGameInfo(&myGame);
    initCardMap(&myCardMap);
    drawCardMap(&myCardMap);
    drawGameInfo(&myGame);
    frameLoop(&myGame,&myCardMap);
}
void frameLoop(GameInfo *myGame,CardMap *myCardMap)
{
    mouse_msg msg={0};
    int flage=1,p=0;
    Card frist;
    Card second;
    for(;is_run();delay_fps(1000))
    {
        updataGameInfo(myGame,myCardMap);
        if(frist.id!=0&&p==1)
        {
            int x=frist.row*CARDHEIGHT;
            int y=frist.col*CARDWIDTH;
            rectangle(x,y,x+CARDWIDTH,y+CARDHEIGHT);
        }
        if(mousemsg())
        {
            msg=getmouse();
            if(msg.is_down()&&msg.x>=getwidth()-160&&
               msg.x<=(ROW-1)*getwidth()-100&&
               msg.y>=300&&msg.y<=360)
               {
                   setlinewidth(4);
                   setcolor(BLUE);
                   rectangle(getwidth()-160,300,getwidth()-100,360);
                   delay_ms(20);
                   reInitCardMap(myCardMap);/*重排*/
               }
               else if(msg.is_down()&&msg.x>=getwidth()-160&&
                       msg.x<=getwidth()-100&&
                       msg.y>=400&&msg.y<=460)
               {
                   setlinewidth(4);
                   setcolor(RED);
                   rectangle(getwidth()-160,400,getwidth()-100,460);
                   delay_ms(20);
                   allRemove(myCardMap);/*提示*/
               }
               else if(msg.is_down()&&msg.x>=getwidth()-160&&
                       msg.x<=getwidth()-100&&
                       msg.y>=500&&msg.y<=560)
                {
                    setlinewidth(4);
                    setcolor(BROWN);
                    rectangle(getwidth()-160,500,getwidth()-100,560);
                    delay_ms(20);
                    start();
                }
                else if(msg.is_down()&&msg.x>=CARDWIDTH&&
               msg.x<=(ROW-1)*CARDWIDTH&&
               msg.y>=CARDHEIGHT&&msg.y<=(COL-1)*CARDHEIGHT)
            {
                if(flage==1)
                {
                    frist=getCardInfo(myCardMap,msg);
                    flage=0;
                    p=1;
                }
                else
                {
                    second=getCardInfo(myCardMap,msg);
                    flage=1;
                    p=0;

                    if(frist.row!=second.row||frist.col!=second.col)//ÅÅ³ýÍ¬Ò»ÕÅ¿¨Æ¬
                    {
                   gameLogics(myGame,myCardMap,&frist,&second);
                    }
                    drawLink(myCardMap);
                    delay_ms(60);
                    cleardevice();
                    PIMAGE img1=newimage();
                    getimage(img1,"picture//84.png");
                    putimage(0,0,img1);
                    drawCardMap(myCardMap);
                }
            }

        }
    }
}
Card getCardInfo(CardMap *myCardMap,mouse_msg msg)
{
    int x,y,i,j;
    Card card;
    i=msg.x/CARDWIDTH;
    j=msg.y/CARDHEIGHT;
    if(myCardMap->cards[i][j].id!=0)
    {
        x=i*CARDWIDTH;
        y=j*CARDHEIGHT;
        setlinewidth(3);
        setcolor(RED);
        rectangle(x,y,x+CARDWIDTH,y+CARDHEIGHT);
    }
    card=myCardMap->cards[i][j];
    return card;
}
