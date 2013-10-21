#ifndef QSkater_H
#define QSkater_H

#include <QString>

class QSkater
{
public:
    QSkater();
    QSkater(QByteArray data);

    ~QSkater();

private:
    int number;
    QString name;
    QString footStance;
    QString training;
    QString age;
    QString city;
    QString email;
    QString info;

public:
    void getInformation(QByteArray data);
    inline QString getName(){return name;}
    inline QString getFootStance(){return footStance;}
    inline QString getCity(){return city;}
    inline QString getEmail(){return email;}
    inline QString getInfo(){return info;}
    inline QString getTraining(){return training;}
    inline QString getAge(){return age;}
    inline int getNumber(){return number;}

    inline void setName(QString na){name = na;}
    inline void setFootStance(QString fo){footStance = fo;}
    inline void setCity(QString ci){city = ci;}
    inline void setEmail(QString em){email = em;}
    inline void setInfo(QString in){info = in;}
    inline void setAge(QString ag){age = ag;}
    inline void setTraining(QString tr){training = tr;}
    inline void setNumber(int nr){number = nr;}

    void copySkater(QSkater *skater);

};



#endif // QSkater_H
