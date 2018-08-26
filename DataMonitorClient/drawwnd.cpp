#include "drawwnd.h"

DrawWnd::DrawWnd(QWidget *parent) : QWidget(parent)
{
    m_pixMem = 0;

    //设置背景颜色
    m_backColor = Qt::black;
}

DrawWnd::~DrawWnd()
{
    DeleteUserDC();
}

//窗口绘制事件
void DrawWnd::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);

    //贴图
    painter.drawPixmap(0,0,*m_pixMem);

    painter.end();

}

//初始化绘图设备
void DrawWnd::InitUserDC()
{
    DeleteUserDC();

    QRect rc = this->rect();

    m_pixMem = new QPixmap(rc.width(),rc.height());

}

//删除绘图设备
void DrawWnd::DeleteUserDC()
{
    if(0 == m_pixMem)
    {
        delete m_pixMem;
        m_pixMem = 0;
    }
}

//设置背景颜色
void DrawWnd::setBackColor(QColor backColor)
{
    m_backColor = backColor;
}
