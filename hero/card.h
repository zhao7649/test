#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
#include <graphics.h>
#define CARDWIDTH 60
#define CARDHEIGHT 60
#define ROW 8
#define COL 8
#define IMAGENAME "PIC\\%d.png"

typedef struct
{
    int level;
    int score;
    int timeDown;
}GameInfo;

typedef struct
{
    int row;
    int col;
    PIMAGE img;
    int id;//����ÿ��ͼƬ

} Card;

typedef struct
{
    int x,y;
}Coord;//����

typedef struct
{
    Coord spot[4];
    int num;
}Link;

typedef struct
{
    Card cards[ROW][COL];
    int cardNum;//��Ƭ����
    Link link;
} CardMap;

#endif // CARD_H_INCLUDED
