#ifndef HEADER_A582BA8FB933897E
#define HEADER_A582BA8FB933897E
//打斗函数，实现打斗中的细节
#include <iostream>
#include <string>
#include <vector>

#include "Player.h"
#include "Amap.h"
#include "Monster.h"
#include "Item.h"
#include "Skill.h"

using namespace std;

class Fight {
public:
    Fight();
    ~Fight();
    int GetBattle(void);
    void SetBattle(int newBattle);
    bool Battle();
    void Reward();

protected:
    int battle=0;
    Player *player;
    Amap *amap;
    Monster *monster;
    Item *item;
    Skill *skill;

};

#endif // header guard

