#ifndef FIELD_H
#define FIELD_H
//该类用于完成<魁地奇球场>（即躲避球游戏）
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int FWIDTH = 40;  // 地图宽度
const int FHEIGHT = 10; // 地图高度
const int MOVE_DELAY = 100; // 调整游戏速度，使障碍物出现的间隔缩短

class Field {
public:
    Field();
    void DrawMap();
    void UpdateObstacles();
    void MovePlayer(char input);
    void CheckCollision();
    bool isGameOver() const;
    bool isGameWon();

    void Init();
    double Play();

protected:
    vector<vector<char>> tmap;
    int playerX, playerY;
    int goalX, goalY;
    int obstacleX;  // 仅记录当前一列障碍物的X位置
    int gapY;       // 当前障碍物列的缺口位置
    bool gameOver;
    bool gameWin;

};

#endif // FIELD_H
