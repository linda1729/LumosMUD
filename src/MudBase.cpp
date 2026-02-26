#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "MudBase.h"

using namespace std;

MudBase::MudBase() {
    cid = 0;
    dataFile = "";
}

MudBase::MudBase(const string& dFile) {
    cid = 0;
    dataFile = dFile;
}

MudBase::~MudBase() {
}

int MudBase::getCid() {
    return cid;
}

void MudBase::setCid(int newCid) {
    cid = newCid;
}

string MudBase::getDataFile() {
    return dataFile;
}

void MudBase::setDataFile(const string& newDataFile) {
    dataFile = newDataFile;
}

int MudBase::Getid(const string& scode) {
    string s=scode;
    return 0;
}
