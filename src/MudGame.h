#ifndef HEADER_DA38D4F2DBFAC45B
#define HEADER_DA38D4F2DBFAC45B
//全局中控类（菜单）
#include <iostream>
#include <string>

#include "Player.h"
#include "Item.h"
#include "Skill.h"
#include "Amap.h"
#include "Monster.h"
#include "Fight.h"
#include "Field.h"

using namespace std;

class MudGame {
public:
    int  mudMenu(); //菜单
    void mudInit(); //初始化各类数据、显示信息
    void mudStop(); //结束并释放各类空间
    void BeforeG(); //注册、登录

    Player *getPlayer();
    Item *getItem();
    Skill *getSkill();
    Amap *getAmap();
    Monster *getMonster();
    Fight *getFight();
    Field *getField();

    void Printtitle(); //打印欢迎界面
    void Printend(); //打印通关界面
    string backcolor(); //字体效果
    string color();
    void Printword();
    std::string dataPath(const std::string& filename) const;


protected:
    Amap   *amap;
    Item  *item;
    Skill *skill;
    Monster *monster;
    Player  *player;
    Fight   *fight;
    Field   *field;

};

#endif // header guard

