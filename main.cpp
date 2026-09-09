#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <string>
using namespace std;
void gotoxy(int column, int line);

const int RONG = 40;
const int CAO = 20;
const int CHIEU_RONG_KY_TU = 1;
const int THOI_GIAN_NGANG = 100;
const int THOI_GIAN_DOC = 150;

struct Point
{
    int x, y;
};
class CONRAN
{
   public:
    struct Point A[100];
    int DoDai;
    CONRAN()
    {
        DoDai = 3;
        A[0].x = 12;
        A[0].y = 10;
        A[1].x = 11;
        A[1].y = 10;
        A[2].x = 10;
        A[2].y = 10;
    }
    void Ve()
    {
        for (int i = 0; i < DoDai; i++)
        {
            gotoxy(A[i].x * CHIEU_RONG_KY_TU, A[i].y);
            cout << 'X';
        }
    }
    void DiChuyen(int Huong)
    {
        for (int i = DoDai - 1; i > 0; i--)
            A[i] = A[i - 1];
        if (Huong == 0)
            A[0].x = A[0].x + 1;
        if (Huong == 1)
            A[0].y = A[0].y + 1;
        if (Huong == 2)
            A[0].x = A[0].x - 1;
        if (Huong == 3)
            A[0].y = A[0].y - 1;
    }
    bool ChuaO(int x, int y)
    {
        for (int i = 0; i < DoDai; i++)
            if (A[i].x == x && A[i].y == y)
                return true;
        return false;
    }
    bool ChamKhung() const
    {
        return A[0].x <= 0 || A[0].x >= RONG - 1 || A[0].y <= 0 || A[0].y >= CAO - 1;
    }
    void An()
    {
        if (DoDai < 100)
        {
            A[DoDai] = A[DoDai - 1];
            DoDai++;
        }
    }
};

class MOI
{
   public:
    Point ViTri;
    void TaoMoi(CONRAN& r)
    {
        do
        {
            ViTri.x = 1 + rand() % (RONG - 2);
            ViTri.y = 1 + rand() % (CAO - 2);
        } while (r.ChuaO(ViTri.x, ViTri.y));
    }
    void Ve()
    {
        gotoxy(ViTri.x * CHIEU_RONG_KY_TU, ViTri.y);
        cout << 'O';
    }
};

void VeKhung()
{
    for (int x = 0; x < RONG; x++)
    {
        gotoxy(x * CHIEU_RONG_KY_TU, 0);
        cout << '#';
        gotoxy(x * CHIEU_RONG_KY_TU, CAO - 1);
        cout << '#';
    }
    for (int y = 1; y < CAO - 1; y++)
    {
        gotoxy(0, y);
        cout << '#';
        gotoxy((RONG - 1) * CHIEU_RONG_KY_TU, y);
        cout << '#';
    }
}

void XoaDiem(Point viTri)
{
    gotoxy(viTri.x * CHIEU_RONG_KY_TU, viTri.y);
    cout << ' ';
}

void XoaVungChoi()
{
    string dongTrong((RONG - 2) * CHIEU_RONG_KY_TU, ' ');
    for (int y = 1; y < CAO - 1; y++)
    {
        gotoxy(CHIEU_RONG_KY_TU, y);
        cout << dongTrong;
    }
}

void DatConTro(bool hienThi)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    if (GetConsoleCursorInfo(console, &cursorInfo))
    {
        cursorInfo.bVisible = hienThi;
        SetConsoleCursorInfo(console, &cursorInfo);
    }
}

#ifndef SNAKE_GAME_TEST
int main()
{
    srand((unsigned)time(NULL));
    DatConTro(false);
    char t;

    while (1)
    {
        CONRAN r;
        MOI m;
        m.TaoMoi(r);
        int Huong = 0;
        bool GameOver = false;

        XoaVungChoi();
        VeKhung();
        r.Ve();
        m.Ve();
        cout.flush();

        while (!GameOver)
        {
            if (kbhit())
            {
                t = getch();
                if (t == 'a')
                    Huong = 2;
                if (t == 'w')
                    Huong = 3;
                if (t == 'd')
                    Huong = 0;
                if (t == 's')
                    Huong = 1;
            }
            Point duoiCu = r.A[r.DoDai - 1];
            r.DiChuyen(Huong);
            if (r.ChamKhung())
            {
                GameOver = true;
                continue;
            }
            if (r.A[0].x == m.ViTri.x && r.A[0].y == m.ViTri.y)
            {
                r.An();
                m.TaoMoi(r);
            }
            XoaDiem(duoiCu);
            r.Ve();
            m.Ve();
            cout.flush();
            Sleep(Huong == 0 || Huong == 2 ? THOI_GIAN_NGANG : THOI_GIAN_DOC);
        }

        XoaVungChoi();
        VeKhung();
        gotoxy(14, CAO / 2);
        cout << "GAME OVER";
        gotoxy(10, CAO / 2 + 2);
        cout << "[ENTER] PLAY AGAIN";
        gotoxy(10, CAO / 2 + 3);
        cout << "[ESC] EXIT";

        while (true)
        {
            t = getch();
            if (t == 13)
                break;
            if (t == 27)
            {
                DatConTro(true);
                return 0;
            }
        }
    }

    DatConTro(true);
    return 0;
}
#endif

void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
