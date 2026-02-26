#ifndef HEADER_21102D0C14FC273
#define HEADER_21102D0C14FC273
//该类用于管理项目中的图片（实际上是dat数据）
#include <iostream>
#include <string>
#include <vector>

#include "MudBase.h"

using namespace std;

struct Amaps {
    string code;   //编号
    string data;   //图片数据
};

class Amap : public MudBase {
public:
    using MudBase::MudBase;

    vector<struct Amaps *> getAmaps();
    void setAmaps(vector<struct Amaps *> newAmaps);
    void LoadData() override;
    void SaveData() override;
    void InpData() override;
    void OutData() override;
    void StaAction() override;
    void EndAction() override;
    int Getid(const string& scode);
    void Display(const string& scode);

protected:
    vector<struct Amaps *> amaps;

};

#endif // header guard

