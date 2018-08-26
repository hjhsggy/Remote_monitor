#ifndef USERTYPE
#define USERTYPE
//功能号
typedef enum{LOGIN = 1, LOGOUT, LOGINOK, LOGINERR, STOPSERVER, TRANSMIT}FUNCTION;
typedef enum{SELECT,UNSELECT,WARNING}CIW_STATE;

//医疗数据
typedef struct
{
    uchar  HR;
    uchar  Sp02;
    uchar  ABPMax;
    uchar  ABPMin;
    uchar  ABPCur;
    uchar  Resp;
    float  Temp;

}MED_NUM;

//线条数据
typedef struct
{
    uchar  ECG[128];
    int    ECGLen;
    uchar  Sp02[128];
    int    Sp02Len;
    uchar  Resp[128];
    int    RespLen;
}MED_STRIP;



//数据包
typedef struct
{
    FUNCTION	fun;
    char		SenderID[32];//发送者ID
    char		ReverID[32];//接收者ID
    char		Content[256];//内容

    MED_NUM     MedNum;//医疗数据
    MED_STRIP	MedStrip;//线条数据

}NET_PACK;

typedef struct
{
	uchar HRMin;
	uchar HRMax;

	uchar SpO2Min;

	uchar RespMin;
	uchar RespMax;

	float TempMin;
	float TempMax;
}THRESHOLD;

#define CIW_ROW   8
#define CIW_COL   2

#endif // USERTYPE

