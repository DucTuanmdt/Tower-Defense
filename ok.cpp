//#include "bailam.h"
#include "hangso.h"

/*
void InHelp()
{
    cleardevice();

    settextstyle(4, HORIZ_DIR, 1);
    outtextxy(200, 150, "Bay gio chua nghi ra luat choi!");

    getch();
}

void InLuaChon(int *pvt, char s[][N], int n)
{
    int x = 200, y = 150;
    int i;

    cleardevice();

    while (1)
    {
        for (i = 0; i < n; i++)
        {
            if (i == (*pvt))
                setcolor(YELLOW);
            else
                setcolor(WHITE);

            settextstyle(4, HORIZ_DIR, 5);
            outtextxy(x , y + 75 * i, s[i]);
        }


        if (GetAsyncKeyState(VK_UP))
            {
                (*pvt)--;
                if ((*pvt) == -1)

                    (*pvt) = n - 1;
            }
        else if (GetAsyncKeyState(VK_DOWN))
            {
                (*pvt)++;
                (*pvt) %= n;
            }
        else if (kbhit())
            {
                if (getch() == 13)
                    return;
            }

           delay(150);
    }
}

void InSetting(int *pbando, int *pdokho)
{
    int i;
    int vt = 0;
    char level[5][N] = {"     Level 1     ", "     Level 2     ", "     Level 3     "};
    char bando[3][N] = {"      Map 1      ", "      Map 2      ", "      Map 3      "};

    InLuaChon(pbando, level, 3);

    InLuaChon(pdokho, bando, 3);
}

#define px 21

int InMenu(int *pbando, int *pdokho)
{
    int vt = 0;
    //int maxp = getmaxx();
    char s[5][N] = {"     Play Game     ", "        Setting        ", "          Help        ", "          Exit        "};

    //(0,HORIZ_DIR, 10);
    int i, j;

    int a[N][N] = { {0, 0, 0, 0, 0},
                    {0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0},
                    {0, 1, 1, 0, 0},
                    {0, 0, 0, 0, 0} };
    int n = 5;

    setcolor(10);

    int k = 0, h = 0;
    int x, y;
    int time = 0;

    int run;
    for (run = 0; run < 80; run++)
    {
        setfillstyle(1, run);
        bar(10 * run, 10, 10 * run + 10, 20);

    }

    getch();


    char c[] = " ";
    sprintf(c, "%c", 271);

    for (run = 0; run < 10; run++)
    {

    settextstyle(run, 0, 1);

    outtextxy(30 + run * 20, 30, c);

    getch();
    }


    while (k < 100)
    {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
            {
                setcolor(a[j][i] != 0 ? 2 : 0);
                setfillstyle(1, a[j][i]);

                x = (k + i) * px;
                y = ( j) * px;


                bar(x + 1, y + 1, x + px - 1, y + px - 1);

                //if (a[j][i])
                   //i rectangle(x, y, x + px, y + px);

                setfillstyle(1, 1);

                bar(h * px, 150 + h, h * px + px, 150 + h + px);

                delay(1);
                time += 1;
                if (time % 30 == 0)
                {
                    //cleardevice();
                    setfillstyle(0, 0);
                    setcolor(0);
                    bar(x, y, x + px, y + px);

                //if (a[j][i])
                    //rectangle(x, y, x + px, y + px);

                    k++;
                }

                setfillstyle(0, 0);

                bar(h * px, 150 + h, h * px + px, 150 + h + px);

            }
            h++;





    }


        getch();

    for (i = 0; i < 999 - px; i+= px)
    {
        setcolor(10 % px);
        for (j = 0; j < 999 - px; j+= px)
        {
            setcolor((i * i + j * j + i + j + 7) % 16);
            setfillstyle(1, (i * i + j * j + i + j) % 16);


            rectangle(i, j, i + px, j + px);
            delay(1);



            delay(1);
            if ((i + j) % 2 == 0)
                bar(i + 1, j + 1, i + px - 2, j + px - 2);
            else
            {
                fillellipse(i, j, px / 2 - 2, px / 2 - 2);
                circle(i, j, px / 2);
            }



        }

    }

    getch();



    startmenu:

    InLuaChon(&vt, s, 4);

    switch (vt)
    {
        case 1:
            {
                InSetting(pbando, pdokho);
                goto startmenu;
            }
        case 2:
            {
                InHelp();
                goto startmenu;
            }
    }

    return vt;
}

*/
