#ifndef HEADER_704074145B1726F
#define HEADER_704074145B1726F
//怪兽类，继承自虚基类MudBase
#include <iostream>
#include <string>
#include <vector>

#include "MudBase.h"

using namespace std;

struct Monsters {
    string code;  //编号
    string title; //名称
    int  moHP;    //血条
    int  damage;  //损害值
    string info; //怪兽信息
};

class Monster : public MudBase {
public:
    using MudBase::MudBase; //继承构造函数

    vector<struct Monsters *> getMonsters();
    void setMonsters(vector<struct Monsters *> newMonsters);
    void LoadData();
    void SaveData();
    void InpData();
    void OutData();
    void StaAction();
    void EndAction();
    int Getid(const string& scode);

    int GetHP();
    int GetDamage();
    string GetName();
    string GetInfo();
    void Speak(); //输出怪兽台词
    void BeAttack(int); //减怪兽血量
    void ShowInfo();  //展示怪兽信息
    void Setid(int);  //用于生成怪兽

protected:
    vector<struct Monsters *> monsters;
    vector<string> words = {"感受我愤怒的咆哮吧，凡人!",
                            "你的末日已经到来，颤抖吧！",
                            "在黑暗的深渊中，我找到了你，现在，接受你的命运！",
                            "你的勇气令人钦佩，但力量，属于我！",
                            "让这无尽的黑暗吞噬你，成为我力量的一部分！",
                            "哼，区区蝼蚁，也敢挑战我的威严？",
                            "感受绝望的滋味吧，这是你最后的时刻！",
                            "我的利爪已经饥渴难耐，你的血肉将是我的盛宴！",
                            "在无尽的黑暗中，我是唯一的王，而你，只是我的玩物！",
                            "你的挣扎只是徒劳，接受命运的审判吧！",
                            "让这毁灭的风暴，成为你生命的终结乐章！",
                            "在绝望的深渊中，你将见证我真正的力量，那是你无法想象的恐怖！",
                            "我的愤怒如同火山爆发，你，就是那即将被淹没的尘埃！"
                           };

};

#endif // header guard

