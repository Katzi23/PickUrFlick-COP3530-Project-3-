#ifndef PICKURFLICK_COP3530_PROJECT_3_ARRAYQ_H
#define PICKURFLICK_COP3530_PROJECT_3_ARRAYQ_H
#include "data.h"
#include <vector>


struct ArrayQ
{
    std::vector<data*> priorityQ;
    // find position where element should go, insert it. O(n)
    void insert(data* d);
    // return the first element (has max rating)
    data* extractMax();
}
;


#endif //PICKURFLICK_COP3530_PROJECT_3_ARRAYQ_H
