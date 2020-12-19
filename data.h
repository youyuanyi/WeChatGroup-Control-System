#ifndef DATA_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<sstream>
#include<cstdlib>
#include<algorithm>

using namespace std;
#define DATA_H
typedef struct{
    string Group_Name;//群名
    int Person_Num;//群人数
    vector<string>Person;//用vector存一个群的群用户
    int year;//年
    int month;//月
    int date;//日
    string times;//string型的时间,"2013 01 01"这样
    string owner;//群主
    string type;//类型
}WeChatGroup;


#endif // DATA_H
