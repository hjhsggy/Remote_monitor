#ifndef TEMPWND_H
#define TEMPWND_H

#include <QObject>
#include <QWidget>

#include "textwnd.h"

/*
显示温度的窗口
*/

class TempWnd : public TextWnd
{
    Q_OBJECT
public:
    explicit TempWnd(QWidget *parent,QRect rcSize);
    ~TempWnd();

protected:
    virtual void DrawContent();//绘制内容

signals:

public slots:
};

#endif // TEMPWND_H
