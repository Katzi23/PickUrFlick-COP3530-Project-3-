#ifndef PICKURFLICK_COP3530_PROJECT_3_MAXHEAP_H
#define PICKURFLICK_COP3530_PROJECT_3_MAXHEAP_H

#include <vector>
#include "data.h"


class MaxHeap
{
private:
    std::vector<data*> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);
public:
    void insert(data* movie);
    data* extractMaxRating();
};


#endif //PICKURFLICK_COP3530_PROJECT_3_MAXHEAP_H
