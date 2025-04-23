#include "ArrayQ.h"

void ArrayQ::insert(data* d)
{
    // find position where element should go, insert it. O(n)
    for (int i = 0; i < priorityQ.size(); i++)
    {
        if (priorityQ[i]->getRating() > d->getRating())
            continue;
        else
        {
            priorityQ.insert(priorityQ.begin() + i, d);
            break;
        }
    }
    // if it's smaller than everything, add it to the end
    priorityQ.push_back(d);
}

data* ArrayQ::extractMax()
{
    data* top = priorityQ.front();
    priorityQ.erase(priorityQ.begin());
    return top;
}

bool ArrayQ::isEmpty(){
    return priorityQ.empty();
}

void ArrayQ::deleteTop()
{
    if (!priorityQ.empty())
        priorityQ.erase(priorityQ.begin());
}