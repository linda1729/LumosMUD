#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#include "Player.h"
#include "Skill.h"
#include "MudGame.h"

using namespace std;
extern MudGame mudGame;

extern SetConsoleColor(WORD color);
extern ResetConsoleColor();
extern printCharByChar(const string& text, int delayMs);

vector<struct Skills *> Skill::getSkills() {
    return skills;
}

void Skill::setSkills(vector<struct Skills *> newSkills) {
    skills = newSkills;
}

void Skill::LoadData() {
    //文本数据读取
    string data;
    struct Skills *st;

    ifstream infile(dataFile,ios::in);

    if(!infile) {
        cout<< "Open error["<<dataFile<<"]!"<<endl;
        return;
    }
    while(infile.peek()!=EOF) {
        getline(infile,data);
        st = new Skills();
        stringstream iss(data);   //文本格式，" "分隔
        iss>>st->code>>st->title>>st->skHP>>st->worth>>st->level>>st->info;
        iss.clear();
        skills.push_back(st);
    }
    infile.close();

    return;
}

void Skill::SaveData() {
    return;
}

void Skill::InpData() {
    int index=0;//是否继续学习技能的标识
    SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    string text = "欢迎踏入<霍格沃茨城堡>，这充满魔法与梦想的知识圣地！\n"
                  "在这里，你可以用<经验点>学习丰富的<咒语>。\n"
                  "快开启你的非凡的学习之旅，探索魔法的无限奥秘吧......\n\n";
    printCharByChar(text, 10);
    ResetConsoleColor();
    cout <<"你的经验值："<<player->GetExPoint()<<endl;
    cout<<"以下是你可以选择学习的咒语:\n";
    OutData();//展示所有技能
    int p;
    cout<<"[1]继续学习"<<endl<<"[2]单纯看看，下次再学"<<endl;
    cin>>p;
    if(p==1) {
        do {
            cout<<"以下是你可以选择学习的咒语:\n";
            OutData();//展示所有技能
            string code;
            int choice;//学习技能的序号
            cout<<"请输入您要学习的咒语序号:";
            cin>>code;
            choice=GetidT<Skills>(skills,code);
            while((choice<0)||choice>((int)skills.size())) {
                cout<<"请重新输入正确的咒语序号:";
                cin>>code;
                choice=GetidT<Skills>(skills,code);
            }
            while(player->GetHasSkills(choice)==1) {
                cout<<"您已学习过该咒语！请重新输入新的咒语序号:";
                cin>>code;
                choice=GetidT<Skills>(skills,code);
            }
            if(player->GetExPoint()<skills[choice]->worth) {
                cout<<"学习失败！经验值不足！请下次再来！"<<endl;
                cout<<"请选择："<<endl
                    <<"[1]尝试学习其它咒语"<<endl
                    <<"[2]退出"<<endl;
                cin>>index;
            } else {
                cout<<"学习成功！"<<endl;
                player->SubExPoint(skills[choice]->worth);//给玩家扣经验点
                player->AddHasSkills(choice);//给玩家标识咒语
                SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout<<"您已成功掌握"<<GetName(choice)<<"!"<<endl<<GetInfo(choice)<<endl;
                ResetConsoleColor();
                cout<<"请选择："<<endl
                    <<"[1]尝试学习其它咒语"<<endl
                    <<"[2]退出"<<endl;
                cin>>index;
            }
        } while(index==1);
    }
}

void Skill::OutData() {
    const int codeWidth = 14;
    const int nameWidth = 21;
    const int minHPWidth = 15;
    const int worthWidth = 19;
    const int levelWidth = 14;

    cout << left; // 设置左对齐
    cout << setw(codeWidth) << "<咒语编号>"
         << setw(nameWidth) << "<咒语名称>"
         << setw(minHPWidth) << "<杀伤值>"
         << setw(worthWidth) << "<学习所需经验点>"
         << setw(levelWidth) << "<咒语等级>"<<endl;

    for(int i=0; i<79; i++) {
        cout<<"-";
    }
    cout<<endl;

    for (int i = 0; i < (int)skills.size(); i++) {
        cout << setw(codeWidth) << skills[i]->code
             << setw(nameWidth) << skills[i]->title
             << setw(minHPWidth) << skills[i]->skHP
             << setw(worthWidth) << skills[i]->worth
             << setw(levelWidth) << skills[i]->level
             << endl;
    }

    cout<<endl;
    return;
}

void Skill::StaAction() {
    player = mudGame.getPlayer();

    if(dataFile.size()>0) LoadData();
    return;
}

void Skill::EndAction() {

    for(int i=0; i<(int)skills.size(); i++) delete skills[i];

    return;
}

int Skill::Getid(const string& scode) {
    return GetidT(skills,scode);
}

string Skill::GetCode(int index) {
    return skills[index]->code;
}

string Skill::GetName(int index) {
    return skills[index]->title;
}

int Skill::GetMinHP(int index) {
    return skills[index]->skHP;
}

int Skill::GetWorth(int index) {
    return skills[index]->worth;
}

int Skill::GetLevel(int index) {
    return skills[index]->level;
}

string Skill::GetInfo(int index) {
    return skills[index]->info;
}


void Skill::ShowMySkills() {
    const int codeWidth = 14;
    const int nameWidth = 21;
    const int minHPWidth = 15;
    const int levelWidth = 14;
    SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE);
    cout << left; // 设置左对齐
    cout << setw(codeWidth) << "<咒语编号>"
         << setw(nameWidth) << "<名称>"
         << setw(minHPWidth) << "<攻击血值>"
         << setw(levelWidth) << "<咒语等级>"<<endl;
    for(int i=0; i<(codeWidth + nameWidth + minHPWidth + levelWidth); i++) {
        cout<<"-";
    }
    ResetConsoleColor();
    cout<<endl;
    for (int i = 0; i < (int)skills.size(); i++) {
        if (player->GetHasSkills(i)!=0) { // 检查是否为空指针
            cout << setw(codeWidth) << skills[i]->code
                 << setw(nameWidth) << skills[i]->title
                 << setw(minHPWidth) << skills[i]->skHP
                 << setw(levelWidth) << skills[i]->level
                 << endl;
        }
    }

    cout<<endl;

    return;
}

