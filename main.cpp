#include "hangso.h"
#include "hienthi.h"
#include "xuli.h"
#include <mmsystem.h>


void Xuat(int a[][COL])
{
    int i, j;
    char s[] = "      ";

    sprintf(s,"x%d", getmaxx());

    outtext(s);

    sprintf(s, "y%d", getmaxy());
    outtext(s);

    getch();

    settextstyle(0, 0, 2);

    for (i = 0; i < ROW; i++)
        for (j = 0; j < COL; j++)
        {
            sprintf(s, "%d", a[i][j]);
            outtextxy(j * 20, i * 20, s);
        }

}

int main(void)
{

    initwindow(WIDTH, HEIGHT, "My Game");

    start_my_game:

    char themap[20] = "";
    int bando[ROW][COL];
    int chonbando = 0, level = 0;

    if (InMenu(&chonbando, &level) == 3) //Exit
        return 1;

    sprintf(themap, "map%d.txt", chonbando + 1);
    if (!DocFile(themap, bando))
        return 1;

    srand(time(0));
    InLoading();

    int mangsong = 4;
    int money = 50;
    int thetime = 5;
    int tgsinh = 2500;
    int change = 0;//flag để in lại item và bản đồ
    Mouse mouse;
    mouse.vtcu.x = 100;
    mouse.vtcu.y = 100;
    mouse.isclick = 0;
    //Tọa độ để in Process
    ToaDo process[3] = { {40, 580}, {50, 580}, {1070, 580}};

    Xe xe[N];
    int nxe = 0;
    Thap thap[N];
    int nthap = 0;

    Dan dan[N];
    int ndan = 0;
    InMap(bando);
    InVien();
    InItem(mangsong, money);


    mciSendString("play sound//gamemusic.mp3", 0, 0, 0);
    while (1)
    {

        if (thetime % tgsinh == 0 && (thetime < TIMEEND - 5000))
           SinhXe(bando, xe, &nxe, thetime, level, &tgsinh);

           //printf("the time %d, TIME %d\n", thetime, TIMEEND);


        InXe(xe, nxe);
        InThap(thap, nthap);
        BanDan(thap, nthap, xe, nxe, dan, &ndan, thetime);
        DanDiChuyen(dan, ndan);
        InDan(dan, ndan);
        TrungDan(bando, xe, nxe, dan, &ndan);

        if (nxe < 20)
            delay(5);

        thetime += 5;

        change = XuLiChuot(&mouse, bando, &money, thap, &nthap);
        XoaXeCu(xe, nxe, thetime);
        KiemTraDan(bando, dan, &ndan);
        XDLaiDich(dan, ndan, xe, nxe);
        XeDiChuyen(bando, xe, nxe, thetime);

        if (ThatThu(xe, &nxe, bando, &mangsong) || KiemTraXe(xe, &nxe, &money) || change)
            {
                if (change == 2)
                    InMap(bando);

                InItem(mangsong, money);
                change = 0;
            }
        LamSachDan(bando, dan, ndan);

        if (thetime % 145 == 0)
            InProcess(process, "Process");

        if (thetime % 5000 == 0)
            InMap(bando);

        if (GetAsyncKeyState(27) || XetThuaGame(mangsong, thetime, nxe))
            {
                mciSendString("stop sound//gamemusic.mp3", 0, 0, 0);
                goto start_my_game;
            }
        //Ấn space để tạm dừng và Enter tiếp tục
        if (GetAsyncKeyState(32))
            while(!GetAsyncKeyState(13));

        if (kbhit())
            getch();
    }

    closegraph( );

    return 0;
}
