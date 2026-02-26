#ifndef HEADER_B680A5854ACF1D3E
#define HEADER_B680A5854ACF1D3E
//虚基类MudBase（衍生类：玩家Player、商品/物资Item、怪兽Monster、技能Skill、图片Amap）
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class MudBase {
public:

//Template：为MudBase衍生出的类code转id
//对数据使用字符编号能让后期数据更丰富
    template <typename T>
    int GetidT(vector<T *>& vec, const string& code) {
        int i, n;

        n = vec.size();
        for(i=0; i<n; i++)
            if(code.compare(vec[i]->code)==0) break;

        return i;
    }

//Template：对Player类数据定位
    template <typename T>
    int GetidT(vector<T *>& vec, const char* code) {
        int i, n;

        n = vec.size();
        for(i=0; i<n; i++)
            if(strcmp(code,vec[i]->code)==0) break;

        return i;
    }

//Template：LoadData
    template <typename T>
    void LoadDataT(vector<T *>& vec, const string& dfile) {
        T *stru;

        if (dfile.size()<1) return;
        ifstream infile(dfile,ios::binary);
        if(!infile.is_open()) {
            cout<< "Open error["<<dfile<<"]!"<<endl;
            return;
        }
        while (!infile.eof()) {
            stru = new T;
            infile.read((char*)stru, sizeof(T));
            vec.push_back(stru);
            if(infile.peek()==EOF) break;
        }
        infile.close();
        return;
    }

//Template: SaveData
    template <typename T>
    void SaveDataT(vector<T *>& vec, const string& dfile) {
        T *stru;
        int i,n;

        if (dfile.size()<1) return;
        ofstream outfile(dfile,ios::binary);
        if(!outfile.is_open()) {
            cout<< "Open error["<<dfile<<"]!"<<endl;
            return;
        }

        n = vec.size();
        for(i=0; i<n; i++) {
            stru = vec[i];
            outfile.write((char*)stru, sizeof(T));
        }
        outfile.close();
        return;
    }

    MudBase();
    MudBase(const string& dFile);
    ~MudBase();
    int getCid(); //获取编号
    void setCid(int newCid);
    string getDataFile();
    void setDataFile(const string& newDataFile);
    int Getid(const string& scode);

    virtual void LoadData()=0; //导入
    virtual void SaveData()=0; //保存
    virtual void InpData()=0;  //写数据
    virtual void OutData()=0;  //展示数据
    virtual void StaAction()=0; //导入，触发类的使用
    virtual void EndAction()=0; //释放内存，结束类的使用

    string dataFile;
    int cid=0;  //编号
};




#endif // header guard

