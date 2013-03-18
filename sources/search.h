#ifndef SEARCH_H
#define SEARCH_H
#include "dealer.h"

class search
{
public:
    search();
    void work(std::vector<courses> &over, std::vector<courses> &all);
    void dfs(std::vector<courses>::iterator,std::vector<courses>::iterator);
    double calc();
    std::vector<std::vector<courses>::iterator> now,ans;
    QStringList stack;
    double score;
    long long statue;
};

#endif // SEARCH_H
