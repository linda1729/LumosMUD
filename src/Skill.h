#ifndef HEADER_5B587C26A3BBCD3D
#define HEADER_5B587C26A3BBCD3D

#include <iostream>
#include <string>
#include <vector>

#include "Player.h"
#include "MudBase.h"

using namespace std;

//Skill Data
struct Skills {
    string code;    //code
    string title;   //名字
    int  skHP;       //扣怪物血值
    int  worth;      //扣经验值（购买需要值）
    int  level;      //
    string info;   //介绍
};

class Skill : public MudBase {
public:
    using MudBase::MudBase; //继承构造函数

    vector<struct Skills *> getSkills();
    void setSkills(vector<struct Skills *> newSkills);
    void LoadData() override;
    void SaveData() override;
    void InpData() override; //学习技能
    void OutData() override;
    void StaAction() override;
    void EndAction() override;
    int Getid(const string& scode);

    string GetCode(int);
    string GetName(int);
    int GetMinHP(int);
    int GetWorth(int);
    int GetLevel(int);
    string GetInfo(int);
    void ShowMySkills();


protected:
    vector<struct Skills *> skills;
    Player *player;
private:

};

#endif // header guard

