#ifndef STRIP_H
#define STRIP_H

#include <QObject>
#include <QRect>
#include <QPainter>

#include <vector>
using namespace std;

//线条类

class Strip
{
public:
    Strip();
    ~Strip();
public:
    void SetStripOffSet(int  nOffSet);
    void Draw(QPainter* pDC);
    void SetStripSize(QRect rcSize);
    void AddPoint(uchar uData);
    QString GetCID() const;
    void SetCID(QString strCID);
private:
    vector<uchar>	m_Data;//存放数据点
    QRect			m_rcSize;//波形窗口的大小
    int				m_nCurPos;//数据点插入的位置
    int				m_nOffSet;//位置的偏移量

    QString			m_strCID;//客户端编号
};

#endif // STRIP_H
