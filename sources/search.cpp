#include "search.h"
#include <QtDebug>

search::search()
{
    ans.clear();
    now.clear();
    score=0;
    stack.clear();
}

double search::calc()
{
    double sum=0;
    std::vector<std::vector<courses>::iterator>::iterator p;
    for(p=now.begin();p!=now.end();p++)
    {
        sum+=(*p)->xf;
    }
//    qDebug() << "New Score:" << sum;
    return sum;
}

void search::dfs(std::vector<courses>::iterator p, std::vector<courses>::iterator n)
{
    if(p==n)
    {
//        qDebug() << "At the End!" << endl;
        double num = calc();
//        qDebug() << num << ' ' << score;
        if(num>score)
        {
            score = num;
            ans.clear();
            ans=now;//Is it ok?
//            qDebug() << ans.size();
        }
        return;
    }
//    qDebug() << p->cName << ' ' << p->tName << endl;
//    qDebug() << stack.count() << endl;
    if((!stack.isEmpty())&&(stack[stack.count()-1]==p->code)) dfs(p+1,n);
    else
    {
        if(!(statue&p->timeIndex))
        {
            statue&=p->timeIndex;
            stack <<(p->code);
            now.push_back(p);
//            qDebug() << "All array is ok!" << endl;
            dfs(p+1,n);
            stack.pop_back();
            now.pop_back();
            statue^=p->timeIndex;
        }
        dfs(p+1,n);
    }
}

void search::work(std::vector<courses> &over, std::vector<courses> &all)
{
    statue=0;
    for(std::vector<courses>::iterator p=over.begin();p!=over.end();p++)
    {
        statue|=p->timeIndex;
    }
    qDebug() << all.size();
    dfs(all.begin(),all.end());
    for(std::vector<courses>::iterator p=over.begin();p!=over.end();p++)
    {
        ans.push_back(p);
    }
}
