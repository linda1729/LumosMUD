#ifndef HEADER_6762314294ED2E1A
#define HEADER_6762314294ED2E1A
//商品/物资类，继承自虚基类MudBase
#include <iostream>
#include <string>
#include <vector>

#include "MudBase.h"
#include "Player.h"

using namespace std;


struct Items {
    string code;    //编号
    string title;   //名称
    int  attack;      //增加攻击值
    int  defense;     //增加防御值
    int  price;       //单价（金币）
    int  itemLevel;   //商品等级
    string info;   //商品说明
};

class Item : public MudBase {
public:
    using MudBase::MudBase; //继承构造函数

    vector<struct Items *> getItems();
    void setItems(vector<struct Items *> newItems);
    void LoadData() override;
    void SaveData() override;
    void InpData() override; //购买函数
    void OutData() override; //展示商品
    void StaAction() override; //初始化、触发类功能
    void EndAction() override; //释放数据
    int Getid(const string& scode);

    void Package(); //展示玩家背包中的物资
    void UseItem(int); //打斗中使用商品进行相应的扣除

protected:
    vector<struct Items *> items;
    Player *player;

private:

};

#endif // header guard

