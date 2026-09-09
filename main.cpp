#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;
void gotoxy(int column, int line);

const int RONG = 40;
const int CAO = 20;

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
        A[0].x = 10;
        A[0].y = 10;
        A[1].x = 11;
        A[1].y = 10;
        A[2].x = 12;
        A[2].y = 10;
    }
    void Ve()
    {
        for (int i = 0; i < DoDai; i++)
        {
            gotoxy(A[i].x, A[i].y);
            cout << "X";
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
    // Sinh moi tai vi tri ngau nhien, khong trung than ran
    void TaoMoi(CONRAN& r)
    {
        do
        {
            ViTri.x = rand() % RONG;
            ViTri.y = rand() % CAO;
        } while (r.ChuaO(ViTri.x, ViTri.y));
    }
    void Ve()
    {
        gotoxy(ViTri.x, ViTri.y);
        cout << "O";
    }
};

int main()
{
    srand((unsigned)time(NULL));
    CONRAN r;
    MOI m;
    m.TaoMoi(r);
    int Huong = 0;
    char t;

    while (1)
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
        r.DiChuyen(Huong);
        if (r.A[0].x == m.ViTri.x && r.A[0].y == m.ViTri.y)
        {
            r.An();
            m.TaoMoi(r);
        }
        system("cls");
        r.Ve();
        m.Ve();
        Sleep(300);
    }

    return 0;
}

void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}