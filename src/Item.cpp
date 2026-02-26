#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#include <thread>
#include <chrono>

#include "Player.h"
#include "MudBase.h"
#include "Item.h"
#include "MudGame.h"

using namespace std;

extern MudGame mudGame;

extern SetConsoleColor(WORD color);
extern ResetConsoleColor();
extern printCharByChar(const string& text, int delayMs);


vector<struct Items *> Item::getItems() {
    return items;
}

void Item::setItems(vector<struct Items *> newItems) {
    items = newItems;
}

//文本数据读取
void Item::LoadData() {
    string data;
    struct Items *st;

    ifstream infile(dataFile,ios::in);
    if(!infile) {
        cout<< "Open error["<<dataFile<<"]!"<<endl;
        return;
    }
    while(infile.peek()!=EOF) {
        getline(infile,data);

        st = new Items();
        stringstream iss(data); //文本格式，用" "分隔
        iss>>st->code>>st->title>>st->attack>>st->defense>>st->price>>st->itemLevel>>st->info;
        iss.clear();
        items.push_back(st);
    }
    infile.close();

    return;
}

void Item::SaveData() {
    return;
}

//购买函数
void Item::InpData() {
    int qty,amt,num; //选择商品的总价、数量、序号
    int ind=0;//是否继续购买界面的标识

    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    string text = "欢迎踏入<对角巷>，魔法世界的购物天堂!\n"
                  "在这里，古灵阁、奥利凡德魔杖店、韦斯莱把戏坊与长袍店，应有尽有。\n"
                  "快探索隐秘小巷，开启非凡购物之旅吧......\n\n";
    printCharByChar(text, 10);
    ResetConsoleColor();
    cout <<"你的金币："<<player->GetMoney()<<endl;
    cout<<"以下是你可以选择换购的商品:\n";
    OutData(); //展示所有商品
    int p;
    cout<<"[1]继续购买"<<endl<<"[2]单纯看看，下次再买"<<endl;
    cin>>p;

    if(p==1)  {
        do {
            OutData();//展示所有商品
            cout<<"请输入您要购买的商品序号:";
            cin>>num;
            while((num<1)||(num>(int)items.size())) {
                cout<<"请重新输入正确的商品序号:";
                cin>>num;
            }
            num--;

            cout<<"请输入您要购买商品的数量:";
            cin>>qty;
            while(qty<=0) {
                cout<<"请重新输入正确的购买数量:";
                cin>>qty;
            }

            amt=items[num]->price*qty;//计算总价
            if(player->GetMoney()<amt) {
                cout<<"购买失败！您没有足够的金币！请下次再来！"<<endl;
                cout<<"请选择："<<endl<<"[1]继续购买其它商品"<<endl<<"[2]退出"<<endl;
            } else {
                player->BuyItem(num,items[num]->attack,items[num]->defense,qty,amt);//给玩家加物资,扣钱
                cid=num;
                SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout<<"您已成功购买"<<items[num]->title<<"!"<<endl<<items[num]->info<<endl;
                ResetConsoleColor();
                cout<<"请选择："<<endl<<"[1]继续购买其它商品"<<endl<<"[2]退出"<<endl;
            }
            cin>>ind;
        } while(ind==1);
    }

    return;
}

//展示商品函数
void Item::OutData() {
    const int idWidth = 15;
    const int titleWidth = 23;
    const int valueWidth = 15;
    const int levelWidth = 15;
    const int priceWidth = 15;

    cout << left;
    cout << setw(idWidth) << "<商品编号>"
         << setw(titleWidth) << "<商品名称>"
         << setw(valueWidth) << "<提升攻击值>"
         << setw(valueWidth) << "<提升防御值>"
         << setw(levelWidth) << "<商品等级>"
         << setw(priceWidth) << "<商品售价>" << endl;
    for(int i=0; i<93; i++) {
        cout<<"-";
    }
    cout<<endl;
    int n=items.size();
    for (int i=0; i<n; i++) {
        cout << setw(idWidth) << i+1 << setw(titleWidth) << items[i]->title
             << setw(valueWidth) << items[i]->attack << setw(valueWidth) << items[i]->defense
             << setw(levelWidth) << items[i]->itemLevel <<setw(priceWidth) <<items[i]->price<< endl;
    }
    cout<<endl;
    return;
}

//初始化、触发类功能
void Item::StaAction() {
    player = mudGame.getPlayer();
    if(dataFile.size()>0) LoadData();
    return;
}

//释放数据
void Item::EndAction() {
    for(int i=0; i<(int)items.size(); i++) delete items[i];
    return;
}

int Item::Getid(const string& scode) {
    return GetidT(items,scode);
}

//展示玩家背包的物资
void Item::Package() {
    const int idWidth = 15;
    const int nameWidth = 23;
    const int attackWidth = 15;
    const int defenseWidth = 15;
    const int levelWidth = 15;
    const int numWidth = 15;

    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << left; // 设置左对齐
    cout << setw(idWidth) << "<商品编号>"
         << setw(nameWidth) << "<商品名称>"
         << setw(attackWidth) << "<提升攻击值>"
         << setw(defenseWidth) << "<提升防御值>"
         << setw(levelWidth) << "<商品等级>"
         <<setw(numWidth) << "<库存数量>"<< endl;
    for(int i=0; i<93; i++) {
        cout<<"-";
    }
    ResetConsoleColor();
    cout<<endl;
    for (int i = 0; i < (int)items.size(); i++) {
        if (player->GetHasItems(i)!=0) { // 检查是否为空指针
            cout << setw(idWidth) << items[i]->code
                 << setw(nameWidth) << items[i]->title
                 << setw(attackWidth) << items[i]->attack
                 << setw(defenseWidth) << items[i]->defense
                 << setw(levelWidth) << items[i]->itemLevel
                 << setw(numWidth) << player->GetHasItems(i)<< endl;
        }
    }
    cout<<endl;
    return;
}

//打斗中使用物资
void Item::UseItem(int index) {
    player->SubHasItems(index);
    player->AddAttack(items[index]->attack);
    player->AddDefense(items[index]->defense);
    SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<items[index]->info<<endl<<"您已成功装备"<<items[index]->title<<"!"<<endl;
    ResetConsoleColor();
}

