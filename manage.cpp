#include "manage.h"

void Manage::ReadFile()
{
     ifstream fin;
     fin.open("../weChatData.txt");
     if (!fin.is_open())
         printf("文件打开失败");
     else
     {
         ListLen = 0;
         int i = 0;
         for (i = 0; !fin.eof(); i++)
         {
             string s;
             getline(fin, s);//读一行
             stringstream ss(s);//把字符串转换为流
             string temp;
             ss >> temp;
             GroupList[i].Group_Name = temp;
             ss >> temp;
             int num = atoi(temp.c_str());
             GroupList[i].Person_Num = num;
             for (int j = 0; j<num; j++)
             {
                 ss >> temp;
                 GroupList[i].Person.push_back(temp);//存用户
             }
             ss >> temp;
             GroupList[i].times += temp;
             GroupList[i].year = atoi(temp.c_str());//存年

             ss >> temp;
             GroupList[i].times += ' ' + temp;
             GroupList[i].month = atoi(temp.c_str());//存月

             ss >> temp;
             GroupList[i].times += ' ' + temp;
             GroupList[i].date = atoi(temp.c_str());//读日

         }
         fin.close();
         ListLen = i;
     }
}
void Manage::Get_idx()
{
    user_idx = 0;
    int i = 0;
    ifstream fin("../weChatData.txt");
    if (fin.is_open())
       {
           while (!fin.eof())
           {
                WeChatGroup temp;
                string s;
                getline(fin, s);//读一行
                stringstream ss(s);//把string送入流中
                ss >> temp.Group_Name >> temp.Person_Num;
                for (int j = 0; j < temp.Person_Num; j++)
                {
                    string name;
                    ss >> name;
                    temp.Person.push_back(name);
                    //实现用户与下标一一对应
                    if (userTonum.find(name) == userTonum.end())//这个用户还没有被映射
                    {
                        userTonum[name] = user_idx;
                        numTouser[user_idx++] = name;
                    }
                }
                int year, month, date;
                ss >> year >> month >> date;
                temp.year = year; temp.month = month; temp.date = date;
                if (temp.Person_Num)
                    GroupList[i++] = temp;
            }
            ListLen = i;
        }
        fin.close();
}
void Manage::Creat_Hash()
{
    for(int i=0;i<user_idx;i++)
    {
        Hash[i]=new LNode;
        Hash[i]->next = NULL;
    }
    for (int i = 0; i < ListLen; i++)
       {//从第一个群开始
           for (vector<string>::const_iterator it = GroupList[i].Person.begin(); it != GroupList[i].Person.end(); it++)
              {
                int idx = userTonum[*it];//由人名确定是存入哪一个链表中
                LinkList p = Hash[idx];
               //头插法插入群名
                LinkList t_node = new LNode;
                t_node->node_value = GroupList[i].Group_Name;//存入群名
                t_node->next = p->next;
                p->next = t_node;
                }
       }
}
void Manage::Floyd()
{
        int i = 0;
        int j = 0;
        int k = 0;

        for (i = 0; i<971; i++)
            for (j = 0; j < 971; j++)
            {
                D[i][j] = G[i][j].val;
                Path[i][j] = j;
            }
        for (k = 0; k<971; k++)
            for (i = 0; i<971; i++)
                for (j = 0; j < 971; j++)
                {
                    if (D[i][k] + D[k][j] < D[i][j])
                    {
                        D[i][j] = D[i][k] + D[k][j];             
                        Path[i][j] = Path[i][k];
                    }
                }
}
