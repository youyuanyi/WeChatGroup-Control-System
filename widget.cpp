#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //进行界面，按钮和标签的初始化
    this->resize(800,600);
    front=new QPushButton(this);
    front->setText("前台服务");
    front->setGeometry(300,200,200,50);
    front->setStyleSheet("QPushButton{background-color:#FFE4E1;border-radius:25px;font-size:25px;}");
    front->show();

    back=new QPushButton(this);
    back->setText("后台管理");
    back->setGeometry(300,300,200,50);
    back->setStyleSheet("QPushButton{background-color:#F0F8FF;border-radius:25px;font-size:25px;}");
    back->show();

    out=new QPushButton(this);
    out->setText("退出系统");
    out->setGeometry(300,400,200,50);
    out->setStyleSheet("QPushButton{background-color:#B0E2FF;border-radius:25px;font-size:25px;}");
    out->show();


    title=new QLabel(this);
    title->setAlignment(Qt::AlignHCenter);
    title->setText("  微信群管理系统  ");
    title->setStyleSheet("QLabel{font-size:28px;color:white;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    title->setGeometry(300,40,200,30);
    title->show();

    mainwin=new QLabel(this);
    mainwin->setText("     主界面       ");
    mainwin->setAlignment(Qt::AlignHCenter);
    mainwin->setStyleSheet("QLabel{font-size:28px;color:white;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    mainwin->setGeometry(300,80,200,30);
    mainwin->show();


    //连接信号和槽
    connect(out,&QPushButton::clicked,this,&Widget::close);//后续在进行对话框优化
    connect(front,&QPushButton::clicked,this,&Widget::ChangetoFront);//切换到前端界面
    connect(back,&QPushButton::clicked,this,&Widget::ChangetoLogin);//切换到后端界面
    void (FrontServe::*Signal)()=&FrontServe::MySignal;//函数指针指向从前端界面回退到主界面的信号
    connect(&front_Win,Signal,this,&Widget::FrontToWin);//从前端界面回退到主界面

    void (login::*Signal2)()=&login::LoginToMain;
    connect(&login_win,Signal2,this,&Widget::LoginToWin);

    GroupList=new WeChatGroup[500];
}

Widget::~Widget()
{
    delete ui;
}
void Widget::ChangetoFront()
{
    this->hide();
    front_Win.show();
}
void Widget::ChangetoLogin()
{
    this->hide();
    login_win.show();
}
void Widget::FrontToWin()
{
    this->show();
    front_Win.hide();
}
void Widget::LoginToWin()
{
    this->show();
    login_win.hide();
}
void Widget::ReadFile()
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
void Widget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap(":image/main_bg.jpg"));
}
