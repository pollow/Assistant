#include "dealer.h"
#include <QDebug>

extern QMap<QString,long long> tmap;

QString dealer::bracket(QString *str, int flag)
{
    int pa,pb;
    pa=str->indexOf("<td>");
    pb=str->indexOf("</td>");
    QString tmp=str->mid(pa+4,pb-pa-4);
    //std::cerr << qPrintable(tmp) << std::endl;
    str->remove(0,pb+5);
    if(flag){
        while(1){
            pa=tmp.indexOf("<");
            pb=tmp.indexOf(">");
            //std::cerr << pa << ' ' << pb << endl;
            if((pa!=-1)&&(pb!=-1)) tmp.remove(pa,pb-pa+1);
            else break;
        }
    }
    //std::cerr << qPrintable(tmp) << std::endl;
    return tmp;
}

void dealer::extract(courses &tmp, QString *str)
{
    tmp.code=bracket(str,1);
    tmp.cName=bracket(str,1);
    tmp.tName=bracket(str,1);
    bracket(str,1);
    tmp.timeStr=bracket(str,0);
    QString stmp=tmp.timeStr;
//    //qDebug() << stmp;
    while(stmp.indexOf(sw)!=-1)
    {
        int p=stmp.indexOf(sw);
        stmp.remove(p-1,4);
    }
    while(stmp.indexOf(dw)!=-1)
    {
        int p=stmp.indexOf(dw);
        stmp.remove(p-1,4);
    }
//    //qDebug() << stmp;
    tmp.timeIndex = 0;
    if(stmp.indexOf("<br>")!=-1)
    {
        int tx;
        while((tx=stmp.indexOf("<br>"))!=-1)
        {
            tmp.timeIndex|=tmap.value(stmp.mid(0,tx));
            if(!tmap.value(stmp.mid(0,tx))) {nflag=1;return;}
            stmp.remove(0,tx+4);
        }
    }
    tmp.timeIndex|=tmap.value(stmp);
    if(!tmap.value(stmp)){nflag=1;return;}
    tmp.location=bracket(str,0);
    tmp.location.replace("<br>","\n");
    tmp.stars=5;
}

void dealer::work(QFile *file, std::vector<courses> &all)
{
    QFile fn("s.txt");
    fn.open(QFile::ReadWrite);
    QTextStream fin(&fn);
    fin >> sw;
    fin >> dw;

//    //qDebug() << sw << ' ' << dw;

//    QFile file2("k.txt");
//    file2.open(QFile::WriteOnly|QFile::Truncate);
    if(!file->open(QFile::ReadWrite)) std::cerr << qPrintable(file->errorString());

    QTextStream in(file);
//    QTextStream out(&file2);
//    qDebug() << file2.errorString();
    QString str;
    QChar c;
    for(int i=0;i<200;i++) in >> c;
    while(1)
    {
        in >> c;
        str.push_back(c);
        if(str.right(7)=="</HTML>") break;
    }
    //std::cerr<<qPrintable(str);
//    out << str;
//    qDebug() << "I get here!";
//    qDebug() << str;
    QString g;
    int i;

    g="class=\"datagridhead\"";
    //std::cerr << qPrintable(g) << g.length() << std::endl;
    i=str.indexOf((&g));
    str.remove(0,i+g.length()+1);
//    qDebug() << str;

    g="</tr>";
    //std::cerr << qPrintable(g) << g.length() << std::endl;
    i=str.indexOf((&g));
    str.remove(0,i+g.length());
    //清除前部无效内容；循环去除</script>标签前面的东西
//    qDebug() << str;

    g="<fieldset>";
    //std::cerr << qPrintable(g) << g.length() << std::endl;
    str.chop(str.length()-str.indexOf(&g));
    //清除后部无效内容；
    //std::cerr << qPrintable(str) << endl;
    courses cc;
    int p_b;
    QString tmp;
//    out << str;
//    qDebug() << "the string is clean!";
//    qDebug() << str;

    while(str.length()>10)
   {
        p_b=str.indexOf("</tr>");
        tmp=str.mid(0,p_b+5);
        str.remove(0,p_b+5);
        nflag=0;
        extract(cc,&tmp);
        if(nflag) continue;
        all.push_back(cc);
        if(str.length()<20) break;
    }
//    std::vector<courses>::iterator p;
//    for(p=all.begin();p!=all.end();p++)
//    {
//        std::cerr << qPrintable(p->code) << std::endl << qPrintable(p->cName) << std::endl;
//    }
//    std::cerr << "Finished!" << std::endl;
}

void dealer::purify(courses &tmp, QString *str)
{
    tmp.tName=bracket(str,1);
    QString hours=bracket(str,1);
    bracket(str,1);
    tmp.timeStr=bracket(str,0);
    QString stmp=tmp.timeStr;
    while(stmp.indexOf(sw)!=-1)
    {
        int p=stmp.indexOf(sw);
        stmp.remove(p-1,4);
    }
    while(stmp.indexOf(dw)!=-1)
    {
        int p=stmp.indexOf(dw);
        stmp.remove(p-1,4);
    }
    tmp.timeIndex = 0;
    if(stmp.indexOf("<br>")!=-1)
    {
        int tx;
        while((tx=stmp.indexOf("<br>"))!=-1)
        {
            tmp.timeIndex|=tmap.value(stmp.mid(0,tx));
            if(!tmap.value(stmp.mid(0,tx))) {nflag=1;return;}
            stmp.remove(0,tx+4);
        }
    }
    tmp.timeIndex|=tmap.value(stmp);
    if(!tmap.value(stmp)) {nflag=1;return;}
    tmp.location=bracket(str,0);
    tmp.location.replace("<br>","\n");
    QString thours;
    thours=hours.mid(0,1);
    tmp.ks=thours.toInt();
    thours=hours.mid(5,1);
    tmp.ks+=thours.toInt();
    tmp.stars=5;
}

QString dealer::operate(QFile *file ,std::vector<courses> &all)
{
//    QFile file2("2.txt");
    QFile fn("s.txt");
    fn.open(QFile::ReadWrite);
//    file2.open(QFile::ReadWrite|QFile::Truncate);
    file->open(QFile::ReadWrite);

    QTextStream in(file);
//    QTextStream out(&file2);
    QTextStream fin(&fn);
    fin >> sw;
    fin >> dw;
//    //qDebug() << sw << ' ' << dw;
    QString str;
    QChar c;
    while(1)
    {
        in >> c;
        str.push_back(c);
        if(str.right(7)=="</HTML>") break;
    }
    QString g;
    int i;

    g="</script>";
    while((i=str.indexOf(&g))!=-1) {
        str.remove(0,i+g.length());
    }
    //清除前部无效内容；循环去除</script>标签前面的东西

    g="<fieldset>";
    str.chop(str.length()-str.indexOf(&g));
    //清除后部无效内容；

    courses cc;
    fin >> g;
    i=str.indexOf(&g);
    cc.code=str.mid(i+g.length(),8);
//    //qDebug() << cc.code;

    fin >> g;
    i=str.indexOf(&g)+g.length();
    while(str[i]!='&'){cc.cName.push_back(str[i]);i++;}
//    //qDebug() << cc.cName;

    fin >> g;
    QString num;
    i=str.indexOf(&g)+g.length();
    num=str.mid(i,3);
    cc.xf=num.toDouble();
//    //qDebug() << cc.xf;

    fin>> g;
    i=str.indexOf(&g)+g.length();
    num.truncate(0);
    while(str[i]!='<') num.push_back(str[i++]);
    int n=num.toInt();
    //qDebug() << n;
    //以上通用属性。 code & name & 学分 & 获取课程数方便一下循环。

    fin >> g;
    i=str.indexOf(&g);
    //qDebug() << g;
    str.remove(0,i-1);
//    out << str;
//    fin >> g;
//    //qDebug() << g;
//    i=str.lastIndexOf(&g);
//    str.chop(str.length()-i);
//    //qDebug() << str;
    //清除头尾多余干扰。

    int p_b;
    p_b=str.indexOf("</tr>");
    str.remove(0,p_b+5);
    QString tmp;
    QMap<long long, int> hash;
    hash.clear();
    for(int i=0;i<n;i++)
    {
        p_b=str.indexOf("</tr>");
        tmp=str.mid(0,p_b+5);
        str.remove(0,p_b+5);
        nflag=0;
        purify(cc,&tmp);
        if(nflag) continue;
        QMap<long long, int>::iterator f=hash.find(cc.timeIndex);
        if(f==hash.end())
        {
            all.push_back(cc);
            hash.insert(cc.timeIndex,1);
        }
    }
    std::vector<courses>::iterator p;
    for(p=all.begin();p!=all.end();p++)
    {
        qDebug() << p->cName << p->tName <<p->timeStr << p->location << p->xf << p->timeIndex << endl;
    }
    QString ssss='['+cc.code+']'+cc.cName+" *";
    return ssss;
}
