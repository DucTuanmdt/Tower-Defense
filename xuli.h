
#ifndef XULI_H
#define XULI_H

#define XLhuong(x,y,H) (H == RIGHT ? x : y)
#define XLconlai(x,y,H) (H == RIGHT ? y : x)
#define XLdau(H) (H == UP ? -1 : 1)

float KhoangCach(ToaDo a, ToaDo b);
ToaDo NextDan(ToaDo dan, ToaDo xe);
void KhoiTaoXe(Xe xe[], int *pn, int loai, int level);
void KhoiTaoThap(Thap thap[], int *pn, int loai, ToaDo vt, int bando[][COL]);
void KhoiTaoDan(Dan dan[], int *pn, int loai, ToaDo vt, ToaDo dich);
int DocFile(char fname[], int bando[][COL]);
void BanDan(Thap thap[], int nthap, Xe xe[], int nxe, Dan dan[], int *pndan, int thetime);
void XoaDan(Dan dan[], int *pn, int vt);
void XoaXe(Xe xe[], int *pn, int vt);
void TrungDan(int bando[][COL], Xe xe[], int nxe, Dan dan[], int *pndan);
int KiemTraXe(Xe xe[], int *pn, int *pmoney);
void KiemTraDan(int bando[][COL], Dan dan[], int *pn);
void DanDiChuyen(Dan dan[], int n);
void XuLiHuong(Xe *pxe, int bando[][COL]);
void XeDiChuyen(int bando[][COL], Xe xe[], int n, int thetime);
int ThatThu(Xe xe[], int *pn, int bando[][COL], int *pmangsong);
void XDLaiDich(Dan dan[], int ndan, Xe xe[], int nxe);
int XuLiChuot(Mouse *pmouse,int bando[][COL], int *pmoney, Thap thap[], int *pn);
void SinhXe(int bando[][COL], Xe xe[], int *pn, int thetime, int level, int *ptgsinh);
void XoaThap(Thap thap[], int *pn, int vt);
int XetThuaGame(int mangsong, int thetime, int nxe);

#endif // XULI_H
