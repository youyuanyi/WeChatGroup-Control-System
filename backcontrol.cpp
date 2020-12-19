#include "backcontrol.h"

BackControl::BackControl(QWidget *parent) : QWidget(parent)
{
    this->resize(1400,1100);
    this->setWindowTitle("后台管理");
    GroupList=new WeChatGroup[500];
    flag=0;
    add_cnts=0;del_cnts=0;shift_cnts=0;

    out=new QPushButton(this);
    out->setText("返回上一级");
    out->setGeometry(50,150,140,60);
    out->setStyleSheet("QPushButton{background-color:#EEE9E9;border-radius:30px;font-size:20px;}");
    out->show();
    connect(out,&QPushButton::clicked,this,&BackControl::SendSlots);

    title=new QLabel(this);
    title->setText("微信群管理系统");
    title->setGeometry(600,220,150,60);
    title->show();

    back_title=new QLabel(this);
    back_title->setText("后台控制系统");
    back_title->setGeometry(600,290,150,60);
    back_title->show();

    add_btn=new QPushButton(this);
    add_btn->setText("添加用户");
    add_btn->setStyleSheet("QPushButton{background-color:#EEE9E9;border-radius:30px;font-size:20px;}");
    add_btn->setGeometry(50,240,140,60);
    add_btn->show();

    del_btn=new QPushButton(this);
    del_btn->setText("删除用户");
    del_btn->setStyleSheet("QPushButton{background-color:#EEE9E9;border-radius:30px;font-size:20px;}");
    del_btn->setGeometry(50,330,140,60);
    del_btn->show();

    modify_btn=new QPushButton(this);
    modify_btn->setText("修改群名称");
    modify_btn->setStyleSheet("QPushButton{background-color:#EEE9E9;border-radius:30px;font-size:20px;}");
    modify_btn->setGeometry(50,420,140,60);
    modify_btn->show();

    user=new QLineEdit(this);
    user->setText("输入用户名");
    user->setGeometry(40,530,150,40);
    user->show();

    group=new QLineEdit(this);
    group->setText("输入群名");
    group->setGeometry(40,600,150,40);
    group->show();

    new_group=new QLineEdit(this);
    new_group->setText("输入新的群名");
    new_group->setGeometry(40,670,150,40);
    new_group->show();

    edit=new QTextEdit(this);
    edit->setGeometry(200,150,1000,600);
    edit->show();

    connect(add_btn,&QPushButton::clicked,this,&BackControl::Add_readnewfile);
    connect(del_btn,&QPushButton::clicked,this,&BackControl::Del_readnewfile);
    connect(modify_btn,&QPushButton::clicked,this,&BackControl::Mod_readnewfile);

}
void BackControl::ReadFile()
{
    ifstream fin;
    fin.open("../weChatData.txt");
    if (!fin.is_open())
       qDebug("文件打开失败");
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
void BackControl::Save()
{//把新的数据写入到新文件中
     ofstream fout;
     fout.open("../newweChatData.txt");
     if (fout.is_open())
     {
         for (int i = 0; i < ListLen; i++)
         {
             fout << GroupList[i].Group_Name << " " << GroupList[i].Person_Num;
             for (vector<string>::const_iterator it = GroupList[i].Person.begin(); it != GroupList[i].Person.end(); it++)
             {
                 fout << " " << (*it);
             }
             fout << " " << GroupList[i].year << " " << GroupList[i].month << " " << GroupList[i].date << endl;
         }
         fout.close();
     }
}
void BackControl::add_user()
{
    //对结构体操作
        string user_name=user->text().toStdString();
        string group_name=group->text().toStdString();
        for (int i = 0; i < ListLen; i++)
            {
                if (GroupList[i].Group_Name == group_name)
                {
                    flag=1;
                    GroupList[i].Person.push_back(user_name);
                    GroupList[i].Person_Num++;
                    break;
                }
            }

}
void BackControl::del_user()
{
    //对结构体操作
        string user_name=user->text().toStdString();
        string group_name=group->text().toStdString();
        for (int i = 0; i < ListLen; i++)
            {
                if (GroupList[i].Group_Name == group_name)
                {
                    for(vector<string>::const_iterator it=GroupList[i].Person.begin();it!=GroupList[i].Person.end();it++)
                    {
                        if((*it)==user_name)
                        {
                            flag=1;
                            GroupList[i].Person.erase(it);
                            GroupList[i].Person_Num--;
                            break;
                        }
                    }
                }
            }
}
void BackControl::Shif_G()
{
    //对结构体操作
        string new_name=new_group->text().toStdString();
        string group_name=group->text().toStdString();
        for (int i = 0; i < ListLen; i++)
            {
                if (GroupList[i].Group_Name == group_name)
                {
                       GroupList[i].Group_Name=new_name;
                       flag=1;
                       break;

                }
            }
}
void BackControl::Add_readnewfile()
{
    if(add_cnts==0&&del_cnts==0&&shift_cnts==0)
    {//如果之前没有对文件进行过操作，就读原来的文件
        ReadFile();
    }
    add_user();
    Save();
    if(flag==1)
    {
    QFile file("../newweChatData.txt");
    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
    {
        QByteArray array;
        while(file.atEnd()==false)
            array+=file.readLine();
        edit->setText(array);
         file.close();
         add_cnts++;
    }
    else
        qDebug()<<"文件读取失败";
    }
    else
        QMessageBox::information(this,"失败啦","该群不存在");

    flag=0;
}

void BackControl::Del_readnewfile()
{
    if(add_cnts==0&&del_cnts==0&&shift_cnts==0)
    {//如果之前没有对文件进行过操作，就读原来的文件
        ReadFile();
    }
    del_user();
    Save();
    if(flag==1)
    {
    QFile file("../newweChatData.txt");
    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
    {
        QByteArray array;
        while(file.atEnd()==false)
            array+=file.readLine();
        edit->setText(array);
         file.close();
         flag=0;
         del_cnts++;
    }
    else
        qDebug()<<"文件读取失败";
    }
    else
        QMessageBox::information(this,"失败啦","不在群中，删除失败!");
}
void BackControl::Mod_readnewfile()
{//修改完群名后，往这个群里添加新用户有bug
    if(add_cnts==0&&del_cnts==0&&shift_cnts==0)
    {//如果之前没有对文件进行过操作，就读原来的文件
        ReadFile();
    }
    Shif_G();
    Save();
    if(flag==1)
    {
    QFile file("../newweChatData.txt");
    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
    {
        QByteArray array;
        while(file.atEnd()==false)
            array+=file.readLine();
        edit->setText(array);
         file.close();
         flag=0;
         shift_cnts++;
    }
    else
        qDebug()<<"文件读取失败";
    }
    else
        QMessageBox::information(this,"失败啦","不在群中，删除失败!");
}
void BackControl::SendSlots()
{
    emit BackToLogin();
}
void BackControl::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap(":image/back_bg.jpg"));
}
