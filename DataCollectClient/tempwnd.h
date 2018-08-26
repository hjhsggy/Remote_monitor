#ifndef TEMPWND_H
#define TEMPWND_H

#include <QObject>
#include <QWidget>
#include "drawwnd.h"

/*
体温窗口
*/

class TempWnd : public DrawWnd
{
    Q_OBJECT
public:
    explicit TempWnd(QWidget *parent,QRect rc);
    virtual ~TempWnd();

signals:

public slots:

protected:
    QColor      m_backColor;//背景色
    QColor      m_textColor;//文本颜色

    QString     m_strTitle;//标题
    float       m_fNumber;//数值

    QFont       *m_ftTitle;//标题字体
    QFont       *m_ftNumber;//数值字体

    QRect       m_rcSize;//窗口的位置和大小

public:
    void        setTextFont(int nTitle = 16,int nNumber = 24);//设置字体
    void        setNumber(float  fNumber);//设置数字
    void        setTextColor(QColor textColor);//设置文本颜色
    void        setTitle(QString strTitle);//设置标题
private:
    void        deleteTextFont();


protected:
    virtual void DrawContent();//绘制内容
};

#endif // TEMPWND_H
