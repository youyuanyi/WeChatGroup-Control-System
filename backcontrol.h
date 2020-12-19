#ifndef BACKCONTROL_H
#define BACKCONTROL_H

#include<QPushButton>
#include<QLabel>
#include<QTextEdit>
#include<QLineEdit>
#include <QWidget>
#include<fstream>
#include<string>
#include<vector>
#include<QPainter>
#include<QPaintEvent>
#include<QPen>
#include<QPixmap>
#include<map>
#include<QFile>
#include<QDebug>
#include<QMessageBox>
#include"group.h"
#include"data.h"

class BackControl : public QWidget
{
    Q_OBJECT
public:
    explicit BackControl(QWidget *parent = nullptr);
    void Deal_Add();
    void Deal_Del();
    void Deal_Mod();
    void add_user();//增加用户
    void del_user();//删除用户
    void Shif_G();//更改群名
    void Add_readnewfile();
    void Del_readnewfile();
    void Mod_readnewfile();
    void ReadFile();//读文件内容到结构体中
    void Save();
    void paintEvent(QPaintEvent *event);


signals:
     void BackToLogin();
public slots:
     void SendSlots();
private:
    WeChatGroup *GroupList;//群列表
    int ListLen;
    QPushButton *out;//回退
    QPushButton *add_btn;//添加用户,用来进行增加用户
    QPushButton *del_btn;//删除用户
    QPushButton *modify_btn;//修改群名称
    QLabel *title;//主标题
    QLabel *back_title;//后台控制标题
    QLineEdit *user;
    QLineEdit *group;
    QLineEdit *new_group;
    QTextEdit *edit;
    int flag;
    int add_cnts;//这三个cnts用来记录打开文件数
    int del_cnts;
    int shift_cnts;
};

#endif // BACKCONTROL_H
