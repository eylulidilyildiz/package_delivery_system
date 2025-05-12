/**
Author : Eylul Idil Yildiz
ID: 22302223
Section : 3
Homework : 2
Description : This is the header file of the template class Heap. Heaps (maxHeaps) are binary tree-based 
			  data structures in which the elements are ordered according to their pre-determined key
			  values in a way that the root contains the element with the largest key. This file handles
			  the insertion, deletion operations and getter methods of the array-based Heap class.
*/

#ifndef __HEAP_H
#define __HEAP_H

#include "Drone.h"
#include "Package.h"

template <typename T>
class Heap{
public:
    static const int MAX_HEAP_SIZE = 50;
    Heap();	 //constructor
            
    bool heapIsEmpty() const;
    void heapInsert(const T& newItem);
    T heapDeleteRoot(); //returns the deleted element from the root
    void heapDeleteElement(const T& itemToBeDeleted);
    T& getElementAt(int index); // starting from 0
    int getHeapSize();
	Package& getPackageById(int id);
            
protected:
    void heapRebuild(int root);		// Converts the semiheap rooted at index root into a heap 
            
private:
    T items[MAX_HEAP_SIZE];	// array of heap items
    int size;            // number of heap items   
};


// IMPLEMENTATIONS
// Heap implementations are handled in the header file due to the template <typename T> usage.
template <typename T>
Heap<T> :: Heap(){
    size = 0;
}

template <typename T>
T& Heap<T> :: getElementAt(int index){
    if (index >= 0 && index < size){
        return items[index];
    }
    static T emptyItem;
    return emptyItem;  
	
}

template <typename T>
int Heap<T> :: getHeapSize(){
    return size;
}

template <typename T>
bool Heap<T> :: heapIsEmpty() const {
	return (size <= 0);
}

template <typename T>
void Heap<T> :: heapInsert(const T& newItem)
{
    if(size >= MAX_HEAP_SIZE){
        return;
    }
    // Place the new item at the end of the heap
	items[size] = newItem;

	// Trickle new item up to its proper position
	int place = size;
	int parent = (place - 1)/2;
	while ( (place > 0) && (items[place] > items[parent]) ) 
    {
		T temp = items[parent];
		items[parent] = items[place];
		items[place] = temp;

		place = parent;
		parent = (place - 1)/2;
	}
 	++size;
}

template <typename T>
T Heap<T> :: heapDeleteRoot()  {
	if (heapIsEmpty()){
        static T emptyItem;
        return emptyItem;
    }
	else {
	    T rootItem = items[0];
		items[0] = items[--size];
		heapRebuild(0);
		return rootItem;
	}
}

template <typename T>
void Heap<T> :: heapDeleteElement(const T& itemToBeDeleted)  {
	if (heapIsEmpty())
		return;
	else {
		int index = 0;
		T currentItem = items[0];
		while (currentItem != itemToBeDeleted && index != size) // != operation is overridden for Drone and Package classes
		{
			index ++;
			currentItem = items[index];
		}
		items[index] = items[--size];
		heapRebuild(index);
	}
}


template <typename T>
void Heap<T> :: heapRebuild(int root) 
{   
	int child = 2 * root + 1; 	// index of root's left child, if any
	if ( child < size ) {		
		// root is not a leaf so that it has a left child
		int rightChild = child + 1; 	// index of a right child, if any
		// If root has right child, find larger child
		if ( (rightChild < size) && (items[rightChild] >items[child]) )
			child = rightChild; 	// index of larger child

		// If root’s item is smaller than larger child, swap values
		if ( items[root] < items[child] ) {
			T temp = items[root];
			items[root] = items[child];
			items[child] = temp;

			// transform the new subtree into a heap
			heapRebuild(child);
		}
    }
}

/*
template <>
Package& Heap<Package>::getPackageById(int id) {
    for (int i = 0; i < size; i++) {
        if (items[i].getId() == id) {
            return items[i]; 
        }
    }
    //if package is not found
	static Package emptyItem;
    return emptyItem;  
}*/

#endif
