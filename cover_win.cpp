#include "cover_win.h"
#include<QFile>
#include<QDebug>
Cover_Win::Cover_Win(QWidget *parent) : QWidget(parent)
{
    this->resize(1400,1100);
    this->setWindowTitle("群覆盖");
    out_btn=new QPushButton(this);
    out_btn->setText("回退");
    out_btn->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
    out_btn->setGeometry(50,150,150,30);
    out_btn->show();
    connect(out_btn,&QPushButton::clicked,this,&Cover_Win::SendSlot);

    title=new QLabel(this);
    title->setText("  微信群管理系统");
    title->setGeometry(this->width()/2-100,30,350,30);
    title->setStyleSheet("QLabel{font-size:28px;color:white;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    title->show();


    front_title=new QLabel(this);
    front_title->setText("   前端服务系统");
    front_title->setGeometry(this->width()/2-100,70,350,30);
    front_title->setStyleSheet("QLabel{font-size:28px;color:white;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    front_title->show();

    fun_title=new QLabel(this);
    fun_title->setText("       群覆盖");
    fun_title->setGeometry(this->width()/2-100,110,350,30);
    fun_title->setStyleSheet("QLabel{font-size:28px;color:white;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    fun_title->show();
    GroupList=new WeChatGroup[500];

    edit=new QTextEdit(this);
    edit->setGeometry(230,150,1000,600);
    edit->show();

    cover_btn=new QPushButton(this);
    cover_btn->setText("覆盖");
    cover_btn->setGeometry(50,210,150,30);
    cover_btn->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
    cover_btn->show();

    search_btn=new QLineEdit(this);
    search_btn->setGeometry(50,270,150,30);
    search_btn->show();
    connect(cover_btn,&QPushButton::clicked,this,&Cover_Win::Show);

    btn=new QPushButton(this);
    btn->setGeometry(50,330,150,30);
    btn->setText("搜索");
    btn->show();
    connect(btn,&QPushButton::clicked,this,&Cover_Win::search);

    ans=new QLineEdit(this);
    ans->setGeometry(50,360,150,30);
    ans->show();
}
//群覆盖
int p[MAXN];//存放每个用户的群主
int p_size[MAXN];//存放覆盖后每个群的人数

//利用map把用户的下标和名称一一映射
map<string, int>  userTonum;//以名称为key，下标为value
string numTouser[MAXN];//通过下标找到用户
int map_idx;//无重复人数
void Cover_Win::SendSlot()
{
    emit CoverToFront();
}
int Cover_Win::find(int x)
{//find函数用来找群主
       if (x == p[x]) //找到群主，返回
            return x;
        else
        {
            p[x] = find(p[x]);//递归找到x的根结点
            return p[x];
        }
}
void Cover_Win::Merge()
{
        //初始化,一开始每个用户都设置为自己是群主,且群里只有自己一个人
        for (int i = 0; i < MAXN; i++)
        {
            p[i] = i;
            p_size[i] = 1;
        }
        map_idx = 0;//设置用户下标从0开始
        //遍历所有的群
        ifstream fin("../weChatData.txt");
        if (fin.is_open())
        {
            while (!fin.eof())
            {
                int i = 0;
                WeChatGroup temp_group;//每次遍历一个群
                string s;
                getline(fin, s);//读一行
                stringstream ss(s);//把string送入到流里
                ss >> temp_group.Group_Name >> temp_group.Person_Num;
                int g_num = temp_group.Person_Num;
                for (int j = 0; j < g_num; j++)
                {
                    string name;
                    ss >> name;
                    if (temp_group.Person.empty()) {
                        //群为空，把第一个人加进来当做群主
                        temp_group.owner = name;
                    }
                    temp_group.Person.push_back(name);//存入人名
                    //实现下标与名字一一映射
                    if (userTonum.find(name) == userTonum.end())//如果该用户没有被访问过
                    {
                        userTonum[name] = map_idx;
                        numTouser[map_idx++] = name;
                    }
                    //核心部分
                    int p1 = find(userTonum[name]);//因为用户下标唯一，所以能找到这个人原来的群主
                    int p2 = find(userTonum[temp_group.owner]);//找当前群的群主
                    if (p1 != p2)//两者属于不同的群;若此前p1加入过一个群，则把p1并到新的以p2为群主的群里
                    {
                        p[p1] = p2;//把p1合并到p2的群中,如果一个人之前已经在一个群中出现了，则把他的原群主归到p2的群中
                        p_size[p2] += p_size[p1];//群人数变化
                    }
                }
                int year, month, date;
                ss >> year >> month >> date;
                temp_group.year = year; temp_group.month = month; temp_group.date = date;
                if (temp_group.Person_Num!=0)
                {
                    GroupList[i] = temp_group;
                    i++;
                }
            }
        }
        fin.close();

}
void Cover_Win::Cover()
{
       int index = 1;
        //写入文件时不用管qt
        ofstream fout;
        fout.open("../weChatCoverData.txt");
        int v[MAXN] = { 0 };//所有用户假设未被访问
        for (int i = 0; i < map_idx; i++)
        {
            if (!v[i])//之前的遍历没有被加入到群中
            {
                int p_num = 1;//当前群人数,从1开始
                vector<string> Same_G_Username;//存放同一个群中的所有用户名
                Same_G_Username.push_back(numTouser[i]);//先把第一个用户，他也就是群主，放进去
                fout << index++;//群序号
                v[i] = 1;//以i为基准
                for (int j = i + 1; j < map_idx; j++)//遍历所有用户
                {
                    if (find(i) == find(j))//和i是在同一个群的用户
                    {
                        Same_G_Username.push_back(numTouser[j]);//把j放入该群中
                        p_num++;//群人数增加
                        v[j] = 1;//j就被访问过了，不能加入到其他群中
                    }
                }
                fout << " " << p_num;
                for (vector<string>::const_iterator it = Same_G_Username.begin(); it != Same_G_Username.end(); it++)
                {
                    fout << " " << (*it);
                }
                fout << endl;

            }
        }
        fout.close();
}
void Cover_Win::Show()
{
    Merge();
    Cover();
    QFile file("../weChatCoverData.txt");
    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
    {
        qDebug()<<"文件打开成功";
        QByteArray array;
        while(file.atEnd()==false)
            array+=file.readLine();
        edit->setText(array);
         file.close();
    }
    else
        qDebug()<<"文件读取失败";

}
void Cover_Win::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap(":image/cover.jpg"));
}
int Cover_Win::GetNum(string s)
{
    int k;
    if(userTonum.find(s)!=userTonum.end())
        k=userTonum[s];
    else
        return -1;
    return p_size[find(k)];
}
void Cover_Win::search()
{
       string user_name=search_btn->text().toStdString();
       int num=GetNum(user_name);
       qDebug()<<num;
}
