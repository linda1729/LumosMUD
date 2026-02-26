#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "Player.h"
#include "Map.h"
#include "MudGame.h"

using namespace std;

//字体效果
void SetConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void ResetConsoleColor() {
    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 默认白色
}

void printCharByChar(const string& text, int delayMs) {
    for (char c : text) {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
}

//全局中控初始化
MudGame mudGame;

//主函数
int main() {
    system("mode con cols=150 lines=50");
    mudGame.mudMenu(); //菜单
    return 0;
}


//菜单
int MudGame::mudMenu() {
    int ch;
    mudInit();  //初始化数据、显示欢迎界面
    BeforeG();  //注册、登录

    //打印菜单
    do {
        cout << endl;
        cout << ">>>游戏菜单: " << endl;
        SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "   游戏概览> 1)游戏规则      2)魔法世界地图" << endl;
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "   游戏情景> 3)魁地奇场      4)禁林" << endl;   //魁地奇场（躲避球游戏）、禁林（打怪游戏）
        cout << "             5)霍格沃茨      6)对角巷"<< endl;  //霍格沃茨（学校学习技能）、对角巷（商店买商品/物资）
        cout << "             7)圣芒戈医院"<< endl;  //圣芒戈医院（提升血值）
        SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "   个人界面> 8)背包          9)拥有技能"<< endl;
        cout << "             10)身份信息"<<endl;
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE);
        cout << "   游戏设置> 0)退出游戏并保存" << endl; //每次需要正常按0退出才能保存数据
        ResetConsoleColor();
        cout << "   温馨提示：正常按0退出才能保存数据！"<<endl;
        cout << ">>请选择[0~10]: ";
        cin  >> ch;
        system("CLS");

        switch(ch) {
        case 0:
            break;
        case 1:
            amap->Display(dataPath("intro.dat"));
            break;
        case 2:
            amap->Display(dataPath("amaps.dat"));
            break;
        case 3: {
            int tindex;
            string intr = "\n欢迎来到<魁地奇球场>！\n"
                          ">>>你可以通过[W][S][A][D]四个键来控制你【P】的位置\n"
                          ">>>当你【P】追上金色飞贼【G】时--->游戏成功结束\n"
                          ">>>若你【P】不慎撞到障碍墙--->游戏失败\n"
                          ">>>成功用时越短，奖励越丰厚哦！\n";
            string prompt = "是否立即开始游戏？\n"
                            "[1]是\n"
                            "[2]下次再来\n";
            printCharByChar(intr, 5);
            SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printCharByChar(prompt, 5);
            ResetConsoleColor();
            cin>>tindex;
            if(tindex==1) {
                //开始躲避球游戏
                double result =field->Play();
                //游戏失败
                if(result<=0) {
                    cout<<"很遗憾！没有获得奖励！"<<endl;
                }
                //游戏成功，按照用时分配奖励
                else if(result<=10&&result>0) {
                    player->AddMoney(30);
                    player->AddExPoint(100);
                    cout<<"用时"<<result<<"秒！"<<endl;
                    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    cout<<"获得30金币和100经验点！"<<endl;
                    ResetConsoleColor();
                } else if(result<=20&&result>10) {
                    player->AddMoney(20);
                    player->AddExPoint(50);
                    cout<<"用时"<<result<<"秒！"<<endl;
                    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    cout<<"获得20金币和50经验点！"<<endl;
                    ResetConsoleColor();
                } else {
                    player->AddMoney(10);
                    player->AddExPoint(50);
                    cout<<"用时"<<result<<"秒！"<<endl;
                    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    cout<<"获得10金币和30经验点！"<<endl;
                    ResetConsoleColor();
                }
            }
            break;
        }

        case 4: {
            string text = "欢迎来到<禁林>!\n"
                          ">>>在这里，你需要通过按键[W][S][A][D]来移动自己[*]并探索迷宫。\n"
                          ">>>你会遇到<怪物>，也会遇见<宝藏>\n"
                          ">>>当然，善于伪装的怪物们[0]和宝藏[0]看起来没有什么区别\n"
                          ">>>所以在打开宝箱前先想一想自己有没有能力击败怪物\n"
                          ">>>有些怪物手里可能会有强大的<死亡圣器>\n"
                          ">>>得到它们会让你更接近你的目标\n"
                          ">>>加油，开启你的探索吧......\n";
            int tindex=0;
            string prompt = "是否立即开始游戏？\n"
                            "[1]是\n"
                            "[2]下次再来\n";
            printCharByChar(text, 5);
            SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printCharByChar(prompt, 5);
            ResetConsoleColor();
            cin>>tindex;

            if(tindex==1) {
                SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout<<endl<<"提示:按[P]可返回<游戏菜单>"<<endl;
                Sleep(2500);
                ResetConsoleColor();
                //检测玩家是中途退出游戏还是赢得游戏
                if(mapForest()==1) {
                    //玩家赢得游戏
                }
            }
            break;
        }

        case 5:
            skill->InpData();
            break;

        case 6:
            item->InpData();
            break;

        case 7:
            player->Hospital();
            break;

        case 8:
            item->Package();
            break;

        case 9:
            skill->ShowMySkills();
            break;

        case 10:
            player->OutData();
            break;

        default:
            break;

        }

        cin.ignore(); //清除键盘输入多余字符
    } while(ch>0 && ch<=10);

    mudStop();  //终止运行处理

    return 0;
}

void MudGame::mudInit() {
    //初始化系统数据
    player = new Player(dataPath("players.dat"));
    amap    = new Amap(dataPath("amaps.dat"));
    skill  = new Skill(dataPath("skills.dat"));
    item   = new Item(dataPath("items.dat"));
    monster= new Monster(dataPath("monsters.dat"));
    fight  = new Fight();
    field  = new Field();

    player->StaAction();
    amap->StaAction();
    skill->StaAction();
    item->StaAction();
    monster->StaAction();

    //打印欢迎界面
    Printtitle();
    Printword();
}

//结束游戏释放内存
void MudGame::mudStop() {
    amap->EndAction();
    skill->EndAction();
    item->EndAction();
    monster->EndAction();
    player->EndAction();

//   delete amap;
//   delete skill;
//   delete item;
//   delete monster;
//   delete player;

    delete field;
    delete fight;
}

Player * MudGame::getPlayer() {
    return player;
}

Item * MudGame::getItem() {
    return item;
}

Skill * MudGame::getSkill() {
    return skill;
}

Amap * MudGame::getAmap() {
    return amap;
}

Fight * MudGame::getFight() {
    return fight;
}

Monster * MudGame::getMonster() {
    return monster;
}

//注册、登录
void MudGame::BeforeG() {
    int  choice=0;
    char tcode[40];
    char tname[40];
    char tpwd[40];
    int  thouse;
    vector<Players *> tplayer;
    tplayer = player->getPlayers();

    while(1) {
        cout<<endl<<"欢迎你来到魔法世界！"<<endl;
        cout<<"[1]新用户注册"<<endl<<"[2]登录游戏"<<endl;
        cin>>choice;
        if(choice!=1) break;

        cout<<"请输入你的<账号名>，下次进入魔法世界你会需要用到它的！"<<endl;
        cin>>tcode;
        //注册时检查是否出现重名
        while(player->CheckPlayer(tcode)) {
            cout<<"很抱歉！该<账号名>已注册！请重新输入："<<endl;
            cin>>tcode;
        }
        cout<<"请输入魔法世界的<游戏名>: "<<endl;
        cin>>tname;
        cout<<"输入你的<密码>："<<endl;
        cin>>tpwd;
        cout <<"请为自己选择一个<学院>吧！谨慎选择哦！"<<endl;
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY); // 红色
        cout << "[1]格兰芬多:在火焰的炽热中铸就勇气，狮心之地，诞生着无畏的战士与梦想的勇士。" << endl;
        SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY); // 绿色
        cout << "[2]斯莱特林:在深邃的水域中潜藏野心，蛇之秘境，培养着精明的领袖与策略家的摇篮。" << endl;
        SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY); // 蓝色
        cout << "[3]拉文克劳:翱翔于智慧的风暴之巅，鹰之巢穴，汇聚着睿智的学者与探索未知的先驱。" << endl;
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN); // 黄色
        cout << "[4]赫奇帕奇:于大地的怀抱中耕耘忠诚，獾之家园，孕育着不懈的努力与勤勉的守护着。" << endl;
        ResetConsoleColor();
        cin >> thouse;
        player->SignData(tcode,tname,tpwd,thouse);
        cout<<"注册完毕！现在就开启你的魔法之旅吧！"<<endl;
    }

    while(1) {
        cout<<"请输入你的<账号名>:";
        cin>>tcode;
        //登录时检查是否存在该用户
        while(!(player->CheckPlayer(tcode))) {
            cout<<"不存在该用户！请重输你的<账号名>:";
            cin>>tcode;
        }
        cout<<"请输入你的<密码>:";
        cin>>tpwd;
        //匹配密码
        if(player->Login(tcode,tpwd)) break;
        cout<<"密码错误,请重新输入!"<<endl;
    }
    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout <<"登录成功！欢迎再次来到魔法世界！"<<endl;
    //继续游戏（存档）或者新开游戏
    cout <<"[1]继续游戏"<<endl<<"[2]新开游戏"<<endl;
    ResetConsoleColor();
    cin >> choice;
    if(choice==2) {
        cout <<"请为魔法世界的自己取一个<游戏名>吧！"<<endl;
        cin >> tname;
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY); // 红色
        cout << "[1]格兰芬多:在火焰的炽热中铸就勇气，狮心之地，诞生着无畏的战士与梦想的勇士。" << endl;
        SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY); // 绿色
        cout << "[2]斯莱特林:在深邃的水域中潜藏野心，蛇之秘境，培养着精明的领袖与策略家的摇篮。" << endl;
        SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY); // 蓝色
        cout << "[3]拉文克劳:翱翔于智慧的风暴之巅，鹰之巢穴，汇聚着睿智的学者与探索未知的先驱。" << endl;
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN); // 黄色
        cout << "[4]赫奇帕奇:于大地的怀抱中耕耘忠诚，獾之家园，孕育着不懈的努力与勤勉的守护着。" << endl;
        ResetConsoleColor();
        cin >> thouse;
        player->NewData(tname,thouse);
        cout<<"新的游戏已开启！"<<endl;
    }
    player->setCid(player->GetidT<Players>(tplayer,tcode));
}

//打印欢迎界面
void MudGame::Printword() {
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    ifstream iff(dataPath("intro.dat"));
    if (!iff.is_open()) {
        cout << "无法打开文件" << endl;
        return;
    }
    string buffer;
    bool skip = false;
    cout << "按下" << color() << "[Tab]" << "\033[0m" << "跳过本段" << "\033[0m" << endl;
    while (getline(iff, buffer) && !skip) {
        for (int i = 0; i < buffer.length(); ++i) {
            if (_kbhit() && _getch() == '\t') { //按下tab跳过
                skip = true;
                break;
            }
            if (!skip) {
                if (buffer[i] == '<') {
                    cout << color() << buffer[i] ;
                    Sleep(20);
                } else if (buffer[i] == '>') {
                    cout  << buffer[i] << "\033[0m";
                    Sleep(20);
                } else cout << buffer[i];
                Sleep(20);
            }
        }
        cout << endl;
    }
    iff.close();
}

//打印游戏logo
void MudGame::Printtitle() {
    //srand(unsigned(time(nullptr)));
    ifstream iff(dataPath("logo.dat"));
    if (!iff.is_open()) {
        cout << "无法打开文件" << endl;
        return;
    }
    string buffer;
    while (getline(iff, buffer)) {
        Sleep(100);
        cout << color() << buffer << "\033[0m" << endl;
    }
    iff.close();
}

//打印游戏通关界面
void MudGame::Printend() {
    //srand(unsigned(time(nullptr)));
    ifstream iff(dataPath("over.dat"));
    if (!iff.is_open()) {
        cout << "无法打开文件" << endl;
        return;
    }
    string buffer;
    while (getline(iff, buffer)) {
        Sleep(100);
        cout << color() << buffer << "\033[0m" << endl;
    }
    iff.close();
}

//设置颜色
string MudGame::color() {
    int n = rand() % 6 + 31;
    return "\033[" + to_string(n) + "m";
}

string MudGame::backcolor() {
    int n = rand() % 6 + 40;
    return "\033[" + to_string(n) + "m";
}

string MudGame::dataPath(const string& filename) const {
    const string base = "data/";
    if (filename.rfind(base, 0) == 0) {
        return filename;
    }
    return base + filename;
}
