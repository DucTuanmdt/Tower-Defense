
#ifndef HIENTHI_H
#define HIENTHI_H


void InHelp();
void InLuaChon(int *pvt, char s[][N], int n);
void InSetting(int *pbando, int *pdokho);
int InMenu(int *pbando, int *pdokho);

void InXe(Xe xe[N], int n);
void InThap(Thap thap[], int n);
void XoaDanCu(int bando[][COL], ToaDo vt);
void InDan(Dan dan[N], int n);
void InMotO(int i, int j, int mau, int dang);
void InMap(int bando[][COL]);
void XoaXeCu(Xe xe[], int n, int thetime);
void LamSachDan(int bando[][COL], Dan dan[], int n);
void InVien();
void InItem(int mangsong, int money);
void InProcess(ToaDo process[], char s[]);
void InChienThang();
void InThua();
void InLoading();


#endif // HIENTHI_H
