#include "search_user_win.h"

Search_User_Win::Search_User_Win(QWidget *parent) : QWidget(parent)
{
    this->resize(800,600);
    this->setWindowTitle("查找用户");
    out_btn=new QPushButton(this);
    out_btn->setText("回退");
    out_btn->setGeometry(30,150,180,50);
    out_btn->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
    out_btn->show();
    connect(out_btn,&QPushButton::clicked,this,&Search_User_Win::SendSlot);

    title=new QLabel(this);
    title->setText("  微信群管理系统");
    title->setGeometry(this->width()/2-100,30,350,30);
    title->setStyleSheet("QLabel{font-size:28px;color:black;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    title->show();

    front_title=new QLabel(this);
    front_title->setText("   前端服务系统");
    front_title->setGeometry(this->width()/2-100,70,350,30);
    front_title->setStyleSheet("QLabel{font-size:28px;color:black;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    front_title->show();

    fun_title=new QLabel(this);
    fun_title->setText("查询群中是否存在某用户");
    fun_title->setGeometry(this->width()/2-100,110,350,30);
    fun_title->setStyleSheet("QLabel{font-size:28px;color:black;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    fun_title->show();
    GroupList=new WeChatGroup[500];

    user_edit=new QLineEdit(this);
    user_edit->setGeometry(30,250,180,50);
    user_edit->setText("在此处输入用户名");
    user_edit->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
    user_edit->show();

    group_edit=new QLineEdit(this);
    group_edit->setGeometry(30,350,180,50);
    group_edit->setText("在此处输入群名");
    group_edit->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
    group_edit->show();


    search=new QPushButton(this);
    search->setText("搜索");
    search->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
    search->setGeometry(30,450,180,50);
    connect(search,&QPushButton::clicked,this,&Search_User_Win::Hash_Search);

}
void Search_User_Win::SendSlot()
{
    emit UserToFront();
}
void Search_User_Win::Get_idx()
{
        user_idx=0;
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
                    //核心部分，实现用户与下标一一对应
                    if (userTonum.find(name) == userTonum.end());//这个用户还没有被映射
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
void Search_User_Win::Creat_Hash()
{
    //遍历每个群，读到群中用户时，由用户名得到映射下标，因此知道在哪一个用户链表中插入该群
        //完成初始化
        for (int i = 0; i < user_idx; i++)
        {
            Hash[i] = new LNode;
            Hash[i]->next = NULL;
        }
        for (int i = 0; i < ListLen; i++)
        {//从第一个群开始
            for (vector<string>::const_iterator it = GroupList[i].Person.begin(); it != GroupList[i].Person.end(); it++)
            {
                int idx = userTonum[*it];//由人名得到用户下标,确定是存入哪一个用户链表中
                LinkList p = Hash[idx];
                //头插法插入群名
                LinkList t_node = new LNode;
                t_node->node_value = GroupList[i].Group_Name;//存入群名
                t_node->next = p->next;
                p->next = t_node;
            }
        }
}
void Search_User_Win::Hash_Search()
{
        Get_idx();
        Creat_Hash();
        //3.输入用户名，得到映射下标，找到要查询的链表，查询是否有该群
        string name_key, group_key;
        name_key=user_edit->text().toStdString();
        group_key=group_edit->text().toStdString();//先把QString转换为string
        int idx = userTonum[name_key];//得到要查找的用户放入下标
        LinkList p = Hash[idx]->next;
        int cmp_cnts = 0;
        bool flag = false;
        while (p)
        {
            cmp_cnts++;
            if(p->node_value==group_key)
            {
                flag = true;
                break;
            }
            p = p->next;
        }
        if(flag==true)
        {
            QMessageBox::information(this,"存在",QString("存在，比较次数为:%1").arg(cmp_cnts));
        }
        else
            QMessageBox::information(this,"不存在","不存在");
}
void Search_User_Win::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap(":image/ts.png"));
}
