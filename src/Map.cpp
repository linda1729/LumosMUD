#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

#include "Map.h"
#include "Fight.h"
#include "MudGame.h"
#include "Player.h"

using namespace std;

extern MudGame mudGame;

#define Height 40
#define Width 99

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearLine(int y) {
    gotoxy(0, y);
    cout << string(100, ' ');
    gotoxy(0, y);  // 将光标移回该行的起始位置
}

Map::Map(const string& filename) : map(Height, vector<int>(Width)), playerx(1), playery(1) {
    if (!loadMazeFromFile(filename)) {
        gotoxy(0, 41);
        clearLine(41);
        cout << "Error: Failed to load the maze!" << endl;
        exit(1);
    }
}

bool Map::loadMazeFromFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        gotoxy(0, 41);
        clearLine(41);
        cout << "无法打开文件: " << filename << endl;
        return false;
    }

    for (int row = 0; row < Height; ++row) {
        for (int col = 0; col < Width; ++col) {
            char ch;
            file.get(ch);
            if (file) {
                map[row][col] = (ch == '1') ? 1 : 0;
                map[1][12] = 2;
                map[5][80] = 2;
                map[11][28] = 2;
                map[13][77] = 2;
                map[1][53] = 2;
                map[11][53] = 2;
                map[17][48] = 2;
                map[21][48] = 2;
                map[23][40] = 2;
                map[23][13] = 2;
                map[25][53] = 2;
                map[29][5] = 2;
                map[31][72] = 2;
            } else {
                gotoxy(0, 41);
                clearLine(41);
                cout << "读取文件失败" << endl;
                return false;
            }
        }
        file.ignore(); // 忽略换行符
    }

    file.close();
    return true;
}

void Map::printMaze() const {
    system("cls");

    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            if (x == playerx && y == playery)
                cout << "*";
            else if (map[y][x] == 1)
                cout << "1";
            else if (map[y][x] == 2)
                cout << "0";
            else
                cout << " ";
        }
        cout << endl;
    }
}

int Map::movePlayer() {
    int prevX = playerx, prevY = playery;
    int X = 0;
    int Y = 0;
    char  moveinput;
    Fight* ft = mudGame.getFight();

    while (1) {  //修改
        moveinput = _getch();
        if (moveinput == 'p' || moveinput == 'P') {
            return 0;  // 用户选择退出游戏
        }

        if (moveinput == 'w' || moveinput == 'W') {
            X = 0;
            Y = -1;
        } else if (moveinput == 's' || moveinput == 'S') {
            X = 0;
            Y = 1;
        } else if (moveinput == 'd' || moveinput == 'D') {
            X = 1;
            Y = 0;
        } else if (moveinput == 'a' || moveinput == 'A') {
            X = -1;
            Y = 0;
        } else continue;

        break;
    }

    // 检查目标位置是否为墙壁，并确保移动后不会超出边界
    if (map[playery + Y][playerx + X] != 1 && playery + Y >= 0 && playerx + X >= 0 && playery + Y < Height && playerx + X < Width) {
        playerx += X;
        playery += Y;
    }

    // 恢复玩家之前位置上的内容
    gotoxy(prevX, prevY);
    if (map[prevY][prevX] == 1) {
        cout << "1";  // 如果之前位置是墙壁，恢复为墙壁
    } else if (map[prevY][prevX] == 2) {
        cout << "0";
    } else {
        cout << " ";
    }

    // 显示玩家在新位置
    gotoxy(playerx, playery);
    cout << "*";
    cout.flush();

    //宝藏点
    if(playery==1&&playerx==53) {
        if (check[13] == 0) {
            char fightinput;
            gotoxy(0, 41);
            clearLine(41);
            cout << "你发现了宝箱";
            fightinput = _getch();
            gotoxy(0, Height + 1);
            clearLine(41);
            ft->Reward();
            Sleep(2000);
            printMaze();
            check[13] = 1;
        }
    }
    if (playery == 13 && playerx == 77) {
        if (check[12] == 0) {
            char fightinput;
            gotoxy(0, 41);
            clearLine(41);
            cout << "你发现了宝箱";
            fightinput = _getch();
            gotoxy(0, Height + 1);
            clearLine(41);
            ft->Reward();
            Sleep(2000);
            printMaze();
            check[12] = 1;
        }
    }
    if (playery == 23 && playerx == 40) {
        if (check[14] == 0) {
            char fightinput;
            gotoxy(0, 41);
            clearLine(41);
            cout << "你发现了宝箱";
            fightinput = _getch();
            gotoxy(0, Height + 1);
            clearLine(41);
            ft->Reward();
            Sleep(2000);
            printMaze();
            check[14] = 1;
        }
    }
    if (playery == 23 && playerx == 13) {
        if (check[15] == 0) {
            char fightinput;
            gotoxy(0, 41);
            clearLine(41);
            cout << "你发现了宝箱";
            fightinput = _getch();
            gotoxy(0, Height + 1);
            clearLine(41);
            ft->Reward();
            Sleep(2000);
            printMaze();
            check[15] = 1;
        }
    }
    //怪物点
    if (playery == 11 && playerx == 53) {
        if (check[4] == 0) {
            char fightinput;
            gotoxy(0, 41);
            clearLine(41);
            cout << "你遇到了怪物,是否战斗Y/N";
            fightinput = _getch();
            if (fightinput == 'y' || fightinput == 'Y') {
                gotoxy(0, Height + 1);
                clearLine(41);
                system("cls");
                cout << "你开始战斗了";
                ft->Battle();
                printMaze();
                check[4] = 1;
            } else {
                gotoxy(0, Height + 1);
                clearLine(41);
                cout << "面对强大的敌人，你选择撤退" << endl << "按[P]可返回<游戏菜单>";
                playerx = prevX;
                playery = prevY;
                gotoxy(prevX + X, prevY + Y);
                if (map[prevY + Y][prevX + X] == 1) {
                    cout << "1";  // 如果之前位置是墙壁，恢复为墙壁
                } else if (map[prevY + Y][prevX + X] == 2) {
                    cout << "0";
                } else {
                    cout << " ";
                }
                gotoxy(playerx, playery);
                cout << "*";
                cout.flush();
            }
        }
    }
    if (playery == 1 && playerx == 12) {
        if (check[0] == 0) {
            char fightinput;
            gotoxy(0, 41);
            clearLine(41);
            cout << "你遇到了怪物,是否战斗Y/N";
            fightinput = _getch();
            if (fightinput == 'y' || fightinput == 'Y') {
                gotoxy(0, Height + 1);
                clearLine(41);
                system("cls");
                cout << "你开始战斗了";
                ft->Battle();
                printMaze();
                check[0] = 1;
            } else {
                gotoxy(0, Height + 1);
                clearLine(41);
                cout << "面对强大的敌人，你选择撤退" << endl << "按[P]可返回<游戏菜单>";
                playerx = prevX;
                playery = prevY;
                gotoxy(prevX + X, prevY + Y);
                if (map[prevY + Y][prevX + X] == 1) {
                    cout << "1";  // 如果之前位置是墙壁，恢复为墙壁
                } else if (map[prevY + Y][prevX + X] == 2) {
                    cout << "0";
                } else {
                    cout << " ";
                }
                gotoxy(playerx, playery);
                cout << "*";
                cout.flush();
            }

        }
    }
    if (playery == 5 && playerx == 80) {
        if (check[1] == 0) {
            char fightinput;
            gotoxy(0, 41);
            clearLine(41);
            cout << "你遇到了怪物,是否战斗Y/N";
            fightinput = _getch();
            if (fightinput == 'y' || fightinput == 'Y') {
                gotoxy(0, Height + 1);
                clearLine(41);
                system("cls");
                cout << "你开始战斗了";
                ft->Battle();
                printMaze();
                check[1] = 1;
            } else {
                gotoxy(0, Height + 1);
                clearLine(41);
                cout << "面对强大的敌人，你选择撤退" << endl << "按[P]可返回<游戏菜单>";
                playerx = prevX;
                playery = prevY;
                gotoxy(prevX + X, prevY + Y);
                if (map[prevY + Y][prevX + X] == 1) {
                    cout << "1";  // 如果之前位置是墙壁，恢复为墙壁
                } else if (map[prevY + Y][prevX + X] == 2) {
                    cout << "0";
                } else {
                    cout << " ";
                }
                gotoxy(playerx, playery);
                cout << "*";
                cout.flush();
            }
        }
    }
    if (playery == 11 && playerx == 28) {
        if (check[2] == 0) {
            char fightinput;
            gotoxy(0, 41);
            clearLine(41);
            cout << "你遇到了怪物,是否战斗Y/N";
            fightinput = _getch();
            if (fightinput == 'y' || fightinput == 'Y') {
                gotoxy(0, Height + 1);
                clearLine(41);
                system("cls");
                cout << "你开始战斗了";
                ft->Battle();
                printMaze();
                check[2] = 1;
            } else {
                gotoxy(0, Height + 1);
                clearLine(41);
                cout << "面对强大的敌人，你选择撤退" << endl << "按[P]可返回<游戏菜单>";
                playerx = prevX;
                playery = prevY;
                gotoxy(prevX + X, prevY + Y);
                if (map[prevY + Y][prevX + X] == 1) {
                    cout << "1";  // 如果之前位置是墙壁，恢复为墙壁
                } else if (map[prevY + Y][prevX + X] == 2) {
                    cout << "0";
                } else {
                    cout << " ";
                }
                gotoxy(playerx, playery);
                cout << "*";
                cout.flush();
            }
        }
    }
    if (playery == 17 && playerx == 48) {
        if (check[6] == 0) {
            char fightinput;
            gotoxy(0, 41);
            clearLine(41);
            cout << "你遇到了怪物,是否战斗Y/N";
            fightinput = _getch();
            if (fightinput == 'y' || fightinput == 'Y') {
                gotoxy(0, Height + 1);
                clearLine(41);
                system("cls");
                cout << "你开始战斗了";
                ft->Battle();
                printMaze();
                check[6] = 1;
            } else {
                gotoxy(0, Height + 1);
                clearLine(41);
                cout << "面对强大的敌人，你选择撤退";
                playerx = prevX;
                playery = prevY;
                gotoxy(prevX + X, prevY + Y);
                if (map[prevY + Y][prevX + X] == 1) {
                    cout << "1";  // 如果之前位置是墙壁，恢复为墙壁
                } else if (map[prevY + Y][prevX + X] == 2) {
                    cout << "0";
                } else {
                    cout << " ";
                }
                gotoxy(playerx, playery);
                cout << "*";
                cout.flush();
            }
        }
    }
    if (playery == 21 && playerx == 48) {
        if (check[7] == 0) {
            char fightinput;
            gotoxy(0, 41);
            clearLine(41);
            cout << "你遇到了怪物,是否战斗Y/N";
            fightinput = _getch();
            if (fightinput == 'y' || fightinput == 'Y') {
                gotoxy(0, Height + 1);
                clearLine(41);
                cout << "你开始战斗了";
                system("cls");
                ft->Battle();
                printMaze();
                check[7] = 1;
            } else {
                gotoxy(0, Height + 1);
                clearLine(41);
                cout << "面对强大的敌人，你选择撤退" << endl << "按[P]可返回<游戏菜单>";
                playerx = prevX;
                playery = prevY;
                gotoxy(prevX + X, prevY + Y);
                if (map[prevY + Y][prevX + X] == 1) {
                    cout << "1";  // 如果之前位置是墙壁，恢复为墙壁
                } else if (map[prevY + Y][prevX + X] == 2) {
                    cout << "0";
                } else {
                    cout << " ";
                }
                gotoxy(playerx, playery);
                cout << "*";
                cout.flush();
            }
        }
    }
    if (playery == 25 && playerx == 53) {
        if (check[8] == 0) {
            char fightinput;
            gotoxy(0, 41);
            clearLine(41);
            cout << "你遇到了怪物,是否战斗Y/N";
            fightinput = _getch();
            if (fightinput == 'y' || fightinput == 'Y') {
                gotoxy(0, Height + 1);
                clearLine(41);
                cout << "你开始战斗了";
                system("cls");
                ft->Battle();
                printMaze();
                check[8] = 1;
            } else {
                gotoxy(0, Height + 1);
                clearLine(41);
                cout << "面对强大的敌人，你选择撤退" << endl << "按[P]可返回<游戏菜单>";
                playerx = prevX;
                playery = prevY;
                gotoxy(prevX + X, prevY + Y);
                if (map[prevY + Y][prevX + X] == 1) {
                    cout << "1";  // 如果之前位置是墙壁，恢复为墙壁
                } else if (map[prevY + Y][prevX + X] == 2) {
                    cout << "0";
                } else {
                    cout << " ";
                }
                gotoxy(playerx, playery);
                cout << "*";
                cout.flush();
            }
        }
    }
    if (playery == 29 && playerx == 5) {
        if (check[9] == 0) {
            char fightinput;
            gotoxy(0, 41);
            clearLine(41);
            cout << "你遇到了怪物,是否战斗Y/N";
            fightinput = _getch();
            if (fightinput == 'y' || fightinput == 'Y') {
                gotoxy(0, Height + 1);
                clearLine(41);
                system("cls");
                cout << "你开始战斗了";
                ft->Battle();
                printMaze();
                check[9] = 1;
            } else {
                gotoxy(0, Height + 1);
                clearLine(41);
                cout << "面对强大的敌人，你选择撤退" << endl << "按[P]可返回<游戏菜单>";
                playerx = prevX;
                playery = prevY;
                gotoxy(prevX + X, prevY + Y);
                if (map[prevY + Y][prevX + X] == 1) {
                    cout << "1";  // 如果之前位置是墙壁，恢复为墙壁
                } else if (map[prevY + Y][prevX + X] == 2) {
                    cout << "0";
                } else {
                    cout << " ";
                }
                gotoxy(playerx, playery);
                cout << "*";
                cout.flush();
            }
        }
    }
    if (playery == 31 && playerx == 72) {
        if (check[10] == 0) {
            char fightinput;
            gotoxy(0, 41);
            clearLine(41);
            cout << "你遇到了怪物,是否战斗Y/N";
            fightinput = _getch();
            if (fightinput == 'y' || fightinput == 'Y') {
                gotoxy(0, Height + 1);
                clearLine(41);
                system("cls");
                cout << "你开始战斗了";
                ft->Battle();
                printMaze();
                check[10] = 1;
            } else {
                gotoxy(0, Height + 1);
                clearLine(41);
                cout << "面对强大的敌人，你选择撤退" << endl << "按[P]可返回<游戏菜单>";
                playerx = prevX;
                playery = prevY;
                gotoxy(prevX + X, prevY + Y);
                if (map[prevY + Y][prevX + X] == 1) {
                    cout << "1";  // 如果之前位置是墙壁，恢复为墙壁
                } else if (map[prevY + Y][prevX + X] == 2) {
                    cout << "0";
                } else {
                    cout << " ";
                }
                gotoxy(playerx, playery);
                cout << "*";
                cout.flush();
            }
        }
    }
    return 1;
}

void Map::setxy(int x, int y) {
    playery = y;
    playerx = x;
}

//传送点（玩家退出并重新进入禁林后，可以根据存档继续上次的游戏）
void Map::setenter() {
    int x;
    x = mudGame.getPlayer()->GetLevel();
    switch (x) {
    case 1:
        setxy(1, 1);
        break;
    case 2:
        setxy(79, 5);
        break;
    case 3:
        setxy(54, 11);
        break;
    case 4:
        setxy(47, 17);
        break;
    case 5:
        setxy(49, 21);
        break;
    case 6:
        setxy(29, 11);
        break;
    case 7:
        setxy(4, 29);
        break;
    case 8:
        setxy(52, 25);
        break;
    case 9:
        setxy(71, 31);
        break;

    }
}

//检查玩家是否抵达终点通关
bool Map::isGameWon() const {
    return (playery == 37 && playerx == 98);
}

//禁林功能
int mapForest() {
    int result = 1;
    system("cls");
    Map gameMap(mudGame.dataPath("MAPforest.dat"));
    gameMap.setenter(); //按存档传送玩家
    gameMap.printMaze();

    while (!gameMap.isGameWon()) {
        result = gameMap.movePlayer();
        if (result == 0) {
            system("cls");
            cout << "\n你已离开禁林。" << endl;
            break;
        }
    }
    gotoxy(0, 41);
    clearLine(41);
    if (result) {
        system("cls");
        cout << "\n恭喜你通关成功！！！" << endl << "获得三件死亡圣器！" << endl;
        return 1;
    }
    return 0;
}
