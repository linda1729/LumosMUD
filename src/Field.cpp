#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

#include "Field.h"

void Field::Init() {
    playerX = 0;
    playerY = FHEIGHT / 2;
    goalX = FWIDTH - 1;
    goalY = FHEIGHT / 2;
    gameOver = false;
    gameWin = false;
    obstacleX = FWIDTH - 1;

    tmap.resize(FHEIGHT, vector<char>(FWIDTH, ' '));
    tmap[playerY][playerX] = 'P'; // 'P'表示玩家
    tmap[goalY][goalX] = 'G';     // 'G'表示终点

    gapY = rand() % FHEIGHT;      // 初始化第一个障碍物列的缺口
}

Field::Field() {
    Init();
}

// 用于在控制台上绘制地图
void Field::DrawMap() {
    system("cls");
    // 遍历地图的每一行（高度）
    for (int y = 0; y < FHEIGHT; y++) {
        // 遍历地图的每一列（宽度）
        for (int x = 0; x < FWIDTH; x++) {
            // 输出当前位置(x, y)的地图信息，假设map[y][x]存储了对应位置的信息
            cout << tmap[y][x];
        }
        // 每完成一行的绘制后换行
        cout << endl;
    }
}

void Field::UpdateObstacles() {
    // 清除旧位置上的障碍物
    for (int y = 0; y < FHEIGHT; y++) {
        if (obstacleX < FWIDTH) {     // 确保obstacleX没有超出地图宽度
            tmap[y][obstacleX] = ' '; // 将旧位置上的障碍物清除
        }
    }

    // 更新障碍物位置，向左移动一格
    obstacleX--;

    if (obstacleX >= 0) {
        // 在新位置绘制障碍物，留出缺口
        for (int y = 0; y < FHEIGHT; y++) {
            if (y != gapY) {
                tmap[y][obstacleX] = '#'; // 在新位置上绘制障碍物
            }
        }
    }

    // 当障碍物移动出屏幕后，重新生成
    if (obstacleX < 0) {
        obstacleX = FWIDTH - 1;
        gapY = rand() % FHEIGHT; // 重新设置缺口位置
    }

    // 确保终点始终显示
    tmap[goalY][goalX] = 'G';
}

void Field::MovePlayer(char input) {
    tmap[playerY][playerX] = ' '; // 清除玩家的旧位置

    if ((input == 'w' || input == 'W') && playerY > 0) playerY--;
    if ((input == 's' || input == 'S') && playerY < FHEIGHT - 1) playerY++;
    if ((input == 'a' || input == 'A') && playerX > 0) playerX--;
    if ((input == 'd' || input == 'D') && playerX < FWIDTH - 1) playerX++;

    // 碰到障碍物则游戏结束
    if (tmap[playerY][playerX] == '#') {
        gameOver = true;
    }

    tmap[playerY][playerX] = 'P'; // 玩家新位置
}

void Field::CheckCollision() {
    // 碰撞检测函数，用于检查玩家是否与障碍物或终点重叠
    // 碰撞检测: 如果玩家当前位置与障碍物重叠（即map上该位置为'#'），则游戏结束
    if (tmap[playerY][playerX] == '#') {
        // 设置游戏结束标志为true
        gameOver = true;
        // 同时，设置游戏胜利标志为false，因为此时是碰撞导致游戏结束
        gameWin = false;
    }

    // 到达终点检测: 如果玩家的当前位置与终点的位置相同，则游戏结束且玩家胜利
    if (playerX == goalX && playerY == goalY) {
        // 设置游戏结束标志为true
        gameOver = true;
        // 同时，设置游戏胜利标志为true，因为玩家已经到达终点
        gameWin = true;
    }
}

bool Field::isGameWon() {

    return gameWin;
}

bool Field::isGameOver() const {
    return gameOver;
}

double Field::Play() {
    Init();
    srand(static_cast<unsigned>(time(0))); // 设置随机种子
    clock_t startTime = clock();
    char input;

    while (!gameOver) {
        DrawMap();

        if (_kbhit()) {  // 检测键盘输入
            input = _getch();
            MovePlayer(input); // 移动玩家
        }

        UpdateObstacles(); // 更新障碍物

        CheckCollision(); // 检查是否到达终点

        Sleep(MOVE_DELAY); // 调整游戏速度
    }

    // 在游戏结束之前，清除所有障碍物
    for (int y = 0; y < FHEIGHT; y++) {
        for (int x = 0; x < FWIDTH; x++) {
            if (tmap[y][x] == '#') {
                tmap[y][x] = ' '; // 清除障碍物
            }
        }
    }

    // 重新绘制清理后的地图
    DrawMap();

    clock_t endTime = clock();
    double totalTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;

    if (gameWin) {
        cout << "游戏胜利！" << endl;
        return static_cast<int>(totalTime); // 返回总时间的整数部分
    } else {
        cout << "游戏失败！" << endl;
        return 0; // 返回失败时的值
    }
}


