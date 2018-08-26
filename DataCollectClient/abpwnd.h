#ifndef ABPWND_H
#define ABPWND_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QPainter>
#include "drawwnd.h"

/*
显示血压的窗口
*/

class ABPWnd : public DrawWnd
{
    Q_OBJECT
public:
    explicit ABPWnd(QWidget *parent,QRect rc);
    virtual ~ABPWnd();

signals:

public slots:

private:
    int		m_iABPMax;
    int		m_iABPMin;
    int		m_iABPCur;
    QString m_strTitle;

    QFont   *m_ftTitle;
    QFont   *m_ftNumber;

    QColor  m_textColor;
    QColor  m_colBK;

    QRect   m_rcSize;//窗口的位置和大小
public:
    void SetNumber(int iMax, int iMin, int iCur);
    void setTextFont(int nTitle = 16,int nNumber = 16);//设置字体
    void deleteTextFont();//删除字体
    void setTitle(QString strTitle);//设置标题

protected:
    virtual void DrawContent();//绘制内容
};

#endif // ABPWND_H
