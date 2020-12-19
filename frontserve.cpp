#include "frontserve.h"

FrontServe::FrontServe(QWidget *parent) : QWidget(parent)
{
        this->resize(800,600);
        this->setWindowTitle("前端服务");

        sort=new QPushButton(this);
        sort->setText("微信群的排序");
        sort->setGeometry(270,130,250,30);
        sort->setStyleSheet("QPushButton{background-color:#EEE9E9;border-radius:15px;font-size:20px;}");
        sort->show();

        search_class=new QPushButton(this);
        search_class->setText("按类别查询");
        search_class->setGeometry(270,200,250,30);
        search_class->setStyleSheet("QPushButton{background-color:#EEE9E9;border-radius:15px;font-size:20px;}");
        search_class->show();

        search_user=new QPushButton(this);
        search_user->setText("查询群中有无用户");
        search_user->setStyleSheet("QPushButton{background-color:#EEE9E9;border-radius:15px;font-size:20px;}");
        search_user->setGeometry(270,270,250,30);
        search_class->show();

        search_dis=new QPushButton(this);
        search_dis->setText("查询两用户间的距离");
        search_dis->setGeometry(270,340,250,30);
        search_dis->setStyleSheet("QPushButton{background-color:#EEE9E9;border-radius:15px;font-size:20px;}");
        search_dis->show();

        cover=new QPushButton(this);
        cover->setText("群覆盖");
        cover->setStyleSheet("QPushButton{background-color:#EEE9E9;border-radius:15px;font-size:20px;}");
        cover->setGeometry(270,410,250,30);
        cover->show();

        out=new QPushButton(this);
        out->setText("返回上一级");
        out->setStyleSheet("QPushButton{background-color:#EEE9E9;border-radius:15px;font-size:20px;}");
        out->setGeometry(270,480,250,30);
        out->show();

        title=new QLabel(this);
        title->setText("微信群管理系统");
        title->setGeometry(300,40,200,30);
        title->setStyleSheet("QLabel{font-size:28px;color:white;border-radius:5px;font-family:Georgia, serif;}");
        title->show();

        front_title=new QLabel(this);
        front_title->setText("前端服务系统");
        front_title->setGeometry(300,90,200,30);
        front_title->setStyleSheet("QLabel{font-size:28px;color:white;border-radius:5px;font-family:Georgia, serif;}");
        front_title->show();

        //联系信号和槽
        connect(out,&QPushButton::clicked,this,&FrontServe::SendSlot);
        connect(sort,&QPushButton::clicked,this,&FrontServe::FrontToSort);
        connect(search_class,&QPushButton::clicked,this,&FrontServe::FrontToClass);
        connect(search_user,&QPushButton::clicked,this,&FrontServe::FrontToUser);
        connect(search_dis,&QPushButton::clicked,this,&FrontServe::FrontToDis);
        connect(cover,&QPushButton::clicked,this,&FrontServe::FrontToCover);

        //从各个子界面跳回到前端界面的信号和槽
        void (Search_Class_Win::*class_signal)()=&Search_Class_Win::ClassToFront;
        connect(&Class_Sub,class_signal,this,&FrontServe::Deal_Class);
        void (SortWin::*sort_signal)()=&SortWin::SortToFront;
        connect(&Sort_Sub,sort_signal,this,&FrontServe::Deal_Sort);
        void (Search_User_Win::*user_signal)()=&Search_User_Win::UserToFront;
        connect(&User_Sub,user_signal,this,&FrontServe::Deal_User);
        void (Search_Dis_Win::*dis_signal)()=&Search_Dis_Win::DisToFront;
        connect(&Dis_Sub,dis_signal,this,&FrontServe::Deal_Dis);
        void (Cover_Win::*cover_signal)()=&Cover_Win::CoverToFront;
        connect(&Cover_Sub,cover_signal,this,&FrontServe::Deal_Cover);

}

void FrontServe::SendSlot()
{
    emit MySignal();//子窗口发送信号
}
void FrontServe::FrontToSort()
{//前端跳转到排序界面
    this->hide();
    Sort_Sub.show();

}
void FrontServe::FrontToClass()
{
 //前端跳转到按类型查询
    this->hide();
    Class_Sub.show();
}

void FrontServe::FrontToUser()
{
//前端跳转到查询用户界面
    this->hide();
    User_Sub.show();
}
void FrontServe::FrontToCover()
{
//前端跳转到群覆盖界面
    this->hide();
    Cover_Sub.show();
}
void FrontServe::Deal_Class()
{//从按类型查询界面跳回到前端界面
    this->show();
    Class_Sub.hide();
}
void FrontServe::Deal_Sort()
{
    this->show();
    Sort_Sub.hide();
}
void FrontServe::Deal_User()
{
    this->show();
    User_Sub.hide();
}

void FrontServe::Deal_Cover()
{
    this->show();
    Cover_Sub.hide();
}
void FrontServe::FrontToDis()
{
    this->hide();
    Dis_Sub.show();
}
void FrontServe::Deal_Dis()
{
    this->show();
    Dis_Sub.hide();
}
void FrontServe::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap(":image/star.jpg"));
}
