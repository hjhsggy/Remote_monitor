#include "textwnd.h"

TextWnd::TextWnd(QWidget *parent,QRect rc) :
    DrawWnd(parent)
{
    //设置文本颜色
    m_textColor = QColor::fromRgb(0,255,0);

    m_strTitle = "心率";

    m_fNumber = 60.0f;

    m_ftTitle = NULL;
    m_ftNumber = NULL;

    //设置字体
    setTextFont();

    m_rcSize = rc;

    //设置控件位置
    this->setGeometry(rc);

    //初始化Pixmap
    InitUserDC();

    //画内容
    DrawContent();
}

TextWnd::~TextWnd()
{
    //删除字体
    deleteTextFont();
}


//绘制内容
void TextWnd::DrawContent()
{
    QPainter painter;
    painter.begin(m_pixMem);

    //窗口内部大小
    QRect rc(QPoint(0, 0),QSize(m_rcSize.width(), m_rcSize.height()));

    //画背景
    painter.fillRect(rc,m_backColor);

    int nBorder = 3;

    //设置文本颜色
    painter.setPen(m_textColor);

    painter.setFont(*m_ftTitle);

    //画文本
    QFontMetrics fm = painter.fontMetrics();

    //ascent是指从一个字的基线(baseline)到最顶部的距离
    int nPos = fm.ascent()+nBorder;

    //把nPos值作为基线，绘制文本
    painter.drawText(nBorder, nPos,m_strTitle);


    QRect  rcText = rc;
    //获取字体大小
    int nSize = m_ftTitle->pointSize();
    rcText.setTop(nBorder+nSize);

    //设置字体
    painter.setFont(*m_ftNumber);

    QString strNumber = QString("%1").arg((int)m_fNumber);

    //居中输出文本
    painter.drawText(rcText,Qt::AlignCenter,strNumber);

    painter.end();

    //重绘
    update();

}

//设置字体
void TextWnd::setTextFont(int nTitle,int nNumber)
{
    deleteTextFont();

    m_ftTitle = new QFont("黑体",nTitle);

    m_ftNumber = new QFont("Arial",nNumber,QFont::Bold);
}

//设置数字
void TextWnd::setNumber(float  fNumber)
{
    m_fNumber = fNumber;

    //重绘
    DrawContent();
}

//删除字体
void TextWnd::deleteTextFont()
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
void TextWnd::setTextColor(QColor textColor)
{
    m_textColor = textColor;

    DrawContent();

}

//设置标题
void TextWnd::setTitle(QString strTitle)
{
    m_strTitle = strTitle;

}

