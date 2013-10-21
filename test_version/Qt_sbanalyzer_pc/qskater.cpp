#include "qskater.h"
#include <QDebug>

QSkater::QSkater():
    training('0'),
    age('0'),
    number('0'),
    name("name"),
    footStance("stance"),
    city("city"),
    email("email@com"),
    info("non")
{

}

QSkater::QSkater(QByteArray data)
{
    int index;
    bool ok;

    index = data.indexOf(';');

    QByteArray temp = data.left(index);
    data.remove(0, index+1);
    number = temp.toInt(&ok, 10);
    index = data.indexOf(';');

    name = data.left(index);
    data.remove(0, index+1);

    index = data.indexOf(';');
    footStance = data.left(index);
    data.remove(0, index+1);

    index = data.indexOf(';');
    city = data.left(index);
    data.remove(0, index+1);

    index = data.indexOf(';');
    email = data.left(index);
    data.remove(0, index+1);

    index = data.indexOf(';');
    info = data.left(index);
    data.remove(0, index+1);


    index = data.indexOf(';');
    training = data.left(index);
    //training = temp.toInt(&ok, 10);
    data.remove(0, index+1);

    index = data.indexOf(';');
    age = data.left(index);

    //age = temp.toInt(&ok, 10);
}

QSkater::~QSkater()
{
//    delete name;
//    delete footStance;
//    delete city;
//    delete email;
}

void QSkater::copySkater(QSkater *skater)
{
    name = skater->getName();
    city = skater->getCity();
    email =skater->getEmail();
    info = skater->getInfo();
    footStance = skater->getFootStance();

    number = skater->getNumber();
    age = skater->getAge();
    training = skater->getTraining();

}

void QSkater::getInformation(QByteArray data)
{

}


