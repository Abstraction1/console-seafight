#include <iostream>
#include <ctime>

void drow(int (*m)[10], int x);

void mkships(int (*m)[10], int& deck_count, int& ship_count,
bool (*up)(int (*m)[10], int& cx, int& cy, int& deck_count, bool& hv),
bool (*left)(int (*m)[10], int& cx, int& cy, int& deck_count, bool& hv),
bool (*right)(int (*m)[10], int& cx, int& cy, int& deck_count, bool& hv));

bool checkUpAndDown(int (*m)[10], int& cx, int& cy, int& deck_count, bool& hv);
bool checkLeft(int (*m)[10], int& cx, int& cy, int& deck_count, bool& hv);
bool checkRight(int (*m)[10], int& cx, int& cy, int& deck_count, bool& hv);

int main()
{
    srand(time(NULL));

    int one_deck = 1;
    int two_deck = 2;
    int three_deck = 3;
    int four_deck = 4;

    int one_count = 4;
    int two_count = 3;
    int three_count = 2;
    int four_count = 1;

    const int x = 10;
    const int y = 10;

    bool (*ptr_checkUpAndDown)(int (*m)[10], int& cx, int& cy, int& deck_count, bool& hv) = checkUpAndDown;
    bool (*ptr_checkLeft)(int (*m)[10], int& cx, int& cy, int& deck_count, bool& hv) = checkLeft;
    bool (*ptr_checkRight)(int (*m)[10], int& cx, int& cy, int& deck_count, bool& hv) = checkRight;

    int field[x][y] = {0};

    mkships(field, four_deck, four_count, ptr_checkUpAndDown, ptr_checkLeft, ptr_checkRight);
    mkships(field, three_deck, three_count, ptr_checkUpAndDown, ptr_checkLeft, ptr_checkRight);
    mkships(field, two_deck, two_count, ptr_checkUpAndDown, ptr_checkLeft, ptr_checkRight);
    mkships(field, one_deck, one_count, ptr_checkUpAndDown, ptr_checkLeft, ptr_checkRight);

    drow(field, x);

    return 0;
}

void drow(int (*m)[10], int x)
{
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (m[j][i] == 0)
            {
                std::cout << '_';
            }
            else if (m[j][i] == 1)
            {
                std::cout << '1';
            }
            else if (m[j][i] == 2)
            {
                std::cout << '2';
            }
            else if (m[j][i] == 3)
            {
                std::cout << '3';
            }
            else if (m[j][i] == 4)
            {
                std::cout << '4';
            }
        } std::cout << std::endl;
    }
}

void mkships(int (*m)[10], int& deck_count, int& ship_count,
bool (*up)(int (*m)[10], int& cx, int& cy, int& deck_count, bool& hv),
bool (*left)(int (*m)[10], int& cx, int& cy, int& deck_count, bool& hv),
bool (*right)(int (*m)[10], int& cx, int& cy, int& deck_count, bool& hv))
{
    int cx = 5;
    int cy = 5;
    bool hOrV = true;
    for (int i = 0; i < ship_count; ++i)
    {
        hOrV = rand()%2;
        if(hOrV == true)
        {
            cx = rand() % 10;
            cy = rand() % 10;
            if (
                    up(m, cx, cy, deck_count, hOrV) ||
                    left(m, cx, cy, deck_count, hOrV) ||
                    right(m, cx, cy, deck_count, hOrV)
                    )
            {
                i--;
            }
            else
            {
                for (int i = 0; i < deck_count; ++i)
                {
                    m[cx][cy + i] = deck_count;
                }
            }
        }
        else if (hOrV == false)
        {
            cx = rand() % 10;
            cy = rand() % 10;
            if (
                    up(m, cx, cy, deck_count, hOrV) ||
                    left(m, cx, cy, deck_count, hOrV) ||
                    right(m, cx, cy, deck_count, hOrV)
                    )
            {
                i--;
            }
            else
            {
                for (int i = 0; i < deck_count; ++i)
                {
                    m[cx + i][cy] = deck_count;
                }
            }
        }
    }
}

bool checkUpAndDown(int (*m)[10], int& cx, int& cy, int& deck_count, bool& hv)
{
    bool result = true;
    if (hv == true)
    {
        for (int i = 1; i <= deck_count; ++i)
        {
            result =
                    m[cx][cy - 1] ||
                    m[cx]    [cy] ||
                    m[cx][cy + i] ||
                    cy > 10 - deck_count;
        }
    }
    else if (hv == false)
    {
        for (int i = 1; i <= deck_count; ++i)
        {
            result =
                    m[cx - 1][cy] ||
                    m[cx]    [cy] ||
                    m[cx + i][cy] ||
                    cx > 10 - deck_count;
        }
    } return result;
}

bool checkLeft(int (*m)[10], int &cx, int &cy, int& deck_count, bool& hv)
{
    bool result = true;
    if (hv == true)
    {
        for (int i = 1; i <= deck_count; ++i)
        {
            result =
                    m[cx - 1][cy - 1] ||
                    m[cx - 1]    [cy] ||
                    m[cx - 1][cy + i];
        }
    }
    else if (hv == false)
    {
        for (int i = 1; i <= deck_count; ++i)
        {
            result =
                    m[cx - 1][cy - 1] ||
                    m[cx]    [cy - 1] ||
                    m[cx + i][cy - 1];
        }
    } return result;
}

bool checkRight(int (*m)[10], int &cx, int &cy, int& deck_count, bool& hv)
{
    bool result = true;
    if (hv == true)
    {
        for (int i = 1; i <= deck_count; ++i)
        {
            result =
                    m[cx + 1][cy - 1] ||
                    m[cx + 1]    [cy] ||
                    m[cx + 1][cy + i];
        }
    }
    else if (hv == false)
    {
        for (int i = 1; i <= deck_count; ++i)
        {
            result =
                    m[cx - 1][cy + 1] ||
                    m[cx]    [cy + 1] ||
                    m[cx + i][cy + 1];
        }
    } return result;
}
