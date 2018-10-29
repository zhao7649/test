#include<stdio.h>
#include<graphics.h>
#include"kuangjia.h"
#include"start.h"
int main()
{
    start();
    initgraph(840,700);
    PIMAGE img1=newimage();
    getimage(img1,"pictuer//84.png");
    MUSIC mus;
    mus.OpenFile("music\\hhh-03.mp3");
    mus.Play();
    putimage(0,0,img1);
    gameFrame();
    getch();
    closegraph();
    return 0;
}
