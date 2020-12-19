#ifndef SEARCH_CLASS_WIN_H
#define SEARCH_CLASS_WIN_H

#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QTextEdit>
#include<fstream>
#include<sstream>
#include<string>
#include<QLineEdit>
#include<QDebug>
#include<QTextStream>
#include<QMessageBox>
#include<QPainter>
#include<QPen>
#include<QPixmap>
#include<QPaintEvent>
#include"data.h"
#include<iostream>
using namespace std;
class Search_Class_Win : public QWidget
{
    Q_OBJECT
public:
    explicit Search_Class_Win(QWidget *parent = nullptr);
    int KMP(string,string);
    void Classify();//分类，得到每个群的类别
    void Search_Class();
    void ReadFile();
    void paintEvent(QPaintEvent *event);

signals:
    void ClassToFront();
public slots:
    void SendSlot();
private:
    QPushButton *out_btn;
    QPushButton *class_btn;//分类按钮
    QTextEdit *edit;//显示内容
    QLineEdit *key_word;
    QLabel *title;//主标题
    QLabel *front_title;//前端服务标题
    QLabel *fun_title;//功能标签
    WeChatGroup *GroupList;//群列表
    int ListLen;
    int flag;

};

#endif // SEARCH_CLASS_WIN_H
