#include <QtGui/QApplication>
#include "mainwindow.h"
#include "dealer.h"
#include <QPushButton>
#include <QObject>
#include <QDialog>
#include <QFileDialog>
#include <QMap>
#include <QtGlobal>
#include <QDebug>

QMap<QString,long long> tmap;
QMap<long long, cell> xxyy;
long long pt[50];

void init()
{
    QFile ts("ss.txt");
    ts.open(QFile::ReadWrite);
    QTextStream in(&ts);
    QString s;
    long long dex=1;
    cell tcell;
    for(int i=0;i<7;i++)
    {
        tcell.x=i;
        in >> s;
        tmap.insert(s,dex);
        tcell.y=1;
        xxyy.insert(dex,tcell);
        dex=dex<<1;
        in >> s;
        tmap.insert(s,dex);
        in >> s;
        tmap.insert(s,dex);
        tcell.y=2;
        xxyy.insert(dex,tcell);
        dex=dex<<1;
        in >> s;
        tmap.insert(s,dex);
        in >> s;
        tmap.insert(s,dex);
        tcell.y=3;
        xxyy.insert(dex,tcell);
        dex=dex<<1;
        in >> s;
        tmap.insert(s,dex);
        tcell.y=4;
        xxyy.insert(dex,tcell);
        dex=dex<<1;
        in >> s;
        tmap.insert(s,dex);
        in >> s;
        tmap.insert(s,dex);
        tcell.y=5;
        xxyy.insert(dex,tcell);
        dex=dex<<1;
    }
    for(long long i=0;i<36;i++)
    {
        pt[i]=(long long) 1<<i;
//        qDebug() << i << ' ' << pt[i];
    }
//    for(QMap<QString,long long>::iterator p=tmap.begin();p!=tmap.end();p++)
//        std::cerr << qPrintable(p.key()) << ":" << (long long)p.value() << std::endl;
//    for(QMap<long long, cell>::iterator p=xxyy.begin();p!=xxyy.end();p++)
//        qDebug() << p.key() << ":" << (p.value()).x << ' ' << (p.value().y) << endl;
}

int main(int argc, char *argv[])
{
    init();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
