#define SNAKE_GAME_TEST
#include "main.cpp"

#include <cassert>
#include <iostream>

int main()
{
    CONRAN r;

    assert(r.DoDai == 3);
    assert(r.A[0].x == 12 && r.A[0].y == 10);
    assert(r.A[1].x == 11 && r.A[1].y == 10);
    assert(r.A[2].x == 10 && r.A[2].y == 10);
    assert(!r.ChamKhung());

    r.DiChuyen(0);
    assert(r.A[0].x == 13 && r.A[0].y == 10);
    assert(r.A[1].x == 12 && r.A[1].y == 10);
    assert(r.A[2].x == 11 && r.A[2].y == 10);
    assert(!r.ChamKhung());

    r = CONRAN();
    r.A[0].x = 1;
    r.DiChuyen(2);
    assert(r.ChamKhung());

    r = CONRAN();
    r.A[0].x = RONG - 2;
    r.DiChuyen(0);
    assert(r.ChamKhung());

    r = CONRAN();
    r.A[0].y = 1;
    r.DiChuyen(3);
    assert(r.ChamKhung());

    r = CONRAN();
    r.A[0].y = CAO - 2;
    r.DiChuyen(1);
    assert(r.ChamKhung());

    r = CONRAN();
    int oldLength = r.DoDai;
    Point oldTail = r.A[oldLength - 1];
    r.An();
    assert(r.DoDai == oldLength + 1);
    assert(r.A[oldLength].x == oldTail.x && r.A[oldLength].y == oldTail.y);

    MOI m;
    srand(1);
    for (int i = 0; i < 100; i++)
    {
        m.TaoMoi(r);
        assert(m.ViTri.x > 0 && m.ViTri.x < RONG - 1);
        assert(m.ViTri.y > 0 && m.ViTri.y < CAO - 1);
        assert(!r.ChuaO(m.ViTri.x, m.ViTri.y));
    }

    std::cout << "All snake game tests passed.\n";
    return 0;
}
