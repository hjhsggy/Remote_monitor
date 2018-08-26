#include "strip.h"

Strip::Strip()
{
    m_nCurPos = 0;
    m_nOffSet = 0;
}

Strip::~Strip()
{

}

//设置偏移量
void Strip::SetStripOffSet(int  nOffSet)
{
    m_nOffSet = nOffSet;
}

//绘制曲线
void Strip::Draw(QPainter* pDC)
{
    //如果没数据或者DC为空
    if(m_Data.empty() || NULL == pDC)
    {
        return;
    }

    //获取点数
    int nSize = m_Data.size();

    int nHeight = m_rcSize.height();

    //起始点
    int nXStart = 0;
    int nYStart = nHeight - m_Data[0] - m_nOffSet;

    //结束点
    int nXEnd = nXStart;
    int nYEnd = nYStart;

    //移动到起始点
    pDC->drawLine(nXStart,nYStart,nXEnd,nYEnd);


    //遍历数据点画线
    for(int i =0;i<nSize;i++)
    {
        nXEnd = i;
        nYEnd = nHeight- m_Data[i] - m_nOffSet;

        if(nXEnd != m_nCurPos)
        {
            //画线
            pDC->drawLine(nXStart,nYStart,nXEnd,nYEnd);
        }


        nXStart = nXEnd;
        nYStart = nYEnd;
    }
}

//设置波形窗口的大小
void Strip::SetStripSize(QRect rcSize)
{
    m_rcSize = rcSize;
}

//添加数据点
void Strip::AddPoint(uchar uData)
{
    //获取波形窗口的宽度
    int nWidth = m_rcSize.width();

    int nSize = m_Data.size();

    //如果数据未满
    if(nSize < nWidth)
    {
        //加入元素
        m_Data.push_back(uData);
    }
    else
    {
        m_nCurPos = m_nCurPos % nWidth;

        m_Data[m_nCurPos] = uData;

        m_nCurPos++;
    }
}


//获取客户端ID
QString Strip::GetCID() const
{
    return m_strCID;
}

//设置客户端ID
void Strip::SetCID(QString strCID)
{
    m_strCID = strCID;
}
