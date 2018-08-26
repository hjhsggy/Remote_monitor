#include "stripwnd.h"

#include "infownd.h"

StripWnd::StripWnd(QWidget *parent,QRect rc) : DrawWnd(parent)
{
    m_colStrip =QColor::fromRgb(0,255,0);

    m_rcSize = rc;
    this->setGeometry(rc);

    //初始化Pixmap
    InitUserDC();


    //设置线条尺寸
    for(int i=0;i<CIW_COL*CIW_ROW;i++)
    {
        m_Strip[i].SetStripSize(rc);
    }

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

    if(0 !=InfoWnd::m_pCurInfoWnd)
    {
        QString strCID = InfoWnd::m_pCurInfoWnd->GetCID();

        //找到和当前选中的客户端窗口ID，对象的线条
        for(int i=0;i<CIW_COL*CIW_ROW;i++)
        {

            if(m_Strip[i].GetCID().compare(strCID) == 0)
            {
                //画内容
                m_Strip[i].Draw(&painter);
                break;
            }

        }

    }

    painter.end();

    //重绘
    this->update();
}



//设置偏移量
void StripWnd::SetStripOffSet(int nOffSet)
{
    for(int i=0;i<CIW_ROW*CIW_COL;i++)
    {
        m_Strip[i].SetStripOffSet(nOffSet);
    }

    //重绘
    DrawContent();
}

//添加数据点
void StripWnd::AddPoint(uchar *pData, int nLen,QString strCID)
{
    int iIndex;

    int i;

    for(i=0;i<CIW_COL*CIW_ROW;i++)
    {
        if(m_Strip[i].GetCID().compare(strCID) == 0)
        {
            iIndex = i;
            break;
        }
    }

    for(i=0;i<nLen;i++)
    {
        m_Strip[iIndex].AddPoint(pData[i]);
    }

    //重绘
    DrawContent();
}

//设置线条颜色
void StripWnd::SetStripColor(QColor colStrip)
{
    m_colStrip = colStrip;
}

void  StripWnd::SetAllCID(QString strCIDS)
{
    //C000001,C000002,
    int begin,end,i=0;

    begin=end=0;

    QString strID;

    while(begin < strCIDS.length())
    {
        end = strCIDS.indexOf(",",begin) - 1;
        strID = strCIDS.mid(begin,end-begin+1);

        m_Strip[i].SetCID(strID);

        begin = end + 2;
        i++;
    }
}


