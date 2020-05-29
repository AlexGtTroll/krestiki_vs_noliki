#include <cstdio>
#include <iostream>
#include <cstring>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

int a[3][3], t, y, game = 1;
char name[30], str[500];

void print()//Функция вывода сетки
{
    int i, j;
    cout << "\n";
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (a[i][j] == 0)
                cout << ".\t";
            else if (a[i][j] == 1)
                cout << "X\t";
            else
                cout << "O\t";
        }
        cout << endl;
    }
}

int check()//Проверка на чью-либо победу
{
    for (int i = 0; i < 3; i++)
        if ((a[i][0] != 0 && a[i][0] == a[i][1] && a[i][1] == a[i][2]) ||
            (a[0][i] != 0 && a[0][i] == a[1][i] && a[1][i] == a[2][i]))
            return 1;

    if (a[0][0] != 0 && a[0][0] == a[1][1] && a[1][1] == a[2][2])
        return 1;
    else if (a[0][2] != 0 && a[0][2] == a[1][1] && a[1][1] == a[2][0])
        return 1;
    else
        return 0;
}

void player_print()//Функция ввода данных от игрока
{
    int r = 0, c = 0;
    cout << "Введите строку и столбец: ";
    cin >> r >> c;
    r--;
    c--;
    if (r > 2 || c > 2 || r < 0 || c < 0)
    {
        strcpy_s(str, "Введите правильное значение ");
        strcat_s(str, name);
        strcat_s(str, ".\n");
        cout << str << endl;;
        player_print();
    }
    else if (a[r][c] != 0)
    {
        cout << "Здесь уже занято.\n";
        player_print();
    }
    else
        a[r][c] = t;
}

int defend(int c, int p, int b)// Оборонные ходы от AI
{
    if (b < 3)
        return 0;
    else if (a[0][0] + a[1][1] + a[2][2] == 2 * c && a[0][0] != p && a[1][1] != p && a[2][2] != p)
    {
        for (int i = 0; i < 3; i++)
        {
            if (a[i][i] == 0)
            {
                a[i][i] = y;
                cout << "Ход безупречного AI: " << i + 1 << " " << i + 1 << endl;
                return 1;
            }
        }
    }
    else if (a[0][2] + a[1][1] + a[2][0] == 2 * c && a[0][2] != p && a[1][1] != p && a[2][0] != p)
    {
        for (int i = 0; i < 3; i++)
        {
            if (a[i][2 - i] == 0)
            {
                a[i][2 - i] = y;
                cout << "Ход безупречного AI: " << i + 1 << " " << 3 - i << endl;
                return 1;
            }
        }
    }
    else
    {
        int i, j;
        for (i = 0; i < 3; i++)
        {
            if (a[i][0] + a[i][1] + a[i][2] == 2 * c && a[i][0] != p && a[i][1] != p && a[i][2] != p)
            {
                for (j = 0; j < 3; j++)
                {
                    if (a[i][j] == 0)
                    {
                        a[i][j] = y;
                        cout << "Ход безупречного AI: " << i + 1 << " " << j + 1 << endl;
                        return 1;
                    }
                }
            }
            else if (a[0][i] + a[1][i] + a[2][i] == 2 * c && a[0][i] != p && a[1][i] != p && a[2][i] != p)
            {
                for (j = 0; j < 3; j++)
                {
                    if (a[j][i] == 0)
                    {
                        a[j][i] = y;
                        cout << "Ход безупречного AI: " << j + 1 << " " << i + 1 << endl;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int attack()//Победные ходы AI
{
    int i, j;
    if (a[0][0] + a[0][2] + a[2][0] + a[2][2] == t || a[0][0] + a[0][2] + a[2][0] + a[2][2] == 2 * t)
    {
        for (i = 0; i < 3; i++)
        {
            if (a[i][0] + a[i][1] + a[i][2] == y && (a[i][0] == y || a[i][1] == y || a[i][2] == y))
            {
                if (i == 1)
                {
                    for (j = 0; j < 3; j++)
                    {
                        if (a[i][j] == 0)
                        {
                            a[i][j] = y;
                            cout << "Ход безупречного AI: " << i + 1 << " " << j + 1 << endl;
                            return 1;
                        }
                    }
                }
                else
                {
                    for (j = 2; j >= 0; j--)
                    {
                        if (a[i][j] == 0)
                        {
                            a[i][j] = y;
                            cout << "Ход безупречного AI: " << i + 1 << " " << j + 1 << endl;
                            return 1;
                        }
                    }
                }
            }
            if (a[0][i] + a[1][i] + a[2][i] == y && (a[0][i] == y || a[1][i] == y || a[2][i] == y))
            {
                if (i == 1)
                {
                    for (j = 0; j < 3; j++)
                    {
                        if (a[j][i] == 0)
                        {
                            a[j][i] = y;
                            cout << "Ход безупречного AI: " << j + 1 << " " << i + 1 << endl;
                            return 1;
                        }
                    }
                }
                else
                {
                    for (j = 2; j >= 0; j--)
                    {
                        if (a[j][i] == 0)
                        {
                            a[j][i] = y;
                            cout << "Ход безупречного AI: " << j + 1 << " " << i + 1 << endl;
                            return 1;
                        }
                    }
                }

            }
        }

        if (a[0][0] + a[1][1] + a[2][2] == y && (a[0][0] == y || a[1][1] == y || a[2][2] == y))
        {
            for (i = 2; i >= 0; i--)
            {
                if ((a[i][i] == 0) && ((a[i][0] + a[i][1] + a[i][2] == y && (a[i][0] == y || a[i][1] == y || a[i][2] == y)) ||
                    ((a[0][i] + a[1][i] + a[2][i] == y) && (a[0][i] == y || a[1][i] == y || a[2][i] == y))))
                {
                    a[i][i] = y;
                    cout << "Ход безупречного AI: " << i + 1 << " " << i + 1 << endl;
                    return 1;
                }
            }
            for (i = 2; i >= 0; i--)
            {
                if (a[i][i] == 0)
                {
                    if ((a[i][0] + a[i][1] + a[i][2] == t && (a[i][0] == t || a[i][1] == t || 
                        a[i][2] == t)) && (a[0][i] + a[1][i] + a[2][i] == t && (a[0][i] == t || a[1][i] == t || a[2][i] == t)))
                    {
                        a[i][i] = y;
                        cout << "Ход безупречного AI: " << i + 1 << " " << i + 1 << endl;
                        return 1;
                    }
                }
            }
            for (i = 2; i >= 0; i--)
            {
                if (a[i][i] == 0)
                {
                    a[i][i] = y;
                    cout << "Ход безупречного AI: " << i + 1 << " " << i + 1 << endl;
                    return 1;
                }
            }
        }
        else if (a[0][2] + a[1][1] + a[2][0] == y && (a[0][2] == y || a[1][1] == y || a[2][0] == y))
        {
            for (i = 2; i >= 0; i--)
            {
                if (a[i][2 - i] == 0 && ((a[i][0] + a[i][1] + a[i][2] == y && (a[i][0] == y || a[i][1] == y ||
                    a[i][2] == y)) || ((a[0][2 - i] + a[1][2 - i] + a[2][2 - i] == y) && (a[0][2 - i] == y || a[1][2 - i] == y || a[2][2 - i] == y))))
                {
                    a[i][2 - i] = y;
                    cout << "Ход безупречного AI: " << i + 1 << " " << 3 - i << endl;
                    return 1;
                }
            }
            for (i = 2; i >= 0; i--)
            {
                if (a[i][2 - i] == 0)
                {
                    if ((a[i][0] + a[i][1] + a[i][2] == t && (a[i][0] == t || a[i][1] == t || a[i][2] == t)) && 
                        (a[0][2 - i] + a[1][2 - i] + a[2][2 - i] == t && (a[0][2 - i] == t || a[1][2 - i] == t || a[2][2 - i] == t)))
                    {
                        a[i][2 - i] = y;
                        cout << "Ход безупречного AI: " << i + 1 << " " << 3 - i << endl;
                        return 1;
                    }
                }
            }
            for (i = 2; i >= 0; i--)
            {
                if (a[i][2 - i] == 0)
                {
                    a[i][2 - i] = y;
                    cout << "Ход безупречного AI: " << i + 1 << " " << 3 - i << endl;
                    return 1;
                }
            }
        }
    }
    else
    {
        if (a[0][0] + a[1][1] + a[2][2] == y && (a[0][0] == y || a[1][1] == y || a[2][2] == y))
        {
            for (i = 2; i >= 0; i--)
            {
                if ((a[i][i] == 0) && ((a[i][0] + a[i][1] + a[i][2] == y && (a[i][0] == y || a[i][1] == y || a[i][2] == y)) 
                    || ((a[0][i] + a[1][i] + a[2][i] == y) && (a[0][i] == y || a[1][i] == y || a[2][i] == y))))
                {
                    a[i][i] = y;
                    cout << "Ход безупречного AI: " << i + 1 << " " << i + 1 << endl;
                    return 1;
                }
            }
            for (i = 2; i >= 0; i--)
            {
                if (a[i][i] == 0)
                {
                    if ((a[i][0] + a[i][1] + a[i][2] == t && (a[i][0] == t || a[i][1] == t || a[i][2] == t)) && 
                        (a[0][i] + a[1][i] + a[2][i] == t && (a[0][i] == t || a[1][i] == t || a[2][i] == t)))
                    {
                        a[i][i] = y;
                        cout << "Ход безупречного AI: " << i + 1 << " " << i + 1 << endl;
                        return 1;
                    }
                }
            }
            for (i = 2; i >= 0; i--)
            {
                if (a[i][i] == 0)
                {
                    a[i][i] = y;
                    cout << "Ход безупречного AI: " << i + 1 << " " << i + 1 << endl;
                    return 1;
                }
            }
        }

        else if (a[0][2] + a[1][1] + a[2][0] == y && (a[0][2] == y || a[1][1] == y || a[2][0] == y))
        {
            for (i = 2; i >= 0; i--)
            {
                if (a[i][2 - i] == 0 && ((a[i][0] + a[i][1] + a[i][2] == y && (a[i][0] == y || a[i][1] == y || a[i][2] == y)) || 
                    ((a[0][2 - i] + a[1][2 - i] + a[2][2 - i] == y) && (a[0][2 - i] == y || a[1][2 - i] == y || a[2][2 - i] == y))))
                {
                    a[i][2 - i] = y;
                    cout << "Ход безупречного AI: " << i + 1 << " " << 3 - i << endl;
                    return 1;
                }
            }
            for (i = 2; i >= 0; i--)
            {
                if (a[i][2 - i] == 0)
                {
                    if ((a[i][0] + a[i][1] + a[i][2] == t && (a[i][0] == t || a[i][1] == t || a[i][2] == t)) && 
                        (a[0][2 - i] + a[1][2 - i] + a[2][2 - i] == t && (a[0][2 - i] == t || a[1][2 - i] == t || a[2][2 - i] == t)))
                    {
                        a[i][2 - i] = y;
                        cout << "Ход безупречного AI: " << i + 1 << " " << 3 - i << endl;
                        return 1;
                    }
                }
            }

            for (i = 2; i >= 0; i--)
            {
                if (a[i][2 - i] == 0)
                {
                    a[i][2 - i] = y;
                    cout << "Ход безупречного AI: " << i + 1 << " " << 3 - i << endl;
                    return 1;
                }
            }
        }

        else
        {
            for (i = 0; i < 3; i++)
            {
                if (a[i][0] + a[i][1] + a[i][2] == y && (a[i][0] == y || a[i][1] == y || a[i][2] == y))
                {
                    if (i == 1)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            if (a[i][j] == 0)
                            {
                                a[i][j] = y;
                                cout << "Ход безупречного AI: " << i + 1 << " " << j + 1 << endl;
                                return 1;
                            }
                        }
                    }
                    else {
                        for (j = 2; j >= 0; j--)
                        {
                            if (a[i][j] == 0)
                            {
                                a[i][j] = y;
                                cout << "Ход безупречного AI: " << i + 1 << " " << j + 1 << endl;
                                return 1;
                            }
                        }
                    }
                }
                else if (a[0][i] + a[1][i] + a[2][i] == y && (a[0][i] == y || a[1][i] == y || a[2][i] == y))
                {
                    if (i == 1)
                    {
                        for (j = 0; j < 3; j++)
                        {
                            if (a[j][i] == 0)
                            {
                                a[j][i] = y;
                                cout << "Ход безупречного AI: " << j + 1 << " " << i + 1 << endl;
                                return 1;
                            }
                        }
                    }
                    else
                    {
                        for (j = 2; j >= 0; j--)
                        {
                            if (a[j][i] == 0)
                            {
                                a[j][i] = y;
                                cout << "Ход безупречного AI: " << j + 1 << " " << i + 1 << endl;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void ai(int b)//Управление ходами AI
{
    if (!defend(y, t, b))
    {
        if (!defend(t, y, b))
        {
            if ((a[0][0] + a[0][2] + a[2][0] + a[2][2] == t + y || a[0][0] + a[0][2] + a[2][0] + a[2][2] == t + 2 * y) && a[1][1] == 0)
            {
                for (int i = 0; i < 3; i += 2)
                {
                    for (int j = 0; j < 3; j += 2)
                        if (a[i][j] == 0)
                        {
                            a[i][j] = y;
                            cout << "Ход безупречного AI: " << i + 1 << " " << j + 1 << endl;
                            goto end;
                        }
                }

            }
            else if (b == 2 && a[1][1] == 0)
            {
                a[1][1] = y;
                cout << "Ход безупречного AI: 2 2\n";
                goto end;
            }
            if (!attack())
            {
                if (b == 0)
                {
                    time_t seconds;
                    time(&seconds);
                    srand((unsigned int)seconds);
                    int i, j;
                    a[(rand() % 2) * 2][(rand() % 2) * 2] = y;
                    for (i = 0; i < 3; i += 2)
                    {
                        for (j = 0; j < 3; j += 2)
                            if (a[i][j] == y)
                                cout << "Ход безупречного AI: " << i + 1 << " " << j + 1 << endl;
                    }
                }
                else if (a[1][1] == 0)
                {
                    a[1][1] = y;
                    cout << "Ход безупречного AI: 2 2\n";
                }
                else
                {
                    int i, j;
                    for (i = 0; i < 3; i++)
                    {
                        for (j = 0; j < 3; j++)
                        {
                            if (a[i][j] == 0)
                            {
                                a[i][j] = y;
                                cout << "Ход безупречного AI: " << i + 1 << " " << j + 1 << endl;
                                goto end;
                            }
                        }
                    }
                }
            }
        }
    }
end:
    cout << endl;
}

int main()
{
    system("chcp 1251");
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            a[i][j] = 0;
    if (game == 1)
    {
        cout << "Как Вас зовут? ";
        gets_s(name);
        strcpy_s(str, "\nДоброго времени суток, ");
        strcat_s(str, name);
        cout << str << endl;

        strcpy_s(str, "\nВыберите свой ход ");
        strcat_s(str, name);
        strcat_s(str, ", хотите быть 1ым или 2ым?");
        cout<<str<<endl;
    }
    else
    {
        cout << str << endl;;

        strcpy_s(str, "\n На этот раз Вы хотите ходить 1ым или 2ым, ");
        strcat_s(str, name);
        strcat_s(str, "?");
        cout<<str<<endl;
    }

input:
    cin >> t;
    switch (t)
    {
    case 1:
        y = 2;
        cout << "\nВы играете за X.\nВаш противник - O.\n";
        print();
        for (i = 0; i < 9;)
        {
            player_print();
            print();
            i++;
            if (i > 4)
                if (check())
                {
                    strcpy_s(str, "\nПохоже, Вы выиграли ");
                    strcat_s(str, name);
                    strcat_s(str, " .\nПоздравляю\nОтличная работа!\n\nПохоже, я облажался в коде.\n(((((((");
                    cout<<str<<endl;
                    exit(0);
                    break;
                }
            if (i >= 8)
                break;
            ai(i);
            print();
            i++;
            if (i > 5)
                if (check())
                {
                  
                    if (game > 1)
                        strcat_s(str, ", Ну меня вообще не победить.");
                    else
                        strcat_s(str, ", ха-ха, я выиграл.");
                    cout<<str<<endl;
                    break;
                }
        }
        break;

    case 2:
        y = 1;
        cout << "\nВы играете за O.\nВаш противник - X.\n\nПриступим к игре.";
        print();
        for (i = 0; i < 9;)
        {
            ai(i);
            print();
            i++;
            if (i > 4)
                if (check())
                {
                    if (game > 1)
                        strcat_s(str, ", Ну меня вообще не победить.");
                    else
                        strcat_s(str, ", ха-ха, я выиграл.");
                    cout << str << endl;
                    break;
                }
            if (i >= 8)
                break;
            player_print();
            print();
            i++;
            if (i > 5)
                if (check())
                {
                    strcpy_s(str, "\nПохоже, Вы выиграли ");
                    strcat_s(str, name);
                    strcat_s(str, " .\nПоздравляю\nОтличная работа!\n\nПохоже, я облажался в коде.\n(((((((.");
                    exit(0);
                    break;
                }
        }
        break;
    default:
        strcpy_s(str, "Ну что, ");
        strcat_s(str, name);
        strcat_s(str, " Вам нужно ввести 1 или 2.");
        cout<<str<<endl;
        cout << "\nВведите снова: ";
        goto input;
        break;
    }
    if (!check())
    {
        if (game > 1)
            cout << "Хорошо поиграли!\nНо меня просто не переиграть никогда\n";
        else
            cout << "Неплохо сыграно!\n";

    }
    char c;
    strcpy_s(str, "Сыграем снова? ");
    strcat_s(str, name);
    strcat_s(str, " y/n?");
    cout<<str<<endl;
    cin >> c;
    if (c == 'y' || c == 'Y')
    {
        game++;
        main();
    }
    else
        exit(0);
    return 0;
}