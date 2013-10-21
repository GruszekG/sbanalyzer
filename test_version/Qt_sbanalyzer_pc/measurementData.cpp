#include "measurementData.h"

#include <QDebug>

QVector<measurementData> ExtractData(QByteArray data)
{
    QVector<measurementData> measurements;

    while(data.size()/frameLenght != 0)
    {
        data.remove(0,1);//removing start char
        QByteArray rawData = data;
        rawData.truncate(16);

        quint8 controlSumThere = data.at(16);
        data.remove(0,17);

        quint8 controlSumHere = 0;
        for(int j = 0; j<16; j++)//calculate control sum
        {
            controlSumHere += rawData[j];
        }
        if(controlSumThere == controlSumHere)//check control sum
        {
           measurementData temp;

           temp.ax.as_bytes.lo = rawData.at(6);
           temp.ax.as_bytes.hi = rawData.at(7);
           temp.ay.as_bytes.lo = rawData.at(8);
           temp.ay.as_bytes.hi = rawData.at(9);
           temp.az.as_bytes.lo = rawData.at(10);
           temp.az.as_bytes.hi = rawData.at(11);

           temp.gx.as_bytes.lo = rawData.at(0);
           temp.gx.as_bytes.hi = rawData.at(1);
           temp.gy.as_bytes.lo = rawData.at(2);
           temp.gy.as_bytes.hi = rawData.at(3);
           temp.gz.as_bytes.lo = rawData.at(4);
           temp.gz.as_bytes.hi = rawData.at(5);

           temp.an_gx.as_bytes.lo = rawData.at(12);
           temp.an_gx.as_bytes.hi = rawData.at(13);
           temp.an_gz.as_bytes.lo = rawData.at(14);
           temp.an_gz.as_bytes.hi = rawData.at(15);

            measurements.append(temp);
        }
        else
        {
            qDebug()<<"Invalid frame detected";
        }
    }

    return measurements;
}
