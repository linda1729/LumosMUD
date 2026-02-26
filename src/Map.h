#ifndef HEADER_B08078AAD4AE6A2B
#define HEADER_B08078AAD4AE6A2B
//迷宫类
//包含怪兽点（触发打斗）、宝藏点、通关
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>

#define Height 40
#define Width 99

using namespace std;

void gotoxy(int x, int y);
void clearLine(int y);
int mapForest();

class Map {
public:
    Map(const string& filename);
    bool loadMazeFromFile(const string& filename);
    void printMaze() const;
    void setxy(int x, int y);
    void setenter();  //传送点（玩家退出并重新进入禁林后，可以根据存档继续上次的游戏）
    int movePlayer(); //移动玩家的点
    bool isGameWon() const; //判断是否通关

protected:
    vector<vector<int>> map;
    int playerx;
    int playery;
    int check[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//控制16个怪兽点/宝藏点被玩家触发的次数
};
#endif // header guard
