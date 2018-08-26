#ifndef TEXTWND_H
#define TEXTWND_H

#include <QObject>
#include <QWidget>
#include <QString>
#include "drawwnd.h"

/*
文本数据显示窗口
*/

class TextWnd : public DrawWnd
{
    Q_OBJECT
public:
    explicit TextWnd(QWidget *parent,QRect rc);
    virtual ~TextWnd();
protected:
    virtual void DrawContent();//绘制内容

protected:
    QColor      m_backColor;//背景色
    QColor      m_textColor;//文本颜色

    QString     m_strTitle;//标题
    float       m_fNumber;//数值

    QFont       *m_ftTitle;//标题字体
    QFont       *m_ftNumber;//数值字体

    QRect       m_rcSize;//窗口的位置和大小

public:
    void        setTextFont(int nTitle = 16,int nNumber = 36);//设置字体
    void        setNumber(float  fNumber);//设置数字
    void        setTextColor(QColor textColor);//设置文本颜色
    void        setTitle(QString strTitle);//设置标题
private:
    void        deleteTextFont();//删除字体

signals:

public slots:
};

#endif // TEXTWND_H
