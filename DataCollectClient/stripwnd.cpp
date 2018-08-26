#include "stripwnd.h"

StripWnd::StripWnd(QWidget *parent,QRect rc) : DrawWnd(parent)
{
    m_colStrip =QColor::fromRgb(0,255,0);

    m_rcSize = rc;
    this->setGeometry(rc);

    //初始化Pixmap
    InitUserDC();

    //设置线条尺寸
    m_Strip.SetStripSize(rc);

    //画内容
    DrawContent();
}

StripWnd::~StripWnd()
{

}


//绘制内容
void StripWnd::DrawContent()
{
    QPainter painter;
    painter.begin(m_pixMem);

    QRect rc(QPoint(0, 0),QSize(m_rcSize.width(), m_rcSize.height()));

    //反走样（锯齿）
    painter.setRenderHint(QPainter::Antialiasing, true);

    //画背景
    painter.fillRect(rc,m_backColor);

    QPen pen;

    //画线
    pen.setStyle(Qt::SolidLine);
    pen.setColor(m_colStrip);
    painter.setPen(pen);

    //画内容
    m_Strip.Draw(&painter);

    painter.end();

    //重绘
    this->update();
}


//加入数据点
void StripWnd::AddPoint(uchar uData)
{
    m_Strip.AddPoint(uData);

    //重绘
    DrawContent();
}

//设置偏移量
void StripWnd::SetStripOffSet(int nOffSet)
{
    m_Strip.SetStripOffSet(nOffSet);

    //重绘
    DrawContent();
}

//添加数据点
void StripWnd::AddPoint(uchar *pData, int nLen)
{
    for(int i=0;i<nLen;i++)
    {
        m_Strip.AddPoint(pData[i]);
    }

    //重绘
    DrawContent();
}

//设置线条颜色
void StripWnd::SetStripColor(QColor colStrip)
{
    m_colStrip = colStrip;
}


