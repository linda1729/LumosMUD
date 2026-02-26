#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <windows.h>

#include "MudBase.h"
#include "Player.h"
#include "MudGame.h"

using namespace std;

extern MudGame mudGame;

extern SetConsoleColor(WORD color);
extern ResetConsoleColor();
extern printCharByChar(const string& text, int delayMs);

vector<struct Players *> Player::getPlayers() {
    return players;
}

void Player::setPlayers(vector<struct Players *> newPlayers) {
    players = newPlayers;
}

void Player::LoadData() {
    if (dataFile.empty()) return;

    ifstream infile(dataFile, ios::binary);
    if (!infile.is_open()) {
        ofstream create(dataFile, ios::binary);
        return;
    }
    infile.close();

    LoadDataT<Players>(players,dataFile);
    return;
}

void Player::SaveData() {
    SaveDataT<Players>(players,dataFile);
    return;
}

void Player::InpData() {
    return;
}

//检查玩家是否已经存在
bool Player::CheckPlayer(char* tcode) {
    for (int i = 0; i < (int)players.size(); ++i) {
        if (strcmp(players[i]->code, tcode) == 0) {
            cid =i;
            return true; // 如果找到匹配的玩家，返回 1
        }
    }
    return false; // 如果没有找到匹配的玩家，返回 0
}

//登录
bool Player::Login(char* tcode, char* tpwd) {
    for (int i=0; i<(int)players.size(); ++i) {
        if((strcmp(players[i]->code,tcode)==0)&&(strcmp(players[i]->pwd,tpwd)==0))
            return true; // 如果用户名和密码都匹配，返回 1
    }
    return false; // 如果没有找到匹配的玩家，返回 0
}

//玩家注册
void Player::SignData(char* tempcode,char* tempname,char* temppwd, int temphouse) {
    struct Players *st;

    st = new Players;
    fill(st->code,st->code+40,0);
    fill(st->name,st->name+40,0);
    fill(st->pwd, st->pwd +40,0);
    strcpy(st->code,tempcode);
    strcpy(st->name,tempname);
    strcpy(st->pwd, temppwd);

    switch(temphouse) {
    case 1:	    //格兰芬多
        st->attack=35;
        st->defense=28;
        st->exPoint=200;
        st->money=100;
        break;

    case 2:    //斯莱特林
        st->attack=34;
        st->defense=29;
        st->exPoint=200;
        st->money=100;
        break;

    case 3:    //拉文克劳
        st->attack=27;
        st->defense=36;
        st->exPoint=200;
        st->money=100;
        break;

    case 4:    //赫奇帕奇
        st->attack=32;
        st->defense=31;
        st->exPoint=200;
        st->money=100;
        break;
    }
    st->HP=100;
    st->house=temphouse;
    st->hasLevel=1;
    for(int i=0; i<MAXSKILL; i++) st->hasSkill[i]=0;
    for(int i=0; i<MAXITEMS; i++) st->hasItems[i]=0;

    players.push_back(st);
}

//玩家选择新开游戏
void Player::NewData(char* tempname,int temphouse) {
    SetName(tempname);

    switch(temphouse) {
    case 1:	    //格兰芬多
        SetAttack(35);
        SetDefense(28);
        SetExPoint(200);
        SetMoney(100);
        break;

    case 2:    //斯莱特林
        SetAttack(34);
        SetDefense(29);
        SetExPoint(200);
        SetMoney(100);
        break;

    case 3:    //拉文克劳
        SetAttack(27);
        SetDefense(36);
        SetExPoint(200);
        SetMoney(100);
        break;

    case 4:    //赫奇帕奇
        SetAttack(32);
        SetDefense(31);
        SetExPoint(200);
        SetMoney(100);
        break;
    }
    SetHP(100);
    SetHouse(temphouse);
    SetLevel(1);
    for(int i=0; i<MAXSKILL; i++) SetHasSkills(i,0);
    for(int i=0; i<MAXITEMS; i++) SetHasItems(i,0);

}

//显示玩家数据
void Player::OutData() {
    int i = cid;
    cout << endl;
    cout << "       <玩家资料>      " << endl
         << "------------------------" << endl;
    cout << "编号: " << players[i]->code << endl;
    cout << "游戏名: " << players[i]->name << endl;
    cout << "攻击力: " << players[i]->attack << endl;
    cout << "防御力: " << players[i]->defense << endl;
    cout << "HP: " << players[i]->HP << endl;
    cout << "经验值: " << players[i]->exPoint << endl;
    cout << "金币: " << players[i]->money << endl;
    cout << "学院: ";
    switch (players[i]->house) {
    case 1:
        cout << "格兰芬多" << endl;
        break;
    case 2:
        cout << "斯莱特林" << endl;
        break;
    case 3:
        cout << "拉文克劳" << endl;
        break;
    case 4:
        cout << "赫奇帕奇" << endl;
        break;
    default:
        cout << "未知" << endl;
    }
    cout << "等级: " << players[i]->hasLevel << endl;
    cout << "------------------------"<<endl;
    return;
}

void Player::StaAction() {
    if(dataFile.size()>0) LoadData();
    return;
}

void Player::EndAction() {
    if(dataFile.size()>0) SaveData();

    for(int i=0; i<(int)players.size(); i++) delete players[i];
    return;
}

int Player::Getid(char* scode) {
    return GetidT(players,scode);
}

//买商品
void Player::BuyItem(int ind,int att, int def, int qty, int mon) {
    players[cid]->hasItems[ind] += qty;
    players[cid]->attack  += att;
    players[cid]->defense += def;
    players[cid]->money -= mon;
}

//学技能
void Player::LearnSkill(int ind, int exp, int HP) {
    players[cid]->hasSkill[ind]=1;
    players[cid]->exPoint -= exp;
    players[cid]->HP += HP;
}

char* Player::GetCode() {
    return players[cid]->code;
}

char* Player::GetName() {
    return players[cid]->name;
}

char* Player::GetPwd() {
    return players[cid]->pwd;
}

int Player::GetAttack() {
    return players[cid]->attack;
}

int Player::GetDefense() {
    return players[cid]->defense;
}

int Player::GetHP() {
    return players[cid]->HP;
}

int Player::GetExPoint() {
    return players[cid]->exPoint;
}

int Player::GetMoney() {
    return players[cid]->money;
}

int Player::GetHouse() {
    return players[cid]->house;
}

int Player::GetLevel() {
    return players[cid]->hasLevel;
}

int Player::GetHasSkills(int index) {
    return players[cid]->hasSkill[index];
}

int Player::GetHasItems(int index) {
    return players[cid]->hasItems[index];
}


void Player::SetCode(char* newCode) {
    if (cid<(int)players.size()) {
        strcpy(players[cid]->code,newCode);
    }
}
void Player::SetName(char* newName) {
    if (cid<(int)players.size()) {
        strcpy(players[cid]->name,newName);
    }
}

void Player::SetPwd(char* newPwd) {
    if (cid < (int)players.size()) {
        strcpy(players[cid]->pwd,newPwd);
    }
}

void Player::SetAttack(int newAttack) {
    if (cid < (int)players.size()) {
        players[cid]->attack = newAttack;
    }
}

void Player::SetDefense(int newDefense) {
    if (cid < (int)players.size()) {
        players[cid]->defense = newDefense;
    }
}

void Player::SetHP(int newHP) {
    if (cid < (int)players.size()) {
        players[cid]->HP = newHP;
    }
}

void Player::SetExPoint(int newExPoint) {
    if (cid < (int)players.size()) {
        players[cid]->exPoint = newExPoint;
    }
}

void Player::SetMoney(int newMoney) {
    if (cid < (int)players.size()) {
        players[cid]->money = newMoney;
    }
}

void Player::SetHouse(int newHouse) {
    if (cid < (int)players.size()) {
        players[cid]->house = newHouse;
    }
}

void Player::SetLevel(int newLevel) {
    if (cid < (int)players.size()) {
        players[cid]->hasLevel = newLevel;
    }
}

void Player::SetHasSkills(int index, int value) {
    if (cid<(int)players.size() && index<(int)sizeof(players[cid]->hasSkill)) {
        players[cid]->hasSkill[index] = value;
    }
}

void Player::SetHasItems(int index, int value) {
    if (cid < (int)players.size() && index<(int)sizeof(players[cid]->hasItems)) {
        players[cid]->hasItems[index] = value;
    }
}

void Player::AddMoney(int amt) {
    players[cid]->money += amt;
}

void Player::SubMoney(int amt)  {
    players[cid]->money -= amt;
}

void Player::AddHP(int amt) {
    players[cid]->HP += amt;
}

void Player::SubHP(int amt)  {
    players[cid]->HP -= amt;
}

void Player::AddExPoint(int amt) {
    players[cid]->exPoint += amt;
}

void Player::SubExPoint(int amt) {
    players[cid]->exPoint -= amt;
}

void Player::AddItem(int choice, int qty) {
    players[cid]->hasSkill[choice] += qty;
}

void Player::SubItem(int choice, int qty) {
    players[cid]->hasSkill[choice] -= qty;
}

void Player::AddAttack(int amt) {
    players[cid]->attack += amt;
}

void Player::SubAttack(int amt) {
    players[cid]->attack -= amt;
}

void Player::AddDefense(int amt) {
    players[cid]->defense += amt;
}

void Player::SubDefense(int amt) {
    players[cid]->defense -= amt;
}

void Player::AddHasSkills(int index) {
    players[cid]->hasSkill[index]=1;
}

void Player::AddHasItems(int index,int qty) {
    players[cid]->hasItems[index]+=qty;
}

void Player::SubHasItems(int index) {
    players[cid]->hasItems[index] --;
}

void Player::AddHasLevel() {
    players[cid]->hasLevel++;
}

//打斗胜利后的奖励升级
void Player::WinFight() {
    AddMoney((players[cid]->hasLevel)*100);
    AddExPoint((players[cid]->hasLevel)*60);
    cout<<"<奖励>"<<endl<<"掉落金币："<<(players[cid]->hasLevel)*100<<"\t新增经验值："<<(players[cid]->hasLevel)*60;
    AddHasLevel();
    cout<<"\t您的新等级："<<players[cid]->hasLevel<<endl;
}

//检查是否有物资（用于打斗）
int Player::CheckItems() {
    int num=0;
    for(int i=0; i<MAXITEMS; i++) {
        num=num+players[cid]->hasItems[i];
    }
    return num;
}

//检查是否有技能（用于打斗）
int Player::CheckSkill() {
    int num=0;
    for(int i=0; i<MAXSKILL; i++) {
        num=num+players[cid]->hasSkill[i];
    }
    return num;
}

//玩家台词
void Player::Speak() {
    srand(unsigned(time(nullptr)));
    int n=rand()%words.size();
    cout<<words[n];
}

//医院
void Player::Hospital() {
    SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    string text = "欢迎来到<圣芒戈医院>！\n"
                  "在这里，你可以通过花费<金币>和<经验点>来提升自己的<生命值>\n"
                  "以便更容易地击败禁林里的凶兽！\n\n";
    printCharByChar(text, 10); // 10毫秒延迟
    ResetConsoleColor();
    cout<<"你目前的血量为："<<GetHP()<<endl;
    cout<<"编号   治疗方案      经验点    金币    提升血值"<<endl
        <<"--------------------------------------------"<<endl
        <<"1      物理治疗      10        5       20       "<<endl
        <<"2      魔药治疗      15        10      25       "<<endl
        <<"3      咒语治疗      20        15      35       "<<endl;

    int p;
    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout<<endl<<"[1]立即治疗"<<endl<<"[2]单纯看看，下次再来"<<endl;
    ResetConsoleColor();
    cin>>p;
    if(p==1) {

        int ind=0;
        do {
            int choice = 0;
            cout<<"请选择治疗方案：";
            cin>>choice;
            while(choice!=1&&choice!=2&&choice!=3) {
                cout<<"输入错误！请重新输入：";
                cin>>choice;
            }
            if(choice==1) {
                if(GetExPoint()>=10&&GetMoney()>=5) {
                    AddHP(20);
                    SubExPoint(10);
                    SubMoney(5);
                    cout<<"治疗成功！你目前的血值是："<<GetHP()<<endl;
                } else cout<<"治疗失败！金币/经验值不足！"<<endl;
            } else if(choice==2) {
                if(GetExPoint()>=15&&GetMoney()>=10) {
                    AddHP(25);
                    SubExPoint(15);
                    SubMoney(10);
                    cout<<"治疗成功！你目前的血值是："<<GetHP()<<endl;
                } else cout<<"治疗失败！金币/经验值不足！"<<endl;
            } else {
                if(GetExPoint()>=10&&GetMoney()>=5) {
                    AddHP(35);
                    SubExPoint(20);
                    SubMoney(15);
                    cout<<"治疗成功！你目前的血值是："<<GetHP()<<endl;
                } else cout<<"治疗失败！金币/经验值不足！"<<endl;
            }
            cout<<"请选择："<<endl<<"[1]继续治疗"<<endl<<"[2]离开医院"<<endl;
            cin>>ind;
        } while(ind==1);
    }

}
