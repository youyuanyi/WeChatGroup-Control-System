#include "sortwin.h"

SortWin::SortWin(QWidget *parent) : QWidget(parent)
{
    this->resize(1400,1100);
    this->setWindowTitle("微信群排序");
    out_btn=new QPushButton(this);
    out_btn->setText("回退");
    out_btn->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
    out_btn->setGeometry(30,150,180,50);
    out_btn->show();

    sort_btn=new QPushButton(this);
    sort_btn->setText("排序");
    sort_btn->setGeometry(30,250,180,50);
    sort_btn->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
    sort_btn->show();
    connect(out_btn,&QPushButton::clicked,this,&SortWin::SentSlot);
    connect(sort_btn,&QPushButton::clicked,this,&SortWin::readnewfile);

    title=new QLabel(this);
    title->setText("  微信群管理系统");
    title->setGeometry(this->width()/2-100,30,350,30);
    title->setStyleSheet("QLabel{font-size:28px;color:black;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    title->show();

    front_title=new QLabel(this);
    front_title->setText("   前端服务系统");
    front_title->setStyleSheet("QLabel{font-size:28px;color:black;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    front_title->setGeometry(this->width()/2-100,70,350,30);
    front_title->show();

    fun_title=new QLabel(this);
    fun_title->setGeometry(this->width()/2-100,110,350,30);
    fun_title->setStyleSheet("QLabel{font-size:28px;color:black;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    fun_title->setText("    微信群排序");
    fun_title->show();

    edit=new QTextEdit(this);
    edit->setGeometry(230,150,900,600);
    edit->show();

    GroupList=new WeChatGroup[500];//创建群列表对象
    this->ReadFile();

}
void SortWin::SentSlot()
{
    emit SortToFront();
}
void SortWin::ReadFile()
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
void SortWin::sort()
{
        int i, j;
        for(j=0;j<ListLen-1;j++)
        {
            for ( i = 0; i<ListLen-1-j; i++)
            {//以群人数>年>月>日的优先级进行比较交换
                if (GroupList[i].Person_Num < GroupList[i + 1].Person_Num)
                {
                    WeChatGroup temp = GroupList[i];
                    GroupList[i] = GroupList[i + 1];
                    GroupList[i + 1] = temp;
                }
                else if ((GroupList[i].Person_Num == GroupList[i+ 1].Person_Num) && (GroupList[i].year > GroupList[i + 1].year))
                {
                    WeChatGroup temp = GroupList[i];
                    GroupList[i] = GroupList[i + 1];
                    GroupList[i + 1] = temp;
                }
                else if ((GroupList[i].Person_Num == GroupList[i + 1].Person_Num) && (GroupList[i].year == GroupList[i + 1].year) && (GroupList[i].month > GroupList[i + 1].month))
                {
                    WeChatGroup temp = GroupList[i];
                    GroupList[i] = GroupList[i + 1];
                    GroupList[i + 1] = temp;
                }
                else if ((GroupList[i].Person_Num == GroupList[i + 1].Person_Num) && (GroupList[i].year == GroupList[i + 1].year) && (GroupList[i].month == GroupList[i + 1].month)&&(GroupList[i].date>GroupList[i + 1].date))
                {
                    WeChatGroup temp = GroupList[i];
                    GroupList[i] = GroupList[i + 1];
                    GroupList[i + 1] = temp;
                }
            }
        }
        ofstream fout("../weChatSortData.txt",ios::out);
        if(fout.is_open())
        {
            for(int i=0;i<ListLen;i++)
            {

                fout<<GroupList[i].Group_Name<<" "<<GroupList[i].Person_Num;
                for(vector<string>::const_iterator it=GroupList[i].Person.begin();it!=GroupList[i].Person.end();it++)
                {
                    fout<<" "<<*it;
                }
                fout<<" "<<GroupList[i].year<<" "<<GroupList[i].month<<" "<<GroupList[i].date<<endl;
            }

        }
        fout.close();
}
void SortWin::readnewfile()
{
    sort();
    QFile file("../weChatSortData.txt");
    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
    {
        QByteArray array;
        while(file.atEnd()==false)
            array+=file.readLine();
        edit->setText(array);
         file.close();
    }
    else
        qDebug()<<"文件读取失败";
}
void SortWin::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap(":image/back_bg.jpg"));
}
