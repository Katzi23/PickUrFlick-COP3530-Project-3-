#include "MaxHeap.h"
#include <algorithm>

//Standard heapify up helper function for inserting data
void MaxHeap::heapifyUp(int index) {
    while (index > 0){
        int parent = (index - 1) / 2;
        if (heap[index]->getRating() > heap[parent]->getRating()) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

//Standard heapify down helper function for deleting data
void MaxHeap::heapifyDown(int index) {
    int size = heap.size();
    while (index < size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && heap[left]->getRating() > heap[largest]->getRating()) {
            largest = left;
        }
        if (right < size && heap[right]->getRating() > heap[largest]->getRating()){
            largest = right;
        }

        if (largest != index) {
            std::swap(heap[index], heap[largest]);
        } else {
            break;
        }
    }
}

//Insert data
void MaxHeap::insert(data* movie){
    heap.push_back(movie);
    heapifyUp(heap.size()-1); //Insert at end and then heapify up
}

//Extract the Highest Rated Movie in the Heap
data* MaxHeap::extractMaxRating() {
    if (heap.empty()){
        std::cout << "No Movies in Heap!";
        return nullptr;
    }
    data* maxRating = heap[0]; //Max will always be root node
    heap[0] = heap.back();
    heap.pop_back(); //Remove the max
    heapifyDown(0); //Heapify down the new root from the end;
    return maxRating; //Return the movie with the highest rating
}

bool MaxHeap::isEmpty() {
    if(heap.empty()){
        return true;
    } else {
        return false;
    }
}

