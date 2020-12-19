#ifndef SORTWIN_H
#define SORTWIN_H

#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include <Qvector>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QBuffer>
#include<QTextStream>
#include<QDataStream>
#include<QList>
#include<QPainter>
#include<QPaintEvent>
#include<QPen>
#include<QPixmap>
#include<string>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<QTextEdit>
#include"data.h"
class SortWin : public QWidget
{
    Q_OBJECT
public:
    explicit SortWin(QWidget *parent = nullptr);
    void GroupSort();
    void ReadFile();//读文件内容到结构体中
    void sort();
    void readnewfile();
    //bool cmp(WeChatGroup a,WeChatGroup b);
    void paintEvent(QPaintEvent *event);

signals:
    void SortToFront();

public slots:
    void SentSlot();
 private:
    QPushButton *out_btn;
    QLabel *title;//主标题
    QLabel *front_title;//前端服务标题
    QLabel *fun_title;//功能标签
    WeChatGroup *GroupList;//群列表
    QPushButton *sort_btn;//排序按钮
    QTextEdit *edit;//显示标签
    int ListLen;

};

#endif // SORTWIN_H
