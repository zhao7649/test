#include<graphics.h>
#include<stdio.h>
#include"card.h"

void drawGameInfo(GameInfo *myGame)
{
    setbkmode(TRANSPARENT);//此函数用于设置输出文字时的背景模式，TRANSPARENT指的是背景是透明的
    setfont(-40,0,"Tagettes");//此函数用于设置当前字体样式，设置当前字体为高 40 像素的“Tagettes”字体（忽略行距）。
    xyprintf(getwidth()-160,100,"第%d关",myGame->level);//此函数用于在指定位置格式化输出字符串。
    //getwidth()为获取整个屏幕宽度的函数
    xyprintf(getwidth()-160,160,"时间:%d",myGame->timeDown);
    xyprintf(getwidth()-160,220,"分数:%d",myGame->score);
}

void drawCard(Card *myCard)
{
    char imgName[70];
    sprintf(imgName,IMAGENAME,myCard->id);
    getimage(myCard->img,imgName);
    putimage(myCard->row*CARDWIDTH,myCard->col*CARDHEIGHT,myCard->img);

}

void drawCardMap(CardMap *myCardMap)
{
    int i,j;
    for(i=1; i<ROW-1; i++)
    {
        for(j=1; j<COL-1; j++)
        {
            if(myCardMap->cards[i][j].id!=0)
            {
            drawCard(&myCardMap->cards[i][j]);
            }
        }
    }
}

void drawLink(CardMap *myCardMap)
{
     setcolor(YELLOW);
       if(myCardMap->link.num>=2)
    {
        line(myCardMap->link.spot[0].x,myCardMap->link.spot[0].y
             ,myCardMap->link.spot[1].x,myCardMap->link.spot[1].y);
    }
    if(myCardMap->link.num>=3)
    {
       line(myCardMap->link.spot[1].x,myCardMap->link.spot[1].y
             ,myCardMap->link.spot[2].x,myCardMap->link.spot[2].y);
    }
    if(myCardMap->link.num>=4)
    {
        line(myCardMap->link.spot[2].x,myCardMap->link.spot[2].y
             ,myCardMap->link.spot[3].x,myCardMap->link.spot[3].y);
    }
    //line为EGE函数
    delay_ms(60);
         //line为ege函数
    myCardMap->link.num=0;
}
void drawBG()
{
    PIMAGE bg1=newimage();
    getimage(bg1,"picture\\sola01.JPEG");
    putimage(0,0,bg1);
}
void drawBG2()
{
    drawBG();
    PIMAGE bg2=newimage();
    PIMAGE bg3=newimage();
    PIMAGE exit=newimage();
    getimage(bg2,"picture\\refresh.PNG");
    getimage(bg3,"picture\\reminder.PNG");
    getimage(exit,"picture\\tuichu.PNG");
    putimage(getwidth()-160,300,bg2);
    putimage(getwidth()-160,400,bg3);
    putimage(getwidth()-160,500,exit);
}
void drawBG3()
{
    PIMAGE bg4=newimage();
    PIMAGE bg5=newimage();
    PIMAGE bg6=newimage();
    PIMAGE bg7=newimage();
    getimage(bg4,"picture\\choice.JPEG");
    getimage(bg5,"picture\\easy.JPEG");
    getimage(bg6,"picture\\normal.JPEG");
    getimage(bg7,"picture\\difficult.JPEG");
    putimage(0,0,bg4);
    putimage(getwidth()-160,200,bg5);
    putimage(getwidth()-160,300,bg6);
    putimage(getwidth()-160,400,bg7);
}

