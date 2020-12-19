#ifndef MANAGE_H
#define MANAGE_H
#include<string>
#include<vector>
#include<map>
#include<fstream>
#include<sstream>
#include<QDebug>
#include"data.h"
#include"hash.h"
#define MAXN 1500
//#define maxn 1500
#define maxn2 1500
using namespace std;
typedef struct GNode
{
    double val;
    vector<string> name;
}Graph;
class Manage
{
public:
    WeChatGroup GroupList[500];
    int ListLen;
    Graph G[1000][1000];//邻接矩阵
    void ReadFile();
    void Floyd();//弗洛伊德算法
    void Get_idx();//得到一一映射
    void Creat_Hash();//创建哈希表
    int Path[1000][1000];
    double D[1000][1000];
    int user_idx;//用户下标
    LinkList Hash[1500];//先把用户链表数组开大点

    //利用map把用户的下标和名称一一映射
    map<string, int>  userTonum;//以名称为key，下标为value
    string *numTouser=new string[1500];//通过下标找到用户
    int map_idx;//无重复的用户人数,经测试为971人

};

#endif // MANAGE_H
