#ifndef INFOWND_H
#define INFOWND_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QSound>

#include "drawwnd.h"
#include "../Common/UserType.h"

#include <QList>

#include "ThresholdDialog.h"

class InfoWnd : public DrawWnd
{
    Q_OBJECT
public:
    explicit InfoWnd(QWidget *parent,QRect rc);
    ~InfoWnd();

    static QList<InfoWnd*>  m_InfoWndList;//控件列表
    static InfoWnd*         m_pCurInfoWnd;//当前选中的窗口
    static ThresholdDialog*   m_pDlgThreshold;
public:
    QString GetCID() const;
    void SetCID(QString CID);
    void SetState(CIW_STATE state);
    void SetMedNum(const MED_NUM& medNum);
    static void  SetAllCID(QString strCIDS);

    void SetThreshold(THRESHOLD thd);
    THRESHOLD GetThreshold() const;
protected:
    virtual void DrawContent();//绘制内容
    void mouseDoubleClickEvent(QMouseEvent *e);//鼠标双击事件
    void timerEvent(QTimerEvent *e);//窗口定时器事件
    void closeEvent(QCloseEvent *e);//窗口关闭事件
private:
    QString		m_strCID;
    QString		m_strHR;
    QString		m_strSpO2;
    QString		m_strABP;
    QString		m_strResp;
    QString		m_strTemp;

    QColor      m_colCID;
    QColor      m_colHR;
    QColor      m_colSpO2;
    QColor      m_colABP;
    QColor      m_colResp;
    QColor      m_colTemp;
    QColor      m_colFrame;

    QFont       m_ftText;
    CIW_STATE	m_state;

    QPushButton *m_btnThreshold;
    THRESHOLD	m_Threshold;//阈值

    uint		m_uTimerWarnning;//报警定时器

    QSound *m_pSound;//播放声音

protected:
    QRect       m_rcSize;//窗口的位置和大小

    bool IsWarnning(const MED_NUM &MedNum);

signals:

public slots:
    void  slotBtnThreshold();//阈值按钮响应

};

#endif // INFOWND_H
