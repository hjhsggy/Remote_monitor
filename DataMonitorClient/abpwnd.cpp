#include "abpwnd.h"

ABPWnd::ABPWnd(QWidget *parent,QRect rcSize)
    : TextWnd(parent,rcSize)
{
    m_iABPMax = 120;
    m_iABPCur = 60;
    m_iABPMin = 80;

    m_strTitle = "血压";
    m_textColor = qRgb(255,0,0);

    //设置字体
    setTextFont(16,24);

    DrawContent();
}

ABPWnd::~ABPWnd()
{

}

void ABPWnd::SetNumber(int iMax, int iMin, int iCur)
{
    m_iABPMax = iMax;
    m_iABPMin = iMin;
    m_iABPCur = iCur;

    //重绘
    DrawContent();

}

//绘制内容
void ABPWnd::DrawContent()
{
    QRect  rc = this->rect();
    QPainter  painter;
    painter.begin(m_pixMem);

    painter.fillRect(rc,m_backColor);

    int nBorder = 3;

    //设置文本颜色
    painter.setPen(m_textColor);

    painter.setFont(*m_ftTitle);

    //画文本
    int nSize = m_ftTitle->pointSize();

    //把nBorder+nSize值作为基线
    painter.drawText(nBorder, nBorder+nSize*3/2,m_strTitle);


    QRect  rcText = rc;
    rcText.setTop(nBorder+nSize*3/2);

    painter.setFont(*m_ftNumber);

    QString strABP;
    strABP.sprintf(("%d/%d\r\n%d"),m_iABPMax,m_iABPMin,m_iABPCur);

    painter.drawText(rcText,Qt::AlignCenter,strABP);

    painter.end();

    //重绘
    this->update();


}
