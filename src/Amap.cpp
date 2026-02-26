#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <chrono>

#include "Player.h"
#include "Fight.h"
#include "MudBase.h"
#include "Amap.h"
#include "MudGame.h"

using namespace std;
extern MudGame mudGame;

vector<struct Amaps *> Amap::getAmaps() {
    return amaps;
}

void Amap::setAmaps(vector<struct Amaps *> newAmaps) {
    amaps = newAmaps;
}

void Amap::LoadData() {
    //文本数据读取
    struct Amaps *st;
    stringstream buffer;

    ifstream infile(dataFile,ios::in);
    if(!infile) {
        cout<< "Open error["<<dataFile<<"]!"<<endl;
        return;
    }
    buffer<<infile.rdbuf();
    infile.close();

    st = new Amaps();
    st->code = dataFile;
    st->data = buffer.str();
    amaps.push_back(st);
    buffer.clear();

    return;
}

void Amap::SaveData() {
    return;
}

void Amap::InpData() {
    return;
}

//显示数据
void Amap::OutData() {
    int n=amaps.size();
    if ((cid<0)||(cid>=n)) return;
    cout << endl << amaps[cid]->data << endl;
    return;
}

//触发类的使用，读取文件
void Amap::StaAction() {
    if(dataFile.size()>0) LoadData();
    return;
}

//结束类的使用，释放空间
void Amap::EndAction() {
    for(int i=0; i<(int)amaps.size(); i++) delete amaps[i];
    return;
}

//重载，转换code为遍历id
int Amap::Getid(const string& scode) {
    return GetidT(amaps,scode);
}


void Amap::Display(const string& scode) {
    int m, n;
    // 通过 Getid 方法获取与 scode 对应的文件序号（在 amaps 向量中的索引）
    n = Getid(scode);
    // 获取 amaps 向量的大小
    m = amaps.size();
    // 如果文件序号 n 等于 amaps 向量的大小 m，这意味着 scode 对应的数据尚未加载到 amaps 中
    // 因此，我们需要设置数据文件，并调用 LoadData 方法来加载数据
    if (m == n) {
        setDataFile(scode); // 设置数据文件
        LoadData();         // 加载数据
    }

    // 设置当前要显示的图片数据的索引（cid）为 n
    setCid(n);

    // 调用 OutData 方法来显示图片数据
    OutData();
}
