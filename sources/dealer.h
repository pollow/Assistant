#ifndef DEALER_H
#define DEALER_H

#include <QtCore/QCoreApplication>
#include <QDir>
#include <QDataStream>
#include <QFile>
#include <iostream>
#include <fstream>
#include <string>
#include <QTextStream>
#include <QChar>
#include <QTextCodec>
#include <vector>
#include <QMap>

class courses
{
public:
    QString code;
    QString cName;
    QString location;
    QString timeStr;
    long long int timeIndex;
    QString tName;
    double xf;
    int ks;
    int stars;
    courses()
    {
        timeIndex=0;
    }
};

class dealer
{
public:
    QString bracket(QString *, int flag);
    void extract(courses &tmp, QString *str);
    void work(QFile *,std::vector<courses> &all);
    void purify(courses &tmp, QString *str);
    QString operate(QFile *,std::vector<courses> &all);

private:
    QString sw,dw;
    int nflag;
};

#endif // DEALER_H
