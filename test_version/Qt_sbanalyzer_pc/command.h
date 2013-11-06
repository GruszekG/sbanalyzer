#ifndef COMMAND_H
#define COMMAND_H

#include "LIS3DH.h"
#include "L3G4200D.h"

#include <QString>

union uint16byBytes
{
  struct {
    quint8 lo;
    quint8 hi;
  } as_bytes;
  quint16 as_word;
};

enum CommandID_t
{
    Measure_Cmd = 0x01,

    Config_Cmd,

    WriteReg_Cmd,
    ReadReg_Cmd,

    Info_Cmd,

    CmdCount

};

class Cmd
{
    public:
    Cmd(void);
    unsigned char getCmdID(void);
    QString getCmdIDStr(void);
    unsigned char getCheckSum(void);
    QString getCheckSumStr(void);
    void setCmdID(unsigned char _ID);
    void setCmdID(QString _cmd);
    void setCheckSum(unsigned char _checkSum);

    protected:

    unsigned char CmdID;
    unsigned char CheckSum;
    unsigned char CmdLength;
    unsigned char	EndByte;

};
class MeasureCmd : public Cmd
{
    public:
    MeasureCmd(void);
    void loadMeasureCmd(unsigned char _time);
    unsigned char getMeasureTime(void);
    QByteArray getMeasureCmd();

    protected:
    unsigned char MeasureStartDelay; //time of measure in [s]


};

class InfoCmd : public Cmd
{
    public:
    InfoCmd(void);
    bool loadCmd(const char* _cmd);
    QString printCmd(void);
    bool checkInfoCmd(const char *_bufor);
    QString printFreqSet(void);
    QString printAccRange(void);
    QString printGyroRange(void);
    QString printBatteryLevel(void);
    QString printMeasurementTime();
    inline unsigned char getAccRange(void) {return LIS3DHRange;}
    inline unsigned char getGyroRange(void) {return L3G4200DRange;}
    inline unsigned char getAccFreq(void) {return L3G4200DFreq;}
    inline unsigned char getGyroFreq(void) {return L3G4200DFreq;}
    inline int getMeasurementTime(void) {return MeasuermentTime;}

    protected:
    unsigned char	LIS3DHFreq;
    unsigned char	LIS3DHRange;
    unsigned char	L3G4200DFreq;
    unsigned char	L3G4200DRange;
    quint16     MeasuermentTime;

    private:
    unsigned char	BatteryLevel;
};

class ConfCmd : public InfoCmd
{
    public:
    ConfCmd(void);
    ConfCmd(ConfCmd* _cmd);
    ConfCmd(InfoCmd _cmd);

    inline void setAccRange(LIS3DH_Range _range) { LIS3DHRange = _range;}
    void setFreq(L3G4200D_ODR _freq);
    inline void setGyroRange(L3G4200D_Range _range) {L3G4200DRange = _range;}
    inline void setTime(quint16 _time) {MeasuermentTime = _time;}
   // ConfCmd &operator=(ConfCmd _cmd);

    QString printConfig(void);
    QByteArray getConfCmdToBuf();
    void updateCheckSum(void);

};

#endif // COMMAND_H
