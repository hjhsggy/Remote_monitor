#ifndef STRIPWND_H
#define STRIPWND_H

#include <QObject>
#include <QWidget>

#include "drawwnd.h"
#include "strip.h"


//绘制曲线

class StripWnd : public DrawWnd
{
    Q_OBJECT
public:
    explicit StripWnd(QWidget *parent ,QRect rc);
    virtual ~StripWnd();

signals:

public slots:

public:
    void SetStripColor(QColor  colStrip);
    void AddPoint(uchar* pData,int nLen);
    void SetStripOffSet(int  nOffSet);
    void AddPoint(uchar uData);
private:
    Strip		m_Strip;//线条变量
    QColor      m_colStrip;//线条颜色


protected:
    virtual void DrawContent();//绘制内容
protected:
    QRect       m_rcSize;//窗口的位置和大小
};

#endif // STRIPWND_H
