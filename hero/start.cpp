#include<graphics.h>
#include<stdio.h>

void start()
{
    initgraph(879,680);
    PIMAGE p1=newimage();
    PIMAGE p2=newimage();
    PIMAGE p3=newimage();
    PIMAGE p4=newimage();
    getimage(p1,"picture\\sola01.jpg");
    putimage(0,0,p1);
    getimage(p2,"picture\\start.jpg");
    putimage(350,280,p2);
    getimage(p3,"picture\\end.jpg");
    putimage(350,360,p3);
    getimage(p4,"picture\\list.png");
    putimage(340,440,p4);
    mouse_msg msg={0};
    MUSIC mus;
    mus.OpenFile("music\\sola.mp3");
    mus.Play();
    for(;is_run();delay_fps(100))
    {
        if(mousemsg())
        {
            msg=getmouse();

            if(msg.is_down()&&msg.x>=350&&msg.x<=350+getwidth(p2)&&
               msg.y>=280&&msg.y<=280+getheight(p2))
            {
                setlinewidth(4);
                setcolor(YELLOW);
                rectangle(350,280,350+getwidth(p2),280+getheight(p2));
                delay_ms(20);
                cleardevice();
                initgraph(879,680);
                PIMAGE v1=newimage();
                PIMAGE v2=newimage();
                PIMAGE v3=newimage();
                PIMAGE v4=newimage();
                getimage(v1,"picture\\choice.jpg");
                putimage(0,0,v1);
                getimage(v2,"picture\\easy.jpg");
                putimage(350,280,v2);
                getimage(v3,"picture\\nomal.jpg");
                putimage(350,380,v3);
                getimage(v4,"picture\\difficult.jpg");
                putimage(350,480,v4);
                mouse_msg msg={0};
                for(;is_run();delay_fps(100))
    {
        if(mousemsg())
        {
               msg=getmouse();
                if(msg.is_down()&&msg.x>=350&&msg.x<=350+getwidth(v2)&&
               msg.y>=280&&msg.y<=280+getheight(v2))
               {
                    setlinewidth(4);
                setcolor(YELLOW);
                rectangle(350,280,350+getwidth(v2),280+getheight(v2));
                delay_ms(20);
                cleardevice();
                return;
               }
               if(msg.is_down()&&msg.x>=350&&msg.x<=350+getwidth(v3)&&
               msg.y>=380&&msg.y<=380+getheight(v3))
               {
                     setlinewidth(4);
                setcolor(YELLOW);
                rectangle(350,380,350+getwidth(v3),380+getheight(v3));
                delay_ms(20);
                cleardevice();
                return;
               }
               if(msg.is_down()&&msg.x>=350&&msg.x<=350+getwidth(v4)&&
               msg.y>=480&&msg.y<=480+getheight(v4))
               {
                     setlinewidth(4);
                setcolor(YELLOW);
                rectangle(350,480,350+getwidth(v4),480+getheight(v4));
                delay_ms(20);
                cleardevice();
                return;
               }

        }
    }
                return;
            }
            if(msg.is_down()&&msg.x>=350&&msg.x<=350+getwidth(p3)&&
               msg.y>=360&&msg.y<=360+getheight(p3))
            {
                setlinewidth(4);
                setcolor(YELLOW);
                rectangle(350,360,350+getwidth(p3),360+getheight(p3));
                delay_ms(20);
                closegraph();
            }
            if(msg.is_down()&&msg.x>=340&&msg.x<=340+getwidth(p4)&&
               msg.y>=440&&msg.y<=440+getheight(p4))
            {
                setlinewidth(4);
                setcolor(YELLOW);
                rectangle(340,440,340+getwidth(p4),440+getheight(p4));
                delay_ms(20);
                cleardevice();
                return;
            }
        }
    }
    return ;
}
