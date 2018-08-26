#include "tempwnd.h"

TempWnd::TempWnd(QWidget *parent,QRect rc) : DrawWnd(parent)
{
    //设置背景颜色
    m_backColor = Qt::black;

    //设置文本颜色
    m_textColor = QColor::fromRgb(0,255,0);

    m_strTitle = "心率";

    m_fNumber = 60.0f;

    m_ftTitle = NULL;
    m_ftNumber = NULL;

    setTextFont(16,40);


    m_rcSize = rc;
    this->setGeometry(rc);

    //初始化Pixmap
    InitUserDC();

    //画内容
    DrawContent();

}

TempWnd::~TempWnd()
{
    deleteTextFont();
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

//设置字体
void TempWnd::setTextFont(int nTitle,int nNumber)
{
    deleteTextFont();

    m_ftTitle = new QFont("黑体",nTitle);

    m_ftNumber = new QFont("Arial",nNumber,QFont::Bold);

}

//设置数字
void TempWnd::setNumber(float  fNumber)
{
    m_fNumber = fNumber;

    DrawContent();
}

//删除字体
void TempWnd::deleteTextFont()
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

//设置文本颜色
void TempWnd::setTextColor(QColor textColor)
{
    m_textColor = textColor;
    DrawContent();

}

//设置标题
void  TempWnd::setTitle(QString strTitle)
{
    m_strTitle = strTitle;

}




