#ifndef HEADER_C731EE1489777510
#define HEADER_C731EE1489777510
//玩家类，继承自虚基类MudBase
#include <iostream>
#include <string>
#include <vector>

#include "MudBase.h"

#define MAXSKILL  20
#define MAXITEMS  15

using namespace std;

struct Players {
    char code[40];  //编号（用于游戏登录）
    char name[40];  //游戏姓名
    char pwd[40];   //登录密码
    int attack;     //攻击值（对怪兽攻击加成）
    int defense;    //防御值（削弱怪兽攻击）
    int HP;         //生命值
    int exPoint;    //经验值（学技能，用于攻击怪兽）
    int money;      //金钱（购买商品，用于提高攻击力和防御力）
    int house;      //学院

    int hasLevel;  //玩家等级（会对应生成怪兽等级）
    int hasSkill[MAXSKILL]; //持有技能标识表 0/1
    int hasItems[MAXITEMS]; //持有商品数量表

};

class Player : public MudBase {
public:
    using MudBase::MudBase; //继承构造函数

    vector<struct Players *> getPlayers();
    void setPlayers(vector<struct Players *> newPlayers);
    void LoadData() override;
    void SaveData() override;
    void InpData() override;
    void OutData() override; //显示玩家数据
    void StaAction() override;
    void EndAction() override;
    int Getid(char* scode);

    bool CheckPlayer(char* tcode); //检查玩家是否已经存在
    void SignData(char* tempcode,char* tempname,char*temppwd, int temphouse); //玩家注册
    bool Login(char* tcode, char* tpwd); //登录
    void NewData(char* tempname,int temphouse); //玩家选择新开游戏

    char* GetCode();
    char* GetName();
    char* GetPwd();
    int GetAttack();
    int GetDefense();
    int GetHP();
    int GetExPoint();
    int GetMoney();
    int GetHouse();
    int GetLevel();
    int GetHasSkills(int index);
    int GetHasItems(int index);
    int GetAmapId();
    void SetCode(char* newCode);
    void SetName(char* newName);
    void SetPwd(char* newPwd);
    void SetAttack(int newAttack);
    void SetDefense(int newDefense);
    void SetHP(int newHP);
    void SetExPoint(int newExPoint);
    void SetMoney(int newMoney);
    void SetHouse(int newHouse);
    void SetLevel(int newLevel);
    void SetHasSkills(int index, int value);
    void SetHasItems(int index, int value);

    void AddMoney(int);
    void SubMoney(int);
    void AddExPoint(int);
    void SubExPoint(int);
    void AddItem(int,int);
    void SubItem(int,int);
    void AddAttack(int);
    void SubAttack(int);
    void AddDefense(int);
    void SubDefense(int);
    void AddHasSkills(int index);
    void AddHasItems(int index,int qty);
    void SubHasItems(int index);
    int CheckItems(); //检查是否有物资（用于打斗）
    int CheckSkill(); //检查是否有技能（用于打斗）
    void AddHasLevel();
    void AddHP(int);
    void SubHP(int);

    void WinFight(); //打斗胜利后的奖励升级

    void BuyItem(int ind,int att, int def, int qty, int mon);  //买物资
    void LearnSkill(int ind,int exp, int HP); //学技能
    void Hospital(); //医院加血
    void Speak(); //玩家打斗中的台词

protected:
    vector<struct Players *> players;
    vector<string> words = {"你的招式华而不实，看我的！",
                            "哼，这点攻击也想伤到我？",
                            "别小看了我的速度！",
                            "你的防御如同虚设，受死吧！",
                            "这一击将决定胜负！",
                            "你以为能逃过我的追击吗？",
                            "你的力量，不过如此！",
                            "闪避，同时反击，这是我的节奏！",
                            "休想近身，我的法术可不是闹着玩的！",
                            "哼，你的招式已经被我看穿了！",
                            "别挣扎了，你的败局已定！",
                            "接招吧，这是我新学的绝技！",
                            "你的动作太慢，跟不上我的步伐！",
                            "防御？在我看来只是徒劳！",
                            "看我的连续攻击，你无处可逃！",
                            "哈哈，你的招式对我无效！",
                            "想击败我？你还差得远呢！",
                            "闪避的同时，我也在寻找你的破绽！",
                            "你的力量，不过是我前进的垫脚石！",
                            "别以为我会给你喘息的机会！",
                            "我的法术，可是经过千锤百炼的！",
                            "你的攻击，对我来说只是微风拂面！",
                            "看招！这一击蕴含了我的全部力量！",
                            "你的速度虽快，但我的反应更快！",
                            "别妄想能在我眼皮子底下耍花样！",
                            "哼，你的招式已经过时了！",
                            "想战胜我，你得先跟上我的节奏！",
                            "我的攻击，可是无懈可击的！",
                            "别挣扎了，接受失败吧！"
                           };

};

#endif // header guard

