#include "tempwnd.h"

TempWnd::TempWnd(QWidget *parent,QRect rcSize) : TextWnd(parent,rcSize)
{

}

TempWnd::~TempWnd()
{

}

//绘制内容
void TempWnd::DrawContent()
{
    QPainter painter;
    painter.begin(m_pixMem);

    //窗口内部大小
    QRect rc(QPoint(0, 0),QSize(m_rcSize.width(), m_rcSize.height()));

    //画背景
    painter.fillRect(rc,m_backColor);

    int nBorder = 3;

    float nOldSize = this->font().pointSize();

    //设置文本颜色
    painter.setPen(m_textColor);

    painter.setFont(*m_ftTitle);

    //画文本
    float nNewSize = m_ftTitle->pointSize();

    //字体变换时放大或缩小的倍数
    int nBig = (nNewSize/nOldSize);


    //把nBorder+nSize值作为基线
    painter.drawText(nBorder, nBorder+nNewSize*nBig*3/2,m_strTitle);

    QRect  rcText = rc;
    rcText.setTop(nBorder+nNewSize*nBig*3/2);

    painter.setFont(*m_ftNumber);
    QString strNumber;
    strNumber.sprintf("%.1f",m_fNumber);
    painter.drawText(rcText,Qt::AlignCenter,strNumber);

    painter.end();

    //重绘
    update();
}

