#ifndef HANGSO_H
#define HANGSO_H

#pragma one

#include "graphics.h"
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

//Các Hằng số

enum HuongDi {UP, RIGHT, DOWN};

int const MAUMAP[4] = {0, 7, 14, 7};//Màu bản đồ
int const ROW = 20;
int const COL = 41;
int const HEIGHT = 621;
int const WIDTH = 1188;
int const TIMEEND = 150000;//250000

//XE
int const XE[3][5][5] = {

                        {//UP
                        {0, 1, 0},
                        {1, 1, 1},
                        {1, 0, 1}
                        },

                        {//RIGHT
                        {1, 1, 0},
                        {0, 1, 1},
                        {1, 1, 0}
                        },

                        {//DOWN
                        {1, 0, 1},
                        {1, 1, 1},
                        {0, 1, 0}
                        },
                        };
int const MAUXE[3] = {10, 9, 12};
int const TOCDO[3] = {125, 100, 75};
int const MANG[3] = {5, 12, 20};
int const THUONG[3] = {3, 5, 7};//Tiền thưởng khi bắn hạ địch

//THÁP
int const THAP[3][3] = {
                        {0, 1, 0},
                        {1, 1, 1},
                        {0, 1, 0}
                       };
int const MAUTHAP[3] = {14, 12, 10};//YELLOW, RED, GREEN
int const RTHAP[3] = {17, 12, 6};
int const TGBAN[3] = {150, 100, 800};
int const CULI[3] = {90, 120, 150};//Cự li bắn của tháp
int const GIACA[3] = {25, 50, 100};

//int const KITU[6] = {15, 30, 17, 16, 31, 234};// Các kí tự đặc biệt

int const RDAN = 4;
int const CANH = 9;
int const N = 100;
int const TIMESTOP = 400;

//Các Cấu Trúc

typedef struct
{
    int x, y;
} ToaDo;

typedef struct
{
    int loai, giaca, tgban, culi;
    ToaDo vt;
} Thap;

typedef struct
{
    int loai, mang, tocdo, isstop, thuong;
    HuongDi huong;
    ToaDo vt;
} Xe;

typedef struct
{
    int loai, tocdo, tgsong;
    ToaDo vt, vtcu, vtthap, dich;
} Dan;

typedef struct
{
    ToaDo vt, vtcu;
    int isclick, giaca, loaithap;
} Mouse;

#endif
