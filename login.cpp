#include "login.h"


login::login(QWidget *parent) : QWidget(parent)
{
    this->resize(800,600);
    this->setWindowTitle("登录界面");

    u_label=new QLabel(this);
    u_label->setGeometry(300,200,100,50);
    u_label->setText("用户名");
    u_label->setStyleSheet("QLabel{font-size:28px;color:black;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    u_label->show();

    p_label=new QLabel(this);
    p_label->setGeometry(300,300,100,50);
    p_label->setText("密码");
    p_label->setStyleSheet("QLabel{font-size:28px;color:black;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    p_label->show();

    user=new QLineEdit(this);
    user->setGeometry(425,200,200,50);
    user->show();

    password=new QLineEdit(this);
    password->setGeometry(425,300,200,50);
    password->setEchoMode(QLineEdit::Password);
    password->show();

    login_btn=new QPushButton(this);
    login_btn->setGeometry(475,370,150,50);
    login_btn->setText("登录");
    login_btn->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
    login_btn->show();
    connect(login_btn,&QPushButton::clicked,this,&login::loging);

    out_btn=new QPushButton(this);
    out_btn->setGeometry(300,370,150,50);
    out_btn->setText("回退");
    out_btn->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
    out_btn->show();
    connect(out_btn,&QPushButton::clicked,this,&login::SendSlots);//回退到主窗口
    void (BackControl::*S)()=&BackControl::BackToLogin;
    connect(&back_sub,S,this,&login::Deal_Back);

}
void login::SendSlots()
{
    emit LoginToMain();
}
void login::loging()
{
    QString name=user->text();
    QString pa=password->text();
    if(name==accout&&pa==pwd)
    {
        QMessageBox::information(this,"成功","登陆成功!");
        user->clear();
        password->clear();
        LoginToBack();//登录界面隐藏，后台界面显示
    }
    else
    {
        QMessageBox::information(this,"失败","登录失败!");
        this->close();

    }
}
void login::LoginToBack()
{
    this->hide();
    back_sub.show();
}
void login::Deal_Back()
{
    this->show();
    back_sub.hide();
}
void login::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap(":image/forest.jpg"));
}
