/**
Author : Eylul Idil Yildiz
ID: 22302223
Section : 3
Homework : 2
Description : This is the source file of the template class Heap. In this file, a getter 
              function which takes the numerical value id as a parameter and returns a 
              reference to the Package with that id in the Heap is implemented. 
*/

#include "Heap.h"
#include "Package.h"

template <>
Package& Heap<Package>::getPackageById(int id) {
    for (int i = 0; i < size; i++) {
        if (items[i].getId() == id) {
            return items[i]; 
        }
    }
    // if package with id is not in the heap
    static Package emptyItem;
    return emptyItem;  
}

// Explicitly instantiate template for Heap<Package>
template class Heap<Package>;