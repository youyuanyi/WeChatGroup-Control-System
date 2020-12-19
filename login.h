#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QMessageBox>
#include<QLabel>
#include<QPainter>
#include<QPen>
#include<QPixmap>
#include<QPaintEvent>
#include"backcontrol.h"
class login : public QWidget
{
    Q_OBJECT
public:
    explicit login(QWidget *parent = nullptr);
    void LoginToBack();//登录成功则执行跳转到后台界面
    void loging();//登录
    void Deal_Back();//处理从后台界面回退到登录界面
    void paintEvent(QPaintEvent *event);
signals:
     void LoginToMain();


public slots:
     void SendSlots();

private:
    QPushButton *login_btn;//登录按钮
    QPushButton *out_btn;
    QLabel *u_label;
    QLabel *p_label;
    QLineEdit *user;
    QLineEdit *password;
    BackControl back_sub;//后台界面子对象
    QString accout="数据结构A";
    QString pwd="123456";
};

#endif // LOGIN_H
