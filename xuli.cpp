#include "hangso.h"
#include "xuli.h"
#include "hienthi.h"


float KhoangCach(ToaDo a, ToaDo b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

ToaDo NextDan(ToaDo vt, ToaDo dich)
{
    int x, y;
    ToaDo temp = vt;
    float dmax = 1000000;
    int i, j;

    for (i = -3; i < 3; i++)
        for (j = -3; j < 3; j++)
            {
                temp.x += i;
                temp.y += j;

                if (dmax > KhoangCach(temp, dich))
                {
                    dmax = KhoangCach(temp, dich);
                    x = i;
                    y = j;
                }

                temp = vt;
            }
    vt.x += x;
    vt.y += y;

    return vt;
}

void KhoiTaoXe(Xe xe[], int *pn, int loai, int level)
{
    xe[*pn].loai = loai;
    xe[*pn].mang = MANG[loai] + 3 * (level + 1);
    xe[*pn].tocdo = TOCDO[loai] - 15 * level;
    xe[*pn].isstop = 0;
    xe[*pn].thuong = THUONG[loai];
    xe[*pn].huong = RIGHT;
    xe[*pn].vt = {20, 20};

    (*pn)++;
}

void KhoiTaoThap(Thap thap[], int *pn, int loai, ToaDo vt, int bando[][COL])
{
    mciSendString("play sound//loadgun.wav", 0, 0, 0);
    thap[*pn].loai = loai;
    thap[*pn].giaca = GIACA[loai];
    thap[*pn].tgban = TGBAN[loai];
    thap[*pn].vt = vt;
    thap[*pn].culi = CULI[loai];
    bando[vt.y / (CANH * 3)][vt.x / (CANH * 3)] = 3;

    (*pn)++;
}

void KhoiTaoDan(Dan dan[], int *pn, int loai, ToaDo vt, ToaDo dich)
{
    dan[*pn].loai = loai;
    dan[*pn].tocdo = TOCDO[loai];
    dan[*pn].tgsong = CULI[loai] ;
    dan[*pn].vt = dan[*pn].vtcu = dan[*pn].vtthap = vt;
    dan[*pn].dich = dich;

    (*pn)++;
}

int DocFile(char fname[], int bando[][COL])
{
    FILE *fin = fopen(fname, "rt");
    if (!fin)
    {
        settextstyle(1, 1, 3);
        outtextxy(200, 200, "Khong mo duoc file");

        getch();
        return 0;
    }

    int i, j;

    for (i = 0; i < ROW; i++)
        for (j = 0; j < COL; j++)
            fscanf(fin, "%d ", &bando[i][j]);

    fclose(fin);

    return 1;
}

void BanDan(Thap thap[], int nthap, Xe xe[], int nxe, Dan dan[], int *pndan, int thetime)
{
    int i, j;

    for (i = 0; i < nthap; i++)
        if (thetime % thap[i].tgban == 0)
        {

            for (j = 0; j < nxe; j++)
            {
                if (KhoangCach(thap[i].vt, xe[j].vt) <= thap[i].culi)
                {
                    PlaySound(TEXT("sound//shoot2.wav"), NULL, SND_ASYNC);
                    KhoiTaoDan(dan, pndan,thap[i].loai, thap[i].vt, xe[j].vt);
                    break;//Một tháp mỗi lần chỉ được bắn 1 xe
                }
            }
        }

}

void XoaDan(Dan dan[], int *pn, int vt)
{
    int i;

    for (i = vt; i < *pn - 1; i++)
        dan[i] = dan[i + 1];

    (*pn)--;
}

void XoaXe(Xe xe[], int *pn, int vt)
{
    int i;

    for (i = vt; i < *pn - 1; i++)
        xe[i] = xe[i + 1];

    (*pn)--;
}

//Xử lí xe bị trúng đạn
void TrungDan(int bando[][COL], Xe xe[], int nxe, Dan dan[], int *pndan)
{
    int i, j;

    for (i = 0; i < *pndan; i++)
        if (KhoangCach(dan[i].vt, dan[i].dich) <= CANH)
        {
            for (j = 0; j < nxe; j++)
                if (KhoangCach(xe[j].vt,dan[i].dich) < 0.1)// == 0 sợ bị sai số
                {
                    switch (dan[i].loai)
                    {
                        case 2: xe[j].isstop = TIMESTOP;
                        break;

                        default: xe[j].mang -= (dan[i].loai + 1);
                        break;
                    }

                    XoaDanCu(bando, dan[i].vt);
                    XoaDan(dan, pndan, i);

                    break;
                }
        }
}

//Kiểm tra xe nào hết mạng thì xóa và cộng tiền thưởng
int KiemTraXe(Xe xe[], int *pn, int *pmoney)
{
    int i;
    int x, y;
    int flag = 0;

    for (i = 0; i < *pn; i++)
        if (xe[i].mang <= 0)
        {
            //PlaySound(TEXT("sound//coins.wav"), 0, SND_ASYNC);
            mciSendString("play sound//coins.wav", 0, 0, 0);

            x = xe[i].vt.x - CANH * 3 / 2;
            y = xe[i].vt.y - CANH * 3 / 2;

            setfillstyle(0, 0);
            bar(x, y, x + CANH * 3, y + CANH * 3);//Xóa xe trên màn hình

            (*pmoney) += xe[i].thuong;
            XoaXe(xe, pn, i);
            flag = 1;
        }

    return flag;
}

//Kiểm tra đạn nào quá cự li bắn thì xóa
void KiemTraDan(int bando[][COL], Dan dan[], int *pn)
{
    int i;

    for (i = 0; i < *pn; i++)
        if (KhoangCach(dan[i].vt, dan[i].vtthap) > CULI[dan[i].loai] || dan[i].tgsong < 0)
        {
            XoaDanCu(bando, dan[i].vt);
            XoaDan(dan, pn, i);
        }
}

//Tìm tọa độ tiếp theo của đạn
void DanDiChuyen(Dan dan[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        dan[i].vt = NextDan(dan[i].vt, dan[i].dich);
        dan[i].tgsong -= 3;
    }

}

void XuLiHuong(Xe *pxe, int bando[][COL])
{
    Xe xe = *pxe;
    HuongDi huongcu = RIGHT;
    int x, y;
    int dodai = CANH * 4 + CANH / 2 + 2;

    batdauXLhuong:

    x = xe.vt.x;
    y = xe.vt.y;

    switch (xe.huong)
    {
        case UP: y -= dodai;
        break;

        case DOWN: y += dodai;
        break;

        case RIGHT: x += dodai;
        break;
    }

    x /= (CANH * 3);
    y /= (CANH * 3);

    if (bando[y][x] != 1 && bando[y][x] != 3)
    {
        *pxe = xe;
        return;
    }

    switch (xe.huong)
    {
        case UP: xe.huong = RIGHT;
        break;

        case RIGHT:
                    if (huongcu == UP)
                        xe.huong = DOWN;
                    else
                    huongcu = xe.huong = UP;

        break;

        case DOWN: xe.huong = RIGHT;
        break;
    }

    goto batdauXLhuong;
}

void XeDiChuyen(int bando[][COL], Xe xe[], int n, int thetime)
{
    int xoay = 0;
    int i, j;

    for (i = 0; i < n; i++)
        if (xe[i].isstop <= 0 && thetime % xe[i].tocdo == 0)
        {
            XuLiHuong(&xe[i], bando);
            xe[i].huong == RIGHT ? xe[i].vt.x += CANH : xe[i].vt.y += CANH * XLdau(xe[i].huong);
        }
        else
            xe[i].isstop -= 5;
}

//Thất thủ khỉ xe địch vào được thành
int ThatThu(Xe xe[], int *pn, int bando[][COL], int *pmangsong)
{
    int i;
    int x, y;
    int flag = 0;

    for (i = 0; i < *pn; i++)
        {
            x = xe[i].vt.x / (CANH * 3);
            y = xe[i].vt.y / (CANH * 3);

            if (bando[y][x] == 2)
            {
                mciSendString(" stop sound//warning.wav",0, 0, 0);
                mciSendString(" play sound//warning.wav",0, 0, 0);
                (*pmangsong)--;
                XoaXeCu(xe, *pn, xe[i].tocdo);
                InMotO(x, y, MAUMAP[bando[y][x]], 1);
                XoaXe(xe, pn, i);
                flag = 1;
            }
        }

        return flag;
}

//Xác định lại mục tiêu cho đạn
void XDLaiDich(Dan dan[], int ndan, Xe xe[], int nxe)
{
    int i, j;

    for (i = 0; i < ndan; i++)
            for (j = 0; j < nxe; j++)
            {
                if (KhoangCach(dan[i].vt, xe[j].vt) + KhoangCach(dan[i].vt, dan[i].vtthap) < CULI[dan[i].loai])
                {
                    dan[i].dich = xe[j].vt;
                    break;
                }
            }
}

//isclick = 1: mua tháp, = 2: bán tháp
int XuLiChuot(Mouse *pmouse,int bando[][COL], int *pmoney, Thap thap[], int *pn)
{
    Mouse mouse = *pmouse;
    int x, y, mau;
    int flag = 0;

    if (ismouseclick(WM_LBUTTONDBLCLK))
        {
            getmouseclick(WM_LBUTTONDBLCLK, mouse.vt.x, mouse.vt.y);

            if (mouse.vt.x > 1107 && mouse.vt.x < WIDTH && mouse.vt.y > 162 && mouse.vt.y < 485)
            {
                if (mouse.vt.y < 404)
                {
                    mouse.giaca = GIACA[mouse.vt.y / 81 - 2];
                    mouse.loaithap = mouse.vt.y / 81 - 2;
                    mouse.isclick = 1;
                }
                else
                    mouse.isclick = 2;
            }
            else
                mouse.isclick = 0;
        }

    if (ismouseclick(WM_MOUSEMOVE) && mouse.isclick)
    {
        getmouseclick(WM_MOUSEMOVE, mouse.vt.x, mouse.vt.y);

        if (mouse.vt.x < 1107 && mouse.vt.x > 0 && mouse.vt.y < 540 && mouse.vt.y)
        {
            //Xóa ô cũ
            x = mouse.vtcu.x / (CANH * 3);
            y = mouse.vtcu.y / (CANH * 3);
            mau = MAUMAP[bando[y][x]];
            InMotO(x, y , mau, 1);
            mouse.vtcu = mouse.vt;

            //In ô mới
            x = mouse.vt.x / (CANH * 3);
            y = mouse.vt.y / (CANH * 3);
            mau = bando[y][x] == 1 ? 10 : 13;
            InMotO(x, y , mau, 8);
        }
    }

    if (ismouseclick(WM_LBUTTONDOWN) && mouse.isclick)
    {
        getmouseclick(WM_LBUTTONDOWN, mouse.vt.x, mouse.vt.y);

        if (mouse.vt.x < 1107 && mouse.vt.y < 540)
        {
            //xóa ô cũ
            x = mouse.vtcu.x / (CANH * 3);
            y = mouse.vtcu.y / (CANH * 3);
            mau = MAUMAP[bando[y][x]];
            InMotO(x, y , mau, 1);
            mouse.vtcu = mouse.vt;

            x = mouse.vt.x / (CANH * 3);
            y = mouse.vt.y / (CANH * 3);
            mouse.vt.x = x * CANH * 3 + 13;
            mouse.vt.y = y * CANH * 3 + 13;

            if (bando[y][x] == 3 && mouse.isclick == 2)
            {
                int i;
                for (i = 0; i < *pn; i++)
                    if (mouse.vt.x == thap[i].vt.x && mouse.vt.y == thap[i].vt.y)
                        {
                            mciSendString("play sound//remove.mp3", 0, 0, 0);
                            (*pmoney) += GIACA[thap[i].loai] / 2;
                            XoaThap(thap, pn, i);
                        }
                bando[y][x] = 1;

            }
            else if (bando[y][x] == 1 && *pmoney >= mouse.giaca && mouse.isclick == 1)
                {
                    (*pmoney) -= mouse.giaca;
                    (*pmouse) = mouse;
                    KhoiTaoThap(thap, pn, mouse.loaithap, mouse.vt, bando);
                }

                flag = mouse.isclick;// = 2 thì in lại bản đồ + item, == 1 thì chỉ in item
                mouse.isclick = 0;
        }
    }
    (*pmouse) = mouse;

    return flag;
}

void SinhXe(int bando[][COL], Xe xe[], int *pn, int thetime, int level, int *ptgsinh)
{
    if (*pn > 98)
        return;

    int y;
    do
        y = rand() % (ROW - 2) + 1;
    while (bando[y][0]);

    int loai;
    for (loai = 3; loai > 0; loai--)
        if (thetime <= TIMEEND / loai)
            break;

    loai = loai == 3 ? 1 : loai == 2 ? 2 : 3;
    int temp = rand() % loai;

    KhoiTaoXe(xe, pn, temp, level);

    xe[(*pn) - 1].vt.y = y * CANH * 3 + 13;
    xe[(*pn) - 1].mang += (loai - 1) * 2;
    xe[(*pn) - 1].tocdo -= (loai - 1) *10;

    if (*ptgsinh > 500 - level * 25)
        (*ptgsinh) -= (level + 1) * 10;
}

void XoaThap(Thap thap[], int *pn, int vt)
{
    int i;

    for (i = vt; i < *pn - 1; i++)
        thap[i] = thap[i + 1];

    (*pn)--;
}

int XetThuaGame(int mangsong, int thetime, int nxe)
{
    setbkcolor(GREEN);
    setcolor(RED);

    if (mangsong <= 0)
    {
        InThua();
        return 1;//thua
    }

    if (thetime > TIMEEND && nxe <= 0)
    {
        InChienThang();
        return 2;//thắng
    }


    return 0;
}
