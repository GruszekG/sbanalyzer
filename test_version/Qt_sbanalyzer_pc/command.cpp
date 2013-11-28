
#include "command.h"
#include"QDebug"

Cmd::Cmd(void)
    :CmdID(0)
    ,CheckSum(0)
    ,CmdLength(0)
    ,EndByte(0x0d)
{
}

HelloCmd::HelloCmd(void)
{
    CmdID = Hello_Cmd;
}

unsigned char Cmd::getCmdID(void)
{
    return CmdID;
}

unsigned char Cmd::getCheckSum(void)
{
    return CheckSum;
}

QString Cmd::getCmdIDStr(void)
{
    QString _cmd("dupa");
    if(CmdID == 0)
        QString("Empty CMD");
    else if (CmdID == Measure_Cmd)
        QString("Measure_Cmd");
    else if (CmdID == Config_Cmd)
        QString("Config_Cmd");
    else if (CmdID == Info_Cmd)
        QString("Info_Cmd");
    else if (CmdID == WriteReg_Cmd)
        QString("WriteReg_Cmd");
    else if (CmdID == ReadReg_Cmd)
        QString("ReadReg_Cmd");

    return _cmd;
}
QString Cmd::getCheckSumStr(void)
{
    QString _checkSum;
    _checkSum = QString::number(CheckSum);

    return _checkSum;
}

void Cmd::setCheckSum(unsigned char _checkSum)
{
    CheckSum = _checkSum;
}

void Cmd::setCmdID(QString _CheckID)
{
    if(_CheckID == QString("Measure_Cmd"))
        CmdID = Measure_Cmd;
    else  if(_CheckID == QString("Info_Cmd"))
        CmdID = Info_Cmd;
    else  if(_CheckID == QString("WriteReg_Cmd"))
        CmdID = WriteReg_Cmd;
    else  if(_CheckID == QString("ReadReg_Cmd"))
        CmdID = ReadReg_Cmd;
    else  if(_CheckID == QString("Config_Cmd"))
        CmdID = ReadReg_Cmd;
    else
        CmdID = 0;
}

void Cmd::setCmdID(unsigned char _ID)
{
    if((_ID>0)&&(_ID<CmdCount))
        CmdID = _ID;
    else
        CmdID = 0;
}

InfoCmd::InfoCmd(void)
    :LIS3DHFreq(0)
    ,LIS3DHRange(0)
    ,L3G4200DFreq(0)
    ,L3G4200DRange(0)
    ,BatteryLevel(0)
    ,MeasuermentTime(5)
{

}

QString InfoCmd::printMeasurementTime()
{
    return QString::number(MeasuermentTime, 10) + QString(" s");
}

/*virtual*/ bool InfoCmd::loadCmd(const char *_cmd)
{
    qDebug()<<"LODA CMD";
    if(checkInfoCmd(_cmd))
    {
        for(int i =0; i<6; i++)
            qDebug()<<"dane"<<i<<": "<<(unsigned char)_cmd[i];
        CmdID = _cmd[0];
        LIS3DHFreq  = _cmd[1];
        LIS3DHRange = _cmd[2];
        L3G4200DFreq = _cmd[3];
        L3G4200DRange = _cmd[4];
        MeasuermentTime = ((quint16)_cmd[5]*0x10) + (quint16)_cmd[6];
        BatteryLevel = _cmd[7];
        CheckSum = _cmd[8];
        CmdLength = 0x09;
        qDebug()<<"CMD OK";
        qDebug()<<"ID"<<(unsigned char)CmdID;
        qDebug()<<"Lisfreq"<<(unsigned char)LIS3DHFreq;
        qDebug()<<"LIS3DHRange"<<(unsigned char)LIS3DHRange;
        qDebug()<<"L3G4200DFreq"<<(unsigned char)L3G4200DFreq;
        qDebug()<<"L3G4200DRange"<<(unsigned char)L3G4200DRange;
        qDebug()<<"BatteryLevel"<<(unsigned char)BatteryLevel;
        qDebug()<<"END INFO";
        return true;
    }else
    {
        qDebug()<<"CMD ERROR";
        return false;
    }

}

bool InfoCmd::checkInfoCmd(const char* _bufor)
{
    if(_bufor[0] != Info_Cmd)
    {
        qDebug()<<"ID ERROR";
                return false;
    }
    unsigned char _checkSum = 0;
    for(int i = 0 ; i < 8; i++)
        _checkSum+=_bufor[i];
    if(_checkSum != (unsigned char)_bufor[8])
    {
        qDebug()<<"CHECKSUM ERROR. MB: "<<(unsigned char)_bufor[8]<<" QT: "<<(unsigned char)_checkSum;
        return false;
    }
    if(_bufor[9] != 0x0d)
    {
        qDebug()<<"END BYTE ERROR";
        return false;
    }
    return true;
}

QString InfoCmd::printCmd()
{
    QString _info("Actual measurement board setting.\n");
    _info += QString("Measurement freqency: ") + printFreqSet() + QString(".\n");
    _info += QString("LIS3DH range: ") + printAccRange() + QString(".\n");
    _info += QString("L3G4200D range: ") + printGyroRange() + QString(".\n");
    _info += QString("Measurement time: ") + printMeasurementTime() + QString(".\n");
    _info += QString("Battery level: ") + printBatteryLevel() + QString(".\n");
    return _info;
}

QString InfoCmd::printAccRange()
{
    QString _range;
    qDebug()<<"LIS3DHRange"<<LIS3DHRange;
    if(LIS3DHRange == LIS3DH_2G)
        _range = "+-2 g";
    else if(LIS3DHRange == LIS3DH_4G)
        _range = "+-4 g";
    else if(LIS3DHRange == LIS3DH_8G)
        _range = "+-8 g";
    else if(LIS3DHRange == LIS3DH_16G)
        _range = "+-16 g";
    else
        _range = "invalid settings";

    return _range;
}

QString InfoCmd::printFreqSet()
{
    QString _freq;
    qDebug()<<"L3G4200DFreq"<<L3G4200DFreq;
    if(L3G4200DFreq == L3G4200D_100Hz)
        _freq = "100 Hz";
    else if(L3G4200DFreq == L3G4200D_200Hz)
        _freq = "200 Hz";
    else if(L3G4200DFreq == L3G4200D_400Hz)
        _freq = "400 Hz";
    else if(L3G4200DFreq == L3G4200D_800Hz)
        _freq = "800 Hz";
    else
        _freq = "invalid settings";

    return _freq;
}

QString ConfCmd::printConfig()
{
    QString _info("Settings:\n");
    _info += QString("Measurement freqency: ") + printFreqSet() + QString(".\n");
    _info += QString("LIS3DH range: ") + printAccRange() + QString(".\n");
    _info += QString("L3G4200D range: ") + printGyroRange() + QString(".\n");
    _info += QString("Measurement time: ") + printMeasurementTime() + QString(".\n");
    return _info;
}

QString InfoCmd::printGyroRange()
{
    QString _range;
    qDebug()<<"L3G4200DRange"<<L3G4200DRange;
    if(L3G4200DRange == L3G4200D_250dps)
        _range = "+-250 dps";
    else if(L3G4200DRange == L3G4200D_500dps)
        _range = "+-500 dps";
    else if(L3G4200DRange == L3G4200D_2000dps)
        _range = "+-2000 dps";
    else
        _range = "invalid settings";

    return _range;
}

QString InfoCmd::printBatteryLevel()
{
    return QString("%1/100").arg(BatteryLevel);
}

MeasureCmd::MeasureCmd(void)
    :MeasureStartDelay(2)
{

}

void MeasureCmd::loadMeasureCmd(unsigned char _time)
{
    if(_time<16)
    {
        CmdID = Measure_Cmd;
        MeasureStartDelay = _time;
        CheckSum = CmdID + MeasureStartDelay;
        EndByte = 0x0d;
    }
}

QByteArray MeasureCmd::getMeasureCmd()
{
    QByteArray _cmd;
    _cmd.push_back(CmdID);
    _cmd.push_back(MeasureStartDelay);
    _cmd.push_back(CheckSum);
    _cmd.push_back(EndByte);

    qDebug()<<"Check SUM: "<<CheckSum;

    return _cmd;
}

ConfCmd::ConfCmd()
{
    CmdID = Config_Cmd;
}

ConfCmd::ConfCmd(ConfCmd *_cmd)
//ConfCmd* ConfCmd::operator =(ConfCmd _cmd)
{
    MeasuermentTime = _cmd->getMeasurementTime();
    LIS3DHFreq = _cmd->getAccFreq();
    LIS3DHRange = _cmd->getAccRange();
    L3G4200DFreq = _cmd->getGyroFreq();
    L3G4200DRange = _cmd->getGyroRange();
   // return &_cmd;
}

ConfCmd::ConfCmd(InfoCmd _cmd)
{
    MeasuermentTime = 5;
    LIS3DHFreq = _cmd.getAccFreq();
    LIS3DHRange = _cmd.getAccRange();
    L3G4200DFreq = _cmd.getGyroFreq();
    L3G4200DRange = _cmd.getGyroRange();
}

QByteArray HelloCmd::getHelloCmd()
{
    QByteArray _cmd;
    _cmd.push_back(CmdID);
    _cmd.push_back(EndByte);

    return _cmd;
}

void ConfCmd::setFreq(L3G4200D_ODR _freq)
{
    L3G4200DFreq = _freq;

    if(_freq == L3G4200D_100Hz)
        LIS3DHFreq = LIS3DH_100Hz;
    else if(_freq == L3G4200D_200Hz)
        LIS3DHFreq = LIS3DH_200Hz;
    else if (_freq == L3G4200D_400Hz)
        LIS3DHFreq =LIS3DH_400Hz;
    else if (_freq == L3G4200D_800Hz)
        LIS3DHFreq = LIS3DH_12500Hz;
}

QByteArray ConfCmd::getConfCmdToBuf()
{
    QByteArray _bufor;
    uint16byBytes _time;
    _time.as_word = MeasuermentTime;

    updateCheckSum();

    _bufor.push_back(CmdID);
    _bufor.push_back(LIS3DHFreq);
    _bufor.push_back(LIS3DHRange);
    _bufor.push_back(L3G4200DFreq);
    _bufor.push_back(L3G4200DRange);
    _bufor.push_back(_time.as_bytes.hi);
    _bufor.push_back(_time.as_bytes.lo);
    _bufor.push_back(CheckSum);
    _bufor.push_back(0x0d);
    qDebug()<<"CMD ID:"<< (unsigned int) CmdID;
    qDebug()<<"LIS3DHFreq:"<< (unsigned int) LIS3DHFreq;
    qDebug()<<"LIS3DHRange:"<< (unsigned int) LIS3DHRange;
    qDebug()<<"L3G4200DFreq:"<< (unsigned int) L3G4200DFreq;
    qDebug()<<"L3G4200DRange:"<< (unsigned int) L3G4200DRange;
    qDebug()<<"_time.as_bytes.hi"<< (unsigned int) _time.as_bytes.hi;
    qDebug()<<"_time.as_bytes.lo"<< (unsigned int) _time.as_bytes.lo;
    qDebug()<<"CheckSum"<< (unsigned int) CheckSum;

    return _bufor;
}

void ConfCmd::updateCheckSum()
{
    uint16byBytes _time;
    _time.as_word = MeasuermentTime;
    CheckSum =
            CmdID +
            LIS3DHFreq +
            LIS3DHRange +
            L3G4200DFreq +
            L3G4200DRange +
            _time.as_bytes.hi +
            _time.as_bytes.lo;
}

