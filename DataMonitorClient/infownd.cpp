#include "infownd.h"

#include <QMessageBox>
#include <QTimer>
#include <QApplication>

QList<InfoWnd*>  InfoWnd::m_InfoWndList;//控件列表
InfoWnd*         InfoWnd::m_pCurInfoWnd = 0;//当前选中的窗口
ThresholdDialog*   InfoWnd::m_pDlgThreshold = 0;

InfoWnd::InfoWnd(QWidget *parent,QRect rc) : DrawWnd(parent)
{
    m_strCID =tr("CXXXXXX");
    m_strHR = tr("65");
    m_strSpO2	= tr("98");
    m_strABP	= tr("120/75(100)");
    m_strResp	= tr("18");
    m_strTemp	= tr("35.7");

    m_colCID = qRgb(127,127,127);
    m_colHR = qRgb(0,255,0);
    m_colSpO2	= qRgb(175,0  ,0);
    m_colABP	= qRgb(0  ,255,0);
    m_colResp	= qRgb(255,255,0);
    m_colTemp	= qRgb(255,128,0);

    m_colFrame = qRgb(0,0,0);

    m_ftText = QFont("Arial",10,QFont::Bold,true);

    m_rcSize = rc;

    m_state = UNSELECT;

    m_uTimerWarnning = 0;

    m_pSound = new QSound("123.wav", this); //构建对象

    //设置控件位置
    this->setGeometry(rc);

    //初始化Pixmap
    InitUserDC();

    //画内容
    DrawContent();

    //创建按钮
    QRect rcCtrl;
    QRect rcClient = this->rect();

    rcCtrl.setLeft(rcClient.right() - 25);
    rcCtrl.setTop(rcClient.top() + 5);
    rcCtrl.setRight(rcCtrl.left() +16);
    rcCtrl.setBottom(rcCtrl.top() + 16);

    m_btnThreshold = new QPushButton(this);
    m_btnThreshold->setGeometry(rcCtrl);
    m_btnThreshold->setStyleSheet("QPushButton{border-image: url(:/Images/orgchartpart.codeplex.com.ico);}"
                                  "QPushButton:hover{border-image: url(:/Images/qun.qq.com.ico);}");

    //设置信号和槽
    connect(m_btnThreshold,SIGNAL(clicked()),this,SLOT(slotBtnThreshold()));
}

InfoWnd::~InfoWnd()
{
    if(0 != m_btnThreshold)
    {
        delete m_btnThreshold;
        m_btnThreshold = 0;
    }
}

//获取CID
QString InfoWnd::GetCID() const
{
    return m_strCID;
}

//设置CID
void InfoWnd::SetCID(QString CID)
{
    m_strCID = CID;

    DrawContent();
}

void InfoWnd::SetMedNum(const MED_NUM& medNum)
{
    //报警
    if(IsWarnning(medNum))
    {
        if(m_uTimerWarnning == 0)
        {
            //报警
            m_state = WARNING;

            m_uTimerWarnning = startTimer(500);
        }
    }


    m_strHR.sprintf("%d",medNum.HR);
    m_strSpO2.sprintf("%d",medNum.Sp02);
    m_strABP.sprintf("%d/%d(%d)",medNum.ABPMax,
                     medNum.ABPMin,medNum.ABPCur);
    m_strResp.sprintf("%d",medNum.Resp);
    m_strTemp.sprintf("%.1f",medNum.Temp);

    DrawContent();
}


void  InfoWnd::SetAllCID(QString strCIDS)
{
    //C000001,C000002,C000003,
    int begin,end,i=0;

    begin=end=0;

    QString strID;

    while(begin < strCIDS.length())
    {

        end = strCIDS.indexOf(",",begin) - 1;
        strID = strCIDS.mid(begin,end-begin+1);

        InfoWnd* pWnd = (InfoWnd*)m_InfoWndList[i];

        pWnd->SetCID(strID);

        begin = end + 2;

        i++;
    }
}



//绘制内容
void InfoWnd::DrawContent()
{
    QPainter painter;
    painter.begin(m_pixMem);

    //设置字体
    painter.setFont(m_ftText);

    //文字反走样
    painter.setRenderHint(QPainter::TextAntialiasing);

    //窗口内部大小
    QRect rc(QPoint(0, 0),QSize(m_rcSize.width(), m_rcSize.height()));

    //画背景
    painter.fillRect(rc,m_backColor);


    QRect rcText;
    rcText = rc;

    //CID
    rcText.setLeft(rc.left() + 5);
    rcText.setBottom(rc.height()/4);

    painter.setPen(m_colCID);
    painter.drawText(rcText,Qt::AlignVCenter|Qt::AlignLeft,m_strCID);


    //HR
    rcText.setRight(rc.width()/2);
    rcText.setTop(rcText.bottom());
    rcText.setBottom(rcText.top() + rc.height()/4);

    painter.setPen(m_colHR);
    painter.drawText(rcText,Qt::AlignVCenter|Qt::AlignLeft,m_strHR);

    //SpO2
    rcText.setLeft(rcText.right());
    rcText.setRight(rc.right());

    painter.setPen(m_colSpO2);
    painter.drawText(rcText,Qt::AlignVCenter|Qt::AlignLeft,m_strSpO2);

    //ABP
    rcText.setTop(rcText.bottom());
    rcText.setBottom(rcText.top() + rc.height()/4);
    rcText.setLeft(rc.left()+5);
    rcText.setRight(rc.right());

    painter.setPen(m_colABP);
    painter.drawText(rcText,Qt::AlignLeft|Qt::AlignTop,m_strABP);

    //Resp
    rcText.setTop(rcText.bottom());
    rcText.setBottom(rcText.top() + rc.height()/4);
    rcText.setRight(rc.width()/2);

    painter.setPen(m_colResp);
    painter.drawText(rcText,Qt::AlignLeft|Qt::AlignTop,m_strResp);

    //Temp
    rcText.setLeft(rcText.right());
    rcText.setRight(rc.right());

    painter.setPen(m_colTemp);
    painter.drawText(rcText,Qt::AlignLeft|Qt::AlignTop,m_strTemp);

    //画边框
    switch(m_state)
    {
    case SELECT:
        m_colFrame = qRgb(0,255,0);
        break;
    case UNSELECT:
        m_colFrame = qRgb(0,0,0);
        break;
    case WARNING:
        m_colFrame = qRgb(255,0,0);
        break;
    }

    QPen pen(m_colFrame,5,Qt::SolidLine);
    painter.setPen(pen);
    painter.drawRect(rc);


    painter.end();

    //重绘
    update();
}

//设置状态
void InfoWnd::SetState(CIW_STATE state)
{
    m_state = state;

    DrawContent();
}

//鼠标双击事件
void InfoWnd::mouseDoubleClickEvent(QMouseEvent *e)
{
    //如果是左键双击
    if(e->button() == Qt::LeftButton)
    {
        //设置当前窗口状态
        this->SetState(SELECT);

        //设置当前选中的窗口
        InfoWnd::m_pCurInfoWnd = this;

        for(int i=0;i<CIW_COL*CIW_ROW;i++)
        {
            InfoWnd* pWnd = (InfoWnd*)m_InfoWndList.at(i);

            //不是当前窗口
            if(this != pWnd)
            {
                pWnd->SetState(UNSELECT);
            }

        }

        killTimer(m_uTimerWarnning);
        m_uTimerWarnning = 0;

    }
}

//阈值按钮响应
void InfoWnd::slotBtnThreshold()
{
    if(0 == m_pDlgThreshold)
    {
        m_pDlgThreshold = new ThresholdDialog;
        m_pDlgThreshold->setModal(false);
    }

    m_pDlgThreshold->show();

    m_pDlgThreshold->SetThreshold(m_Threshold);
    m_pDlgThreshold->SetCurInfoWnd(this);

}

void InfoWnd::SetThreshold(THRESHOLD thd)
{
    m_Threshold = thd;
}

THRESHOLD InfoWnd::GetThreshold() const
{
    return m_Threshold;
}

//窗口定时器事件
void InfoWnd::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == m_uTimerWarnning)
    {
        m_state = static_cast<CIW_STATE>(UNSELECT+ WARNING - m_state);

        //::PlaySound(TEXT("123.wav"), NULL, SND_FILENAME | SND_ASYNC);

        m_pSound->play();//播放

        DrawContent();
    }
}

//窗口关闭事件
void InfoWnd::closeEvent(QCloseEvent *e)
{
    killTimer(m_uTimerWarnning);
    m_uTimerWarnning = 0;
}

//是否报警
bool InfoWnd::IsWarnning(const MED_NUM &MedNum)
{
    bool ret = false;

    if(MedNum.HR < m_Threshold.HRMin || MedNum.HR > m_Threshold.HRMax)
    {
        ret = true;
    }

    if(MedNum.Sp02 < m_Threshold.SpO2Min)
    {
        ret = true;
    }

    if( MedNum.Resp < m_Threshold.RespMin|| MedNum.Resp > m_Threshold.RespMax)
    {
        ret = true;
    }

    if( MedNum.Temp < m_Threshold.TempMin|| MedNum.Temp > m_Threshold.TempMax)
    {
        ret = true;
    }

    return ret;
}
