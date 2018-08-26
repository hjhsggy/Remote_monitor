#ifndef DRAWWND_H
#define DRAWWND_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPixmap>

/*
双缓冲基类
*/

class DrawWnd : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWnd(QWidget *parent = 0);
    virtual ~DrawWnd();
protected:
    void paintEvent(QPaintEvent *);//窗口绘制事件

    void InitUserDC();//初始化绘图设备
    virtual void DrawContent()=0;//绘制内容

private:
    void DeleteUserDC();//删除绘图设备
protected:
    QPixmap     *m_pixMem;//内存绘制设备
    QColor      m_backColor;//背景色
public:
    void        setBackColor(QColor backColor);//设置背景颜色

signals:

public slots:
};

#endif // DRAWWND_H
