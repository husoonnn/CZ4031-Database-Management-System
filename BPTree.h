#ifndef BPTREE_H
#define BPTREE_H

#include "mem_pool.h"
#include "types.h"

class Node{
    private:
        int numKeys; //number of keys in this node
        int *keys; //store array of keys in the node
        void* storagepointer;
        Node** pointers; //{BlockAddress, offset}
        bool isLeaf; //whether this is the leaf node
        friend class BPTree;
    
    public:
        Node(int maxKeys);
};

class BPTree{
    private:
        int maxKeys;        //Number of keys
        int height;         // height of B+ Tree
        int numNodes;       //total number of nodes in the B+ Tree
        MemoryPool *disk;   //pointer pointing to memory pool for data block
        MemoryPool *index;  //pointer pointing to memory pool for index
        Node *root;         //pointer to root node
        void *rootAddress;  //pointer to root address
        std::size_t nodeSize;
        Node* findParent(Node*,Node*);

        //update the parent's index pointer to point at child node 
        void insertInternal(int key, Node* currentDiskAddress, Node* childIndexAddress, Address address);

         //update the parent's index pointer to point at child node  
        void deleteInternal(int key, Node* currentDiskAddress, Node* childIndexAddress);
    
    public:
        int getMaxKeys(std::size_t blocksize); 
        BPTree(std::size_t blocksize, MemoryPool *disk, MemoryPool *index);
        void insert(Address address, int key);
        //Node *findParent(Node *cursor, Node *child);
        void display(Node *cursor);
        void print(Node *cursor);
        Node *getRoot();
};
#endif
