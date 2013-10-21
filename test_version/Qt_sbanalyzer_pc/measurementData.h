#ifndef MEASUREMENTDATA_H
#define MEASUREMENTDATA_H

#include <QVector>
#include <QByteArray>

#define frameLenght 18


union int16byBytes
{
  struct {
    quint8 lo;
    quint8 hi;
  } as_bytes;
  qint16 as_word;
};


typedef struct{
    union int16byBytes ax;
    union int16byBytes ay;
    union int16byBytes az;
    union int16byBytes gx;
    union int16byBytes gy;
    union int16byBytes gz;
    union int16byBytes an_gx;
    union int16byBytes an_gz;
}measurementData;

QVector<measurementData> ExtractData(QByteArray data);

#endif // MEASUREMENTDATA_H
