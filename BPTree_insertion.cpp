#include "BPTree.h"
#include "types.h"

#include <vector>
#include <cstring>
#include <iostream>

int const MAX = 3;

using namespace std;

/*INSERTING A RECORD INTO A NODE:
1. Run search operation to find appropriate place to insert
2. Insert the new keys at the proper location, 
  but if the node has a maximum number of keyss already:
3. The node, along with a newly inserted keys, will split from the middle element.
4. The middle element will become the parent for the other two child nodes.
5. The nodes must re-arrange keyss in ascending order.
*/

// // Insert a record into the B+ Tree index. Key: Record's numVotes, Value: {blockAddress, offset}.
// void BPTree::insert(Address address, int keys) //Mtd of BPlusTree 
// {
//   //Check if root node exists
//   if (rootAddress == nullptr){

//     //Initialise node to store incoming new record
//     root = new Node(maxKeys); //Create new node 
//     root->keyss[0] = keys; //Insert new keys into new array of keyss in new node
//     root->isLeaf = true;
//     root->numKeys = 1; //New keys inserted into new node thus total = 1 keys
//   }
//   else{
//     if (root->numKeys < maxKeys) {
//       //insert into block
//     }
//     else{
//       //else split two blocks with half of each keyss
//     }
    
//     //check bool balancing();


//   }
// }

// Insert Operation
void BPTree::insert(Address address, int key) {

  //If empty tree, create new node
  if (root == NULL) {
    root = new Node(maxKeys);
    root->keys[0] = key; //Insert new key into new array of keys in new node
    root->isLeaf = true;
    root->numKeys = 1; //New key inserted into new node thus total = 1 key

  //If not empty - cursor pt to root block - conduct search top down
  } else {
    Node *cursor = root;
    Node *parent;
    while (cursor->isLeaf == false) { //cursor is at non leaf node
      parent = cursor; //original starting position of parent node
      
      //iterate through records in the block
      for (int i = 0; i < cursor->numKeys; i++) { 
        if (key < cursor->keys[i]) { //comparison of keys 
          cursor = (Node *)cursor->pointers[i].blockAddress; //cursor traverse to left block
          break;
        }
        if (i == cursor->numKeys - 1) {
          cursor = (Node *)cursor->pointers[i+1].blockAddress; //cursor traverse to right block
          break;
        }
      }
    }
    if (cursor->numKeys < maxKeys) { //if block still have space 
      int i = 0;

      while (key > cursor->keys[i] && i < cursor->numKeys){ //on same block, compare new key with key in the block & i < total numKeys
        i++; //pt of insertion
      }

      for (int j = cursor->numKeys; j > i; j--) {
        cursor->keys[j] = cursor->keys[j - 1]; //shifting keys, larger than new key, right by 1 position
        cursor->pointers[j] = cursor->pointers[j-1]; //shifting pointers
      }

      cursor->keys[i] = key; //insert key i th position
      cursor->numKeys++; //update numKeys
    
    }else{ //if block no space

      Node *newLeaf = new Node(maxKeys); //create new node
      int virtualNode[MAX + 1]; //KIVKIVvivivivii

      for (int i = 0; i < maxKeys; i++) { //take in (max keys + 1) keys and store in vir node
        virtualNode[i] = cursor->keys[i];
      }

      int i = 0, j;

      while (key > virtualNode[i] && i < maxKeys){ //finding position to slot in new key
        i++;
      }
      for (int j = maxKeys + 1; j > i; j--) { //moving keys that are larger 
        virtualNode[j] = virtualNode[j - 1];
      }

      virtualNode[i] = key;  //insert new key into position i
      newLeaf->isLeaf = true;
      cursor->numKeys = (maxKeys + 1) / 2; //splitting keys into 2 nodes 
      newLeaf->numKeys = maxKeys + 1 - (maxKeys + 1) / 2; //newleaf should contain behind half nodes 

      cursor->pointers[cursor->numKeys] = newLeaf->pointers[0]; //pointing to first pointer of new leaf node 
      newLeaf->pointers[newLeaf->numKeys] = cursor->pointers[maxKeys]; //
      cursor->pointers[maxKeys] = NULL; 
      //rearranging the 2 leaf nodes 
      for (i = 0; i < cursor->numKeys; i++) {
        cursor->keys[i] = virtualNode[i];
      }
      for (i = 0, j = cursor->numKeys; i < newLeaf->numKeys; i++, j++) {
        newLeaf->keys[i] = virtualNode[j];
      }
      if (cursor == root) {
        Node *newRoot = new Node(maxKeys);
        newRoot->keys[0] = newLeaf->keys[0];
        newRoot->pointers[0] = cursor->pointers[0];
        newRoot->pointers[1] = newLeaf->pointers[0];
        newRoot->isLeaf = false;
        newRoot->numKeys = 1;
        root = newRoot;
      } else {
        insertInternal(newLeaf->keys[0], parent, newLeaf);
      }
    }
  }
}

void BPTree::insertInternal(int x, Node *cursor, Node *child) {
  if (cursor->size < MAX) {
    int i = 0;
    while (x > cursor->key[i] && i < cursor->size)
      i++;
    for (int j = cursor->size; j > i; j--) {
      cursor->key[j] = cursor->key[j - 1];
    }
    for (int j = cursor->size + 1; j > i + 1; j--) {
      cursor->ptr[j] = cursor->ptr[j - 1];
    }
    cursor->key[i] = x;
    cursor->size++;
    cursor->ptr[i + 1] = child;
  } else {
    Node *newInternal = new Node;
    int virtualKey[MAX + 1];
    Node *virtualPtr[MAX + 2];
    for (int i = 0; i < MAX; i++) {
      virtualKey[i] = cursor->key[i];
    }
    for (int i = 0; i < MAX + 1; i++) {
      virtualPtr[i] = cursor->ptr[i];
    }
    int i = 0, j;
    while (x > virtualKey[i] && i < MAX)
      i++;
    for (int j = MAX + 1; j > i; j--) {
      virtualKey[j] = virtualKey[j - 1];
    }
    virtualKey[i] = x;
    for (int j = MAX + 2; j > i + 1; j--) {
      virtualPtr[j] = virtualPtr[j - 1];
    }
    virtualPtr[i + 1] = child;
    newInternal->IS_LEAF = false;
    cursor->size = (MAX + 1) / 2;
    newInternal->size = MAX - (MAX + 1) / 2;
    for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
      newInternal->key[i] = virtualKey[j];
    }
    for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
      newInternal->ptr[i] = virtualPtr[j];
    }
    if (cursor == root) {
      Node *newRoot = new Node;
      newRoot->key[0] = cursor->key[cursor->size];
      newRoot->ptr[0] = cursor;
      newRoot->ptr[1] = newInternal;
      newRoot->IS_LEAF = false;
      newRoot->size = 1;
      root = newRoot;
    } else {
      insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
    }
  }
}

// Find the parent
Node *BPTree::findParent(Node *cursor, Node *child) {
  Node *parent;
  if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
    return NULL;
  }
  for (int i = 0; i < cursor->size + 1; i++) {
    if (cursor->ptr[i] == child) {
      parent = cursor;
      return parent;
    } else {
      parent = findParent(cursor->ptr[i], child);
      if (parent != NULL)
        return parent;
    }
  }
  return parent;
}

// Print the tree
void BPTree::display(Node *cursor) {
  if (cursor != NULL) {
    for (int i = 0; i < cursor->size; i++) {
      cout << cursor->key[i] << " ";
    }
    cout << "\n";
    if (cursor->IS_LEAF != true) {
      for (int i = 0; i < cursor->size + 1; i++) {
        display(cursor->ptr[i]);
      }
    }
  }
}

// Get the root
Node *BPTree::getRoot() {
  return root;
}

// void BPTree::Search(){

// }

// void BPTree::blockSpaceCheck(){

// }

// void BPTree::balacingcheck(){

// }