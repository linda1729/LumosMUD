#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>

#include "MudBase.h"
#include "Monster.h"
#include "MudGame.h"

using namespace std;

extern MudGame mudGame;

vector<struct Monsters *> Monster::getMonsters() {
    return monsters;
}

void Monster::setMonsters(vector<struct Monsters *> newMonsters) {
    monsters = newMonsters;
}

void Monster::LoadData() {
    //文本数据读取
    string data;
    string text;
    string word;
    struct Monsters *st;
    ifstream infile(dataFile,ios::in);

    if(!infile) {
        cout<< "Open error["<<dataFile<<"]!"<<endl;
        return;
    }
    while(infile.peek()!=EOF) {
        getline(infile,data);
        st = new Monsters();
        stringstream iss(data);
        iss>>st->code>>st->title>>st->moHP>>st->damage>>st->info;
        iss.clear();
        monsters.push_back(st);

    }
    infile.close();
    return;
}

void Monster::SaveData() {
    return;
}

void Monster::InpData() {
    return;
}

void Monster::OutData() {
    return;
}

void Monster::StaAction() {
    if(dataFile.size()>0) LoadData();
    return;
}

void Monster::EndAction() {
    for(int i=0; i<(int)monsters.size(); i++) delete monsters[i];
    return;
}

void Monster::Setid(int num) {
    cid = num;
}

int Monster::Getid(const string& scode) {
    return GetidT(monsters,scode);
}

int Monster::GetHP() {
    return monsters[cid]->moHP;
}

int Monster::GetDamage() {
    return monsters[cid]->damage;
}

string Monster::GetName() {
    return monsters[cid]->title;
}

string Monster::GetInfo() {
    return monsters[cid]->info;
}

void Monster::ShowInfo() {
    cout<<endl<<monsters[cid]->title;
    cout<<monsters[cid]->info<<endl;
}

void Monster::Speak() {
    srand(unsigned(time(nullptr)));
    int n=rand()%words.size();
    cout<<words[n];
}

void Monster::BeAttack(int bedamage) {
    monsters[cid]->moHP-=bedamage;
}


