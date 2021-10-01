#include "BPTree.h"
#include "mem_pool.h"
#include "types.h"
#include <string>
#include <iostream>

using namespace std;

Node::Node(int maxKeys){
    keys = new int[maxKeys];
    pointers = new Node*[maxKeys+1];
    leafLinkPointer = NULL;

    //int i = 0;
    //while(i<maxKeys + 1){
        //Address nullAddress{(void *) NULL, 0}; // KIVIVIVIVIVIVIV Generate a block and allocate to pointer
        //pointers[i] = nullAddress; //initialize pointer
        //i+=1;
    //}
  numKeys = 0;
}

int BPTree::getMaxKeys(std::size_t blocksize){
    size_t remainderNodeSpace = blocksize - sizeof(bool) - sizeof(int); //bool = isLEaf, int = numKeys

    size_t totalspace = sizeof(Address); //accounting for space of first pointer in a node
    maxKeys = 0;

    while (totalspace + sizeof(Address) + sizeof(float) <= remainderNodeSpace)
    {
        //adding space of one KV pair in a node one by one 
        totalspace = totalspace + (sizeof(Address) + sizeof(float)); 
        maxKeys += 1;
    }

    // Set node size to be equal to block size.
    nodeSize = blocksize;
    return maxKeys;
}

BPTree::BPTree(std::size_t blocksize, MemoryPool *disk, MemoryPool *index){

    maxKeys = getMaxKeys(blocksize);
    std::cout<< maxKeys << endl;
    //Initialize root to NULL
    //rootAddress = nullptr;
    root = NULL;

    // Set node size to be equal to block size.
    //nodeSize = blockSize; KIVIVIVIVIVIVIVIVIVIVIVIVIV

    // Initialize initial variables
    height = 0;
    numNodes = 0;

    // Initialize disk space for index and set reference to disk.
    
    this->disk = disk;
    this->index = index;
}
