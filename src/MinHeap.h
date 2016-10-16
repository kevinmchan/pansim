//
//  MinHeap.h
//  morPop
//
//  Created by Kevin Chan on 2016-02-23.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#ifndef MinHeap_h
#define MinHeap_h

// Structure to represent a min heap node
struct MinHeapNode {
    int v;
    double dist;
};

// Structure to represent a min heap
struct MinHeap {
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
    MinHeapNode **array;
    MinHeap(int capacity);
    ~MinHeap();
};

MinHeap::MinHeap(int capacity) {
    this->pos = new int[capacity];
    this->size = capacity;
    this->capacity = capacity;
    this->array = new MinHeapNode*[capacity];
    for (int i = 0; i < capacity; i++) {
        this->array[i] = new MinHeapNode();
    }
}

MinHeap::~MinHeap() {
    delete[] this->pos;
    for (int i = 0; i < this->capacity; i++) {
        delete this->array[i];
    }
    delete[] this->array;
}

// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
    
    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
        smallest = left;
    
    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
        smallest = right;
    
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];
        
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
        
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check if the given minHeap is ampty or not
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}

// Standard function to extract minimum node from heap
MinHeapNode* extractMin(MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
    
    // Store the root node
    MinHeapNode* root = minHeap->array[0];
    
    // Replace root node with last node
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->array[minHeap->size - 1] = root;
    
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
    
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
    
    return root;
}

// Function to decreasy dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(MinHeap* minHeap, int v, double dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
    
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
    
    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
        
        // move to parent index
        i = (i - 1) / 2;
    }
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}

#endif /* MinHeap_h */
