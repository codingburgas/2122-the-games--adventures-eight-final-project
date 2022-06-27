#include <windows.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <stdio.h>

using namespace std;

bool game = true;

enum eDirection { STAY, LEFT, RIGHT, UP, DOWN, LE_shoot, RI_shoot, DO_shoot, UP_shoot, ST_shoot };
eDirection menu;

void Input()
{

    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            menu = LEFT;
            break;

        case 'd':
            menu = RIGHT;
            break;

        case 'w':
            menu = UP;
            break;

        case 's':
            menu = DOWN;
            break;

        case ' ':
            menu = STAY;
            break;

        case 'j':
            menu = LE_shoot;
            break;

        case 'l':
            menu = RI_shoot;
            break;

        case 'k':
            menu = DO_shoot;
            break;

        case 'i':
            menu = UP_shoot;
            break;
        }
    }
}

void Logic(int&, int&, int&, int&, int&, bool&, bool&);

int main()
{
    int wayOfShooting = 0;
    int Xshoot = 0;
    int Yshoot = 0;
    int XshootPos = 0;
    int YshootPos = 0;
    int YshootCor = 0;
    int XshootCor = 0;
    short int XgamePos = 100;
    short int YgamePos = 150;
    bool Xpermission = 0;
    bool Ypermission = 0;

    int NPCX = 600;
    int NPCY = 600;

    HWND myconsole = GetConsoleWindow();

    HDC mydc = GetDC(myconsole);

    COLORREF COLOR = RGB(184, 95, 44);

    int Xmove = 0;
    int Ymove = 0;

    int Xplayer = 1200;
    int Yplayer = 650;

    int XshotBase = 0;
    int YshotBase = 0;

    int BG[3] = { 54, 102, 53 };

    int Xmap = 50;
    int Ymap = 50;

    int map[100][100];

    bool mapPerm = 0;

    Sleep(1000);

    while (game == true)
    {
        srand(time(0));
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                map[i][j] = rand() % 3;
            }
        }
        COLOR = RGB(BG[0], BG[1], BG[2]);
        for (double i = YgamePos; i < YgamePos + 700; i = i + 1)
        {
            for (double j = XgamePos + 400; j < XgamePos + 1700; j = j + 1)
            {
                SetPixel(mydc, j, i, COLOR);
                SetPixel(mydc, j, i, COLOR);
            }
        }

        COLOR = RGB(255, 255, 255);
        for (int i = Yplayer; i < Yplayer + 800; i++)
        {
            for (int j = Xplayer; j < Xplayer + 1800; j++)
            {
                if (i > Yplayer and i < Yplayer + 50 and j > Xplayer and j < Xplayer + 50)
                {
                    SetPixel(mydc, j, i, COLOR);
                }
            }
        }

        while (game == true)
        {
            Input();
            Logic(Xmove, Ymove, Xshoot, Yshoot, wayOfShooting, Xpermission, Ypermission);


            if (map[Xmap][Ymap] == 1)
            {
                if (mapPerm == 1)
                {
                    COLOR = RGB(145, 145, 135);
                    for (int i = 0; i < 50; i++)
                    {
                        for (int j = 0; j < 50; j++)
                        {
                            SetPixel(mydc, i + NPCX, j + NPCY, COLOR);
                        }
                    }
                    mapPerm = 0;
                }
                if (rand() % 2 == 0)
                {
                    if (Xplayer > NPCX)
                    {
                        NPCX++;
                    }
                    else
                    {
                        NPCX--;
                    }
                }
                else
                {
                    if (Yplayer > NPCY)
                    {
                        NPCY++;
                    }
                    else
                    {
                        NPCY--;
                    }
                }
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = NPCY; i < NPCY + 50; i++)
                {
                    SetPixel(mydc, NPCX, i, COLOR);
                    SetPixel(mydc, NPCX + 50, i, COLOR);
                }
                COLOR = RGB(145, 145, 135);
                for (int i = NPCY; i < NPCY + 50; i++)
                {
                    SetPixel(mydc, NPCX + 1, i, COLOR);
                    SetPixel(mydc, NPCX + 49, i, COLOR);
                }

                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = NPCX; i < NPCX + 50; i++)
                {
                    SetPixel(mydc, i, NPCY, COLOR);
                    SetPixel(mydc, i, NPCY + 50, COLOR);
                }
                COLOR = RGB(145, 145, 135);
                for (int i = NPCX + 1; i < NPCX + 50; i++)
                {
                    SetPixel(mydc, i, NPCY + 1, COLOR);
                    SetPixel(mydc, i, NPCY + 49, COLOR);
                }
                if (XshootPos >= NPCX and XshootPos <= NPCX + 50 and YshootPos >= NPCY and YshootPos <= NPCY + 50)
                {
                    map[Xmap][Ymap] = 0;
                    COLOR = RGB(BG[0], BG[1], BG[2]);
                    for (int i = NPCX; i < NPCX + 50; i++)
                    {
                        for (int j = NPCY; j < NPCY + 50; j++)
                        {
                            SetPixel(mydc, i, j, COLOR);
                        }
                    }
                }
            }


            if (wayOfShooting == 1)
            {
                COLOR = RGB(255, 0, 0);
                for (int i = XshootPos + 12; i < XshootPos + 25; i++)
                {
                    for (int j = YshootPos; j > YshootPos - 13; j--)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = XshootPos + 12; i < XshootPos + 25; i++)
                {
                    SetPixel(mydc, i, YshootPos - 24, COLOR);
                    SetPixel(mydc, i, YshootPos, COLOR);
                }
            }
            if (wayOfShooting == 3)
            {
                COLOR = RGB(255, 0, 0);
                for (int i = XshootPos + 13; i < XshootPos + 25; i++)
                {
                    for (int j = YshootPos + 50; j < YshootPos + 75; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = XshootPos + 13; i < XshootPos + 25; i++)
                {
                    SetPixel(mydc, i, YshootPos + 50, COLOR);
                    SetPixel(mydc, i, YshootPos + 75, COLOR);
                }
            }
            if (wayOfShooting == 2)
            {
                COLOR = RGB(255, 0, 0);
                for (int i = XshootPos + 12 + 50; i < XshootPos + 25 + 50; i++)
                {
                    for (int j = YshootPos + 13; j < YshootPos + 25; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = YshootPos + 13; i < YshootPos + 25; i++)
                {
                    SetPixel(mydc, XshootPos + 12 + 50, i, COLOR);
                    SetPixel(mydc, XshootPos + 50, i, COLOR);
                }
            }
            if (wayOfShooting == 4)
            {
                COLOR = RGB(255, 0, 0);
                for (int i = XshootPos; i > XshootPos - 25; i--)
                {
                    for (int j = YshootPos + 13; j < YshootPos + 25; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = YshootPos + 13; i < YshootPos + 25; i++)
                {
                    SetPixel(mydc, XshootPos, i, COLOR);
                    SetPixel(mydc, XshootPos - 25, i, COLOR);
                }
            }


            if (YshootPos < YgamePos + 25 and wayOfShooting != 0)
            {
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = XshootPos + 12; i < XshootPos + 25; i++)
                {
                    for (int j = YshootPos; j > YshootPos - 13; j--)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
                menu = ST_shoot;
            }
            if (YshootPos > YgamePos + 625 and wayOfShooting != 0)
            {
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = XshootPos + 13; i < XshootPos + 25; i++)
                {
                    for (int j = YshootPos + 50; j < YshootPos + 75; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
                menu = ST_shoot;
            }
            if (XshootPos > XgamePos + 1625 and wayOfShooting != 0)
            {
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = XshootPos + 12 + 50; i < XshootPos + 25 + 50; i++)
                {
                    for (int j = YshootPos + 13; j < YshootPos + 25; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
                menu = ST_shoot;
            }
            if (XshootPos < XgamePos + 450 and wayOfShooting != 0)
            {
                for (int i = XshootPos; i > XshootPos - 25; i--)
                {
                    for (int j = YshootPos + 13; j < YshootPos + 25; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
                menu = ST_shoot;
            }
            if (wayOfShooting == 0)
            {
                COLOR = RGB(BG[0], BG[1], BG[2]);
                XshootPos = Xplayer;
                YshootPos = Yplayer;
                YshotBase = 0;
                XshotBase = 0;
                menu = ST_shoot;
                XshootPos = Xplayer;
                YshootCor = Yplayer;
                XshootCor = Xplayer;
            }

            Xplayer = Xplayer + Xmove;
            Yplayer = Yplayer + Ymove;

            if (Xpermission == 0)
            {
                XshotBase = Xshoot + XshotBase;
                XshootPos = XshootCor + XshotBase;
            }
            if (Ypermission == 0)
            {
                YshotBase = Yshoot + YshotBase;
                YshootPos = YshootCor + YshotBase;
            }
            COLOR = RGB(BG[0], BG[1], BG[2]);
            for (int i = Yplayer; i < Yplayer + 50; i++)
            {
                SetPixel(mydc, Xplayer, i, COLOR);
                SetPixel(mydc, Xplayer + 50, i, COLOR);
            }
            COLOR = RGB(255, 255, 255);
            for (int i = Yplayer; i < Yplayer + 50; i++)
            {
                SetPixel(mydc, Xplayer + 1, i, COLOR);
                SetPixel(mydc, Xplayer + 49, i, COLOR);
            }

            COLOR = RGB(BG[0], BG[1], BG[2]);
            for (int i = Xplayer; i < Xplayer + 50; i++)
            {
                SetPixel(mydc, i, Yplayer, COLOR);
                SetPixel(mydc, i, Yplayer + 50, COLOR);
            }
            COLOR = RGB(255, 255, 255);
            for (int i = Xplayer + 1; i < Xplayer + 50; i++)
            {
                SetPixel(mydc, i, Yplayer + 1, COLOR);
                SetPixel(mydc, i, Yplayer + 49, COLOR);
            }

            if (Xplayer < XgamePos + 400)
            {
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = Xplayer; i <= Xplayer + 50; i++)
                {
                    for (int j = Yplayer; j < Yplayer + 50; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
                Xplayer = Xplayer + 1250;
                Xmap--;
                mapPerm = 1;
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = NPCX; i < NPCX + 50; i++)
                {
                    for (int j = NPCY; j < NPCY + 50; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
            }
            if (Xplayer > XgamePos + 1650)
            {
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = Xplayer; i <= 50 + Xplayer; i++)
                {
                    for (int j = Yplayer; j < Yplayer + 50; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }

                Xplayer = Xplayer - 1250;
                Xmap++;
                mapPerm = 1;
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = NPCX; i < NPCX + 50; i++)
                {
                    for (int j = NPCY; j < NPCY + 50; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
            }
            if (Yplayer > YgamePos + 650)
            {
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = Xplayer; i <= 50 + Xplayer; i++)
                {
                    for (int j = Yplayer; j < Yplayer + 50; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
                Yplayer = Yplayer - 650;
                Ymap++;
                mapPerm = 1;
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = NPCX; i < NPCX + 50; i++)
                {
                    for (int j = NPCY; j < NPCY + 50; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
            }
            if (Yplayer < YgamePos)
            {
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = Xplayer; i <= 50 + Xplayer; i++)
                {
                    for (int j = Yplayer; j < Yplayer + 50; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
                Yplayer = Yplayer + 650;
                Ymap--;
                mapPerm = 1;
                COLOR = RGB(BG[0], BG[1], BG[2]);
                for (int i = NPCX; i < NPCX + 50; i++)
                {
                    for (int j = NPCY; j < NPCY + 50; j++)
                    {
                        SetPixel(mydc, i, j, COLOR);
                    }
                }
            }

        }
    }
}

void Logic(int& Xmove, int& Ymove, int& Xshoot, int& Yshoot, int& wayOfShooting, bool& Xpermission, bool& Ypermission)
{
    switch (menu)
    {
    case LEFT:

        Xmove = -1;
        Ymove = 0;
        break;
    case RIGHT:
        Xmove = 1;
        Ymove = 0;
        break;
    case UP:
        Xmove = 0;
        Ymove = -1;
        break;
    case DOWN:
        Xmove = 0;
        Ymove = 1;
        break;
    case STAY:
        Xmove = 0;
        Ymove = 0;
        break;
    case LE_shoot:
        if (wayOfShooting == 0)
        {
            Xshoot = -1;
            Yshoot = 0;
            wayOfShooting = 4;
            Xpermission = 0;
            Ypermission = 1;
        }
        break;
    case RI_shoot:
        if (wayOfShooting == 0)
        {
            Xshoot = 1;
            Yshoot = 0;
            wayOfShooting = 2;
            Xpermission = 0;
            Ypermission = 1;
        }
        break;
    case DO_shoot:
        if (wayOfShooting == 0)
        {
            Xshoot = 0;
            Yshoot = 1;
            wayOfShooting = 3;
            Xpermission = 1;
            Ypermission = 0;
        }
        break;

    case UP_shoot:
        if (wayOfShooting == 0)
        {
            Xshoot = 0;
            Yshoot = -1;
            wayOfShooting = 1;
            Xpermission = 1;
            Ypermission = 0;
        }
        break;

    case ST_shoot:
        Xshoot = 0;
        Yshoot = 0;
        wayOfShooting = 0;
        Xpermission = 1;
        Ypermission = 1;
        break;
    }
}