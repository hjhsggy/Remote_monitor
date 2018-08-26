#ifndef ABPWND_H
#define ABPWND_H

#include <QObject>
#include <QWidget>

#include "textwnd.h"


/*
血压显示窗口
*/

class ABPWnd : public TextWnd
{
    Q_OBJECT
public:
    explicit ABPWnd(QWidget *parent ,QRect rcSize);
    ~ABPWnd();

private:
    int		m_iABPMax;
    int		m_iABPMin;
    int		m_iABPCur;
public:
    void SetNumber(int iMax, int iMin, int iCur);
protected:
    virtual void DrawContent();//绘制内容

signals:

public slots:
};

#endif // ABPWND_H
