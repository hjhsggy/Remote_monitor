#include "abpwnd.h"

ABPWnd::ABPWnd(QWidget *parent,QRect rc) : DrawWnd(parent)
{
    m_iABPMax = 120;
    m_iABPCur = 60;
    m_iABPMin = 80;

    m_strTitle = "血压";

    m_ftTitle = NULL;
    m_ftNumber = NULL;

    m_textColor = qRgb(255,0,0);
    m_colBK = qRgb(0,0,0);

    m_rcSize = rc;
    this->setGeometry(rc);

    setTextFont();

    //初始化Pixmap
    InitUserDC();

    //画内容
    DrawContent();
}

ABPWnd::~ABPWnd()
{
    deleteTextFont();
}

//绘制内容
void ABPWnd::DrawContent()
{
    QRect  rc = this->rect();
    QPainter  painter;
    painter.begin(m_pixMem);

    painter.fillRect(rc,m_colBK);

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

void ABPWnd::SetNumber(int iMax, int iMin, int iCur)
{
    m_iABPMax = iMax;
    m_iABPMin = iMin;
    m_iABPCur = iCur;

    //重绘
    DrawContent();
}


//设置字体
void ABPWnd::setTextFont(int nTitle,int nNumber)
{
    deleteTextFont();

    m_ftTitle = new QFont("黑体",nTitle);

    m_ftNumber = new QFont("Arial",nNumber,QFont::Bold);
}

//删除字体
void ABPWnd::deleteTextFont()
{
    if(NULL != m_ftTitle)
    {
        delete m_ftTitle;
        m_ftTitle = NULL;
    }

    if(NULL != m_ftNumber)
    {
        delete m_ftNumber;
        m_ftNumber = NULL;
    }
}

//设置标题
void ABPWnd::setTitle(QString strTitle)
{
    m_strTitle = strTitle;

    //重绘
    DrawContent();
}
