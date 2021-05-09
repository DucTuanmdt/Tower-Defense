#include "hangso.h"
#include "hienthi.h"
#include "xuli.h"

void InHelp()
{
    cleardevice();

    FILE *fin = fopen("help.txt", "rt");
    if (!fin)
        return;

    settextstyle(4, HORIZ_DIR, 1);
    int i = 3;
    char s[N] = "";
    while (!feof(fin))
    {
        fgets(s, N, fin);
        s[strlen(s) - 1] = 0;

        outtextxy(WIDTH / 2 - strlen(s) * 7, i * 30, s);
        i++;
    }

    fclose(fin);

    getch();
}

///Cái này lúc nãy em sửa theo anh nói
/*
void InLuaChon(int *pvt, char s[][N], int n)
{
    int x = WIDTH / 2, y = HEIGHT / 2 - n / 2 * 75;
    int i;

    cleardevice();
    settextstyle(4, HORIZ_DIR, 5);

    while (1)
    {
        for (i = 0; i < n; i++)
        {
            if (i == (*pvt))
                setcolor(YELLOW);
            else
                setcolor(WHITE);

            outtextxy(x - strlen(s[i]) / 2 * 40 , y + 75 * i, s[i]);
        }

        if (GetAsyncKeyState(VK_UP) & 0x8000)
            {
                mciSendString("play sound//click.wav", 0, 0, 0);
                (*pvt)--;
                if ((*pvt) == -1)
                    (*pvt) = n - 1;
            }
         if (GetAsyncKeyState(VK_DOWN) & 0x8000)
            {
                mciSendString("play sound//click.wav", 0, 0, 0);
                (*pvt)++;
                (*pvt) %= n;
            }
         if (GetAsyncKeyState(VK_RETURN) & 0x8000)
                {
                    mciSendString("stop sound//correct.wav", 0, 0, 0);
                    mciSendString("play sound//correct.wav", 0, 0, 0);
                    return;
                }

           //delay(150);
    }
}*/

///Đây là code ban đầu
void InLuaChon(int *pvt, char s[][N], int n)
{
    int x = WIDTH / 2, y = HEIGHT / 2 - n / 2 * 75;
    int i;

    cleardevice();
    settextstyle(4, HORIZ_DIR, 5);

    while (1)
    {
        for (i = 0; i < n; i++)
        {
            if (i == (*pvt))
                setcolor(YELLOW);
            else
                setcolor(WHITE);

            outtextxy(x - strlen(s[i]) / 2 * 40 , y + 75 * i, s[i]);
        }

        if (GetAsyncKeyState(VK_UP))
            {
                mciSendString("play sound//click.wav", 0, 0, 0);
                (*pvt)--;
                if ((*pvt) == -1)
                    (*pvt) = n - 1;
            }
        else if (GetAsyncKeyState(VK_DOWN))
            {
                mciSendString("play sound//click.wav", 0, 0, 0);
                (*pvt)++;
                (*pvt) %= n;
            }
        else if (kbhit())
                if (getch() == 13)
                {
                    mciSendString("stop sound//correct.wav", 0, 0, 0);
                    mciSendString("play sound//correct.wav", 0, 0, 0);
                    return;
                }

           delay(150);
    }
}

void InSetting(int *pbando, int *plevel)
{
    int i;
    int vt = 0;
    char level[5][N] = {"Easy", "Normal", "Hard"};
    char bando[3][N] = {"Map  1", "Map  2", "Map  3"};

    InLuaChon(plevel, level, 3);

    InLuaChon(pbando, bando, 3);
}

int InMenu(int *pbando, int *plevel)
{
    char menu[5][N] = {"Play", "Setting", "Help", "Exit"};
    int vt = 0;
    setbkcolor(GREEN);

startmenu:

    InLuaChon(&vt, menu, 4);

    switch (vt)
    {
        case 1:
            {
                InSetting(pbando, plevel);
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

void InXe(Xe xe[N], int n)
{
    int i, j, k;
    int x, y;

    setcolor(WHITE);
    setbkcolor(BLACK);

    for (k = 0; k < n; k++)
    {
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
            {
                x = xe[k].vt.x + (j - 1) * CANH;
                y = xe[k].vt.y + (i - 1) * CANH;

                if (XE[xe[k].huong][i][j])
                    setfillstyle(9, MAUXE[xe[k].loai]);
                else
                    setfillstyle(0, 0);

                bar(x - CANH / 2, y - CANH / 2, x + CANH / 2, y + CANH / 2);

                if (XE[xe[k].huong][i][j])
                    rectangle(x - CANH / 2, y - CANH / 2, x + CANH / 2, y + CANH / 2);
            }
    }
}

void InThap(Thap thap[], int n)
{
    int i, j, k;
    int x, y;

    for (k = 0; k < n; k++)
    {
        setfillstyle(1, MAUTHAP[thap[k].loai]);
        fillellipse(thap[k].vt.x, thap[k].vt.y,RTHAP[0], RTHAP[0]);

        setfillstyle(1, 9);
        fillellipse(thap[k].vt.x, thap[k].vt.y,RTHAP[1],RTHAP[1]);

        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
            {
                if (THAP[i][j])
                {
                    x = thap[k].vt.x + (i - 1) * CANH;
                    y = thap[k].vt.y + (j - 1) * CANH;

                    setfillstyle(1, RED);
                    bar(x - CANH / 2, y - CANH / 2, x + CANH / 2, y + CANH / 2);
                }
            }

        setfillstyle(1, MAUTHAP[thap[k].loai]);
        fillellipse(thap[k].vt.x, thap[k].vt.y,RTHAP[2],RTHAP[2]);
    }
}

void XoaDanCu(int bando[][COL], ToaDo vt)
{
    int i, j;

    i = vt.x / (CANH * 3);
    j = vt.y / (CANH * 3);

    setfillstyle(1, MAUMAP[bando[j][i]]);
    setcolor(MAUMAP[bando[j][i]]);
    fillellipse(vt.x, vt.y, RDAN, RDAN);
    circle(vt.x, vt.y, RDAN);

}

void InDan(Dan dan[N], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        setfillstyle(1, MAUTHAP[dan[i].loai]);
        fillellipse(dan[i].vt.x, dan[i].vt.y, RDAN, RDAN);
    }
}

void InMotO(int i, int j, int mau, int dang)
{
    setfillstyle(dang, mau);
    bar(i * CANH * 3, j * CANH * 3, (i + 1) * CANH * 3, (j + 1) * CANH * 3);
}

void InMap(int bando[][COL])
{
    int i, j;

    for (i = 0; i < ROW; i++)
        for (j = 0; j < COL; j++)
            InMotO(j, i, MAUMAP[bando[i][j]], 1);
}

void XoaXeCu(Xe xe[], int n, int thetime)
{
    int i, j, k;
    int x, y;

    for (k = 0; k < n; k++)
        if (thetime % xe[k].tocdo == 0)
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
            {
                x = xe[k].vt.x + (j - 1) * CANH;
                y = xe[k].vt.y + (i - 1) * CANH;

                setfillstyle(0, 0);
                bar(x - CANH / 2, y - CANH / 2, x + CANH / 2 + 1, y + CANH / 2 + 1);
            }
}

void LamSachDan(int bando[][COL], Dan dan[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        XoaDanCu(bando, dan[i].vt);
}

void InVien()
{
    setfillstyle(1, GREEN);

    bar(WIDTH - CANH * 3 * 3, 0,WIDTH, HEIGHT);
    bar(0, HEIGHT - CANH * 3 * 3, WIDTH, HEIGHT);
}

void InItem(int mangsong, int money)
{
    setcolor(WHITE);
    setbkcolor(GREEN);
    settextstyle(6, HORIZ_DIR, 1);


    char s[6][10];
    sprintf(s[0], "%d", mangsong);

    outtextxy(1112, 20, "  Life");
    outtextxy(1140, 45, s[0]);

    sprintf(s[1], " %d  ", money);
    outtextxy(1112, 100, "Money");

    outtextxy(1120, 130, s[1]);

    int i;
    for (i = 0; i < 3; i++)
        sprintf(s[2 + i], "  $ %d", GIACA[i]);

    sprintf(s[5], "   Sell");

    Thap thap[4];
    int n = 0;
    ToaDo vt = {1147,200};

    for (i = 0; i < 4; i++)
    {
        thap[n].loai = i % 3;
        thap[n++].vt = vt;
        outtextxy(1108, vt.y + 20, s[i + 2]);

        InThap(thap, n);
        vt.y += 81;
    }

    for (i = 0; i < 6; i++)
        rectangle(1108, i * 81, 1189, (i + 1) * 81 - 1);

    setcolor(RED);
    setlinestyle(0, 0, 4);
    i--;
    line(1108, i * 81, 1189, (i + 1) * 81 - 1);
    setlinestyle(0, 0, 0);
}

void InProcess(ToaDo process[], char s[])
{
    setfillstyle(1, 10);
    setbkcolor(GREEN);
    setcolor(WHITE);
    settextstyle(6, HORIZ_DIR, 2);

    ToaDo vt;
    vt.y = process[0].y - 35;
    //vt.x = (process[0].x + process[2].x) / 2 - strlen(s) / 2 - process[0].x;
    vt.x = (process[0].x + process[2].x) / 2 - strlen(s) / 2 * 15;
    outtextxy(vt.x, vt.y, s);

    vt =  process[1];

    bar(process[0].x, process[0].y - 13, vt.x, vt.y + 13);
    rectangle(process[0].x, process[0].y - 14, process[2].x, process[2].y + 14);
    rectangle(process[0].x + 2, process[0].y - 12, process[2].x - 2, process[2].y + 12);

    if (vt.x < process[2].x)
        (process[1]).x += 1;
    if ((process[1]).x > process[2].x)
        (process[1]).x = process[2].x;

}

void InChienThang()
{
    mciSendString("stop sound//gamemusic.mp3", 0, 0, 0);
    mciSendString("play sound//win.wav", 0, 0, 0);
    settextstyle(4, HORIZ_DIR, 8);
    outtextxy(300,280, "You Win!");
    getch();
}

void InThua()
{
    mciSendString("stop sound//gamemusic.mp3", 0, 0, 0);
    mciSendString("play sound//loose.wav", 0, 0, 0);
    settextstyle(4, HORIZ_DIR, 8);
    outtextxy(300,280, "You Loose!");
    getch();
}

void InLoading()
{
    ToaDo process[3] = {{200, 310}, {210, 310}, {990, 310}};

    cleardevice();

    int thetime = 0;
    PlaySound(TEXT("sound//loading.wav"), 0, SND_ASYNC);

    while (thetime < 4000)
    {

        delay(2);
        thetime += 5;
        InProcess(process, "Loading...");
    }

    PlaySound(TEXT("sound//correct.wav"), 0, SND_ASYNC);
}

