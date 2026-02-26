#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <ctime>
#include <cstdlib>

#include "Fight.h"
#include "MudGame.h"

using namespace std;

extern MudGame mudGame;

extern SetConsoleColor(WORD color);
extern ResetConsoleColor();
extern printCharByChar(const string& text, int delayMs);

Fight::Fight() {
    player = mudGame.getPlayer();
    monster= mudGame.getMonster();
    amap = mudGame.getAmap();
    item = mudGame.getItem();
    skill= mudGame.getSkill();
}

Fight::~Fight() {

}

//打斗函数，返回输赢结果
bool Fight::Battle() {
    int ind;
    string code;
    char ch,ch1;
    //复制已读取的数据
    vector<Items*>is=item->getItems();
    vector<Skills*>ss=skill->getSkills();
    //记录玩家本轮打斗前的满血值
    int initalhp=player->GetHP();
    //生成与玩家同级的怪兽并介绍怪兽信息
    monster->Setid(player->GetLevel());
    monster->ShowInfo();

    cout<<"—————————————战斗即将开始！——————————————"<<endl;
    cout<<"按[1]打开背包使用物品获得属性加成！（按任意字符跳过）"<<endl;
    cin>>ch1;
    if(ch1=='1') {
        //检查是否有物资
        if(player->CheckItems()>0) {
            do {
                //循环中检查是否有物资
                if(player->CheckItems()==0) {
                    cout<<"您的物资已经使用完毕！"<<endl;
                    break;
                }

                ind=0;
                cout<<"你的<背包>里有以下物资:"<<endl;
                item->Package();
                cout<<"请选择你想使用的物资:"<<endl;
                cin>>code;
                ind=item->GetidT<Items>(is,code);
                while(ind<0||ind>((int)is.size())||(player->GetHasItems(ind)==0)) {
                    cout<<"输入错误！请重新输入有效数字："<<endl;
                    cin>>code;
                    ind=item->GetidT<Items>(is,code);
                }
                //使用物资：加攻击、防御值、扣物资数
                item->UseItem(ind);
                cout<<endl<<"是否继续添加物资？"<<endl<<"[1]继续添加"<<endl<<"[2]选择完毕"<<endl;
                cin>>ch;
            } while(ch=='1');
        } else {
            cout<< "对不起！你尚未拥有任何物资。"<<endl<<endl;
        }
    }

    cout<<"战斗开始！！！"<<endl;
    //双方血量大于0则一直战斗
    while(monster->GetHP()>0&&player->GetHP()>0) {

        //玩家回合
        cout<<"现在是你的回合！请出招: "<<endl;
        //没有技能，发动物理攻击
        if(player->CheckSkill()==0) {
            cout<<"你尚未掌握任何咒语！只能发动物理攻击！"<<endl;
            player->Speak();
            int newdamage=0;
            newdamage=(1+(player->GetAttack())/100)*5;//普通攻击的基础伤害固定为5
            cout<<"你的物理攻击对怪兽造成了"<<newdamage<<"伤害！"<<endl;
            monster->BeAttack(newdamage);//扣怪物血值
            cout<<"怪物还剩"<<monster->GetHP()<<"滴血"<<endl;
            Sleep(500);
        }
        //有技能，选择技能进行攻击
        else {
            int p=0;
            skill->ShowMySkills();//显示已经拥有的技能
            cout<<"选择你要释放的咒语:";
            cin>>code;
            p=skill->GetidT<Skills>(ss,code);
            while(p<0||p>((int)ss.size())||(player->GetHasSkills(p)==0)) {
                cout<<"输入错误！请重新输入有效数字："<<endl;
                cin>>code;
                p=skill->GetidT<Skills>(ss,code);
            }
            //对怪兽扣血
            int newdamage=0;
            newdamage=(1+(player->GetAttack())/100)*(skill->GetMinHP(p));
            cout<<"你："<<skill->GetInfo(p)<<endl
                <<"你对怪兽造成了"<<newdamage<<"血伤害！"<<endl;
            monster->BeAttack(newdamage);
            cout<<"怪物还剩"<<monster->GetHP()<<"滴血"<<endl<<endl;
            Sleep(500);
            //判断玩家回合中怪兽是否被打败
            if(monster->GetHP()<=0) {
                cout<<monster->GetName()<<"被你打败了！你获得胜利！"<<endl;
                //判断特殊点
                if(player->GetLevel()==3) {
                    cout<<"恭喜你获得<死亡圣器>之<隐身衣>"<<endl;
                }
                if(player->GetLevel()==6) {
                    cout<<"恭喜你获得<死亡圣器>之<复活石>"<<endl;
                }
                if(player->GetLevel()==9) {
                    cout<<"恭喜你获得<死亡圣器>之<老魔杖>"<<endl;
                    Sleep(500);
                    mudGame.Printend(); //成功通关，打印标识
                    Sleep(2000);
                }
                //打怪成功，掉落奖励（加数据并显示）
                player->WinFight();
                break;
            }
        }


        //怪兽回合
        int newMdamage=0;
        newMdamage=(1-(player->GetDefense())/100)*(monster->GetDamage());
        cout<<monster->GetName()<<":";
        monster->Speak();//怪兽台词
        cout<<endl<<monster->GetName()<<"发动攻击！对你造成了"<<newMdamage<<"伤害！"<<endl;
        player->SubHP(newMdamage);
        cout<<"你还剩"<<player->GetHP()<<"滴血"<<endl;
        //判断怪兽回合中玩家是否被击败
        if(player->GetHP()<=0) {
            cout<<"很遗憾，你被"<<monster->GetName()<<"打败了！"<<endl;
            break;
        }
    }


    //确认战斗结果
    char endback;
    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout<<endl<<"按<任意字符>确认战斗结果并返回地图。"<<endl;
    ResetConsoleColor();
    cin >>endback;

    //根据战斗结果为玩家回血
    if (monster->GetHP()<=0) {
        player->SetHP(initalhp+(player->GetLevel()-1)*60);
        return true;
    }
    if(player->GetHP()<=0) {
        player->SetHP(initalhp);
        return false;
    }
}

//地图中的奖励点
void Fight::Reward() {
    int n=(rand()%60)+20;
    player->SetMoney(n);
    cout << "获得"<<n<<"金币"<< endl;
    int m=(rand()%70)+80;
    player->SetExPoint(m);
    cout << "获得"<<m<<"经验" << endl;
    Sleep(2000);
}
