#include "BPTree.h"
#include "types.h"

#include <vector>
#include <cstring>
#include <iostream>


using namespace std;
static int counter = 0;

int BPTree::getCounter(){
  return counter;
}

void BPTree::deleteKey(int key){
  
      
  if (root == NULL) {
    cout << "Tree empty\n";
  } 
  else {
    
    Node *cursor = root;
    Node *parent;
    int leftSibling, rightSibling;
    while (cursor->isLeaf == false) {
      for (int i = 0; i < cursor->numKeys; i++) {
        parent = cursor;
        leftSibling = i - 1;
        rightSibling = i + 1;
        if (key < cursor->keys[i]) {
          cursor = cursor->pointers[i];
          break;
        }
        if (i == cursor->numKeys - 1) {
          leftSibling = i;
          rightSibling = i + 2;
          cursor = cursor->pointers[i + 1];
          break;
        }
      }
    }
    bool found = false;
    int pos;
    for (pos = 0; pos < cursor->numKeys; pos++) {
      if (cursor->keys[pos] == key) {
        found = true;
      
        break;
      }
    }
    if (!found) {
      // cout << "Not found\n";
      return;
    }
    for (int i = pos; i < cursor->numKeys; i++) {
      cursor->keys[i] = cursor->keys[i + 1];
    }
    cursor->numKeys--;
    if (cursor == root) {
      for (int i = 0; i < maxKeys + 1; i++) {
        cursor->pointers[i] = NULL;
      }
      if (cursor->numKeys == 0) {
        cout << "Tree died\n";
        delete[] cursor->keys;
        delete[] cursor->pointers;
        delete cursor;
        root = NULL;
      }
      return;
    }
    cursor->pointers[cursor->numKeys] = cursor->pointers[cursor->numKeys + 1];
    cursor->pointers[cursor->numKeys + 1] = NULL;
    if (cursor->numKeys >= (maxKeys + 1) / 2) {
      return;
    }
    if (leftSibling >= 0) {
      Node *leftNode = parent->pointers[leftSibling];
      if (leftNode->numKeys >= (maxKeys + 1) / 2 + 1) {
        for (int i = cursor->numKeys; i > 0; i--) {
          cursor->keys[i] = cursor->keys[i - 1];
        }
        cursor->numKeys++;
        cursor->pointers[cursor->numKeys] = cursor->pointers[cursor->numKeys - 1];
        cursor->pointers[cursor->numKeys - 1] = NULL;
        cursor->keys[0] = leftNode->keys[leftNode->numKeys - 1];
        leftNode->numKeys--;
        leftNode->pointers[leftNode->numKeys] = cursor;
        leftNode->pointers[leftNode->numKeys + 1] = NULL;
        parent->keys[leftSibling] = cursor->keys[0];
        return;
      }
    }
    if (rightSibling <= parent->numKeys) {
      Node *rightNode = parent->pointers[rightSibling];
      if (rightNode->numKeys >= (maxKeys + 1) / 2 + 1) {
        cursor->numKeys++;
        cursor->pointers[cursor->numKeys] = cursor->pointers[cursor->numKeys - 1];
        cursor->pointers[cursor->numKeys - 1] = NULL;
        cursor->keys[cursor->numKeys - 1] = rightNode->keys[0];
        rightNode->numKeys--;
        rightNode->pointers[rightNode->numKeys] = rightNode->pointers[rightNode->numKeys + 1];
        rightNode->pointers[rightNode->numKeys + 1] = NULL;
        for (int i = 0; i < rightNode->numKeys; i++) {
          rightNode->keys[i] = rightNode->keys[i + 1];
        }
        parent->keys[rightSibling - 1] = rightNode->keys[0];
        return;
      }
    }
    if (leftSibling >= 0) {
      Node *leftNode = parent->pointers[leftSibling];
      for (int i = leftNode->numKeys, j = 0; j < cursor->numKeys; i++, j++) {
        leftNode->keys[i] = cursor->keys[j];
      }
      leftNode->pointers[leftNode->numKeys] = NULL;
      leftNode->numKeys += cursor->numKeys;
      leftNode->pointers[leftNode->numKeys] = cursor->pointers[cursor->numKeys];
      deleteInternal(parent->keys[leftSibling], parent, cursor);
      counter += 1;
      std::cout<< "Number of nodes deleted: "<<counter<<endl;
      delete[] cursor->keys;
      delete[] cursor->pointers;
      delete cursor;


    } else if (rightSibling <= parent->numKeys) {
      Node *rightNode = parent->pointers[rightSibling];
      for (int i = cursor->numKeys, j = 0; j < rightNode->numKeys; i++, j++) {
        cursor->keys[i] = rightNode->keys[j];
      }
      cursor->pointers[cursor->numKeys] = NULL;
      cursor->numKeys += rightNode->numKeys;
      cursor->pointers[cursor->numKeys] = rightNode->pointers[rightNode->numKeys];
      cout << "Merging two leaf nodes\n";
      deleteInternal(parent->keys[rightSibling - 1], parent, rightNode);
      counter += 1;
      std::cout<< "Number of nodes deleted: "<<counter<<endl;
      delete[] rightNode->keys;
      delete[] rightNode->pointers;
      delete rightNode;
      


    }
  }
}

void BPTree::deleteInternal(int x, Node *cursor, Node *child) {
  if (cursor == root) {
    if (cursor->numKeys == 1) {
      if (cursor->pointers[1] == child) {
        delete[] child->keys;
        delete[] child->pointers;
        delete child;

        std::cout<< "Number of nodes deleted: "<<counter<<endl;
        root = cursor->pointers[0];
        delete[] cursor->keys;
        delete[] cursor->pointers;
        delete cursor;
        cout << "Changed root node\n";
        return;
      } else if (cursor->pointers[0] == child) {
        delete[] child->keys;
        delete[] child->pointers;
        delete child;
      
        std::cout<< "Number of nodes deleted: "<<counter<<endl;
        
        root = cursor->pointers[1];
        delete[] cursor->keys;
        delete[] cursor->pointers;
        delete cursor;
        cout << "Changed root node\n";
        return;
      }
    }
  }
  int pos;
  for (pos = 0; pos < cursor->numKeys; pos++) {
    if (cursor->keys[pos] == x) {
      break;
    }
  }
  for (int i = pos; i < cursor->numKeys; i++) {
    cursor->keys[i] = cursor->keys[i + 1];
  }
  for (pos = 0; pos < cursor->numKeys + 1; pos++) {
    if (cursor->pointers[pos] == child) {
      break;
    }
  }
  for (int i = pos; i < cursor->numKeys + 1; i++) {
    cursor->pointers[i] = cursor->pointers[i + 1];
  }
  cursor->numKeys--;
  if (cursor->numKeys >= (maxKeys + 1) / 2 - 1) {
    return;
  }
  if (cursor == root)
    return;
  Node *parent = findParent(root, cursor);
  int leftSibling, rightSibling;
  for (pos = 0; pos < parent->numKeys + 1; pos++) {
    if (parent->pointers[pos] == cursor) {
      leftSibling = pos - 1;
      rightSibling = pos + 1;
      break;
    }
  }
  if (leftSibling >= 0) {
    Node *leftNode = parent->pointers[leftSibling];
    if (leftNode->numKeys >= (maxKeys + 1) / 2) {
      for (int i = cursor->numKeys; i > 0; i--) {
        cursor->keys[i] = cursor->keys[i - 1];
      }
      cursor->keys[0] = parent->keys[leftSibling];
      parent->keys[leftSibling] = leftNode->keys[leftNode->numKeys - 1];
      for (int i = cursor->numKeys + 1; i > 0; i--) {
        cursor->pointers[i] = cursor->pointers[i - 1];
      }
      cursor->pointers[0] = leftNode->pointers[leftNode->numKeys];
      cursor->numKeys++;
      leftNode->numKeys--;
      return;
    }
  }
  if (rightSibling <= parent->numKeys) {
    Node *rightNode = parent->pointers[rightSibling];
    if (rightNode->numKeys >= (maxKeys + 1) / 2) {
      cursor->keys[cursor->numKeys] = parent->keys[pos];
      parent->keys[pos] = rightNode->keys[0];
      for (int i = 0; i < rightNode->numKeys - 1; i++) {
        rightNode->keys[i] = rightNode->keys[i + 1];
      }
      cursor->pointers[cursor->numKeys + 1] = rightNode->pointers[0];
      for (int i = 0; i < rightNode->numKeys; ++i) {
        rightNode->pointers[i] = rightNode->pointers[i + 1];
      }
      cursor->numKeys++;
      rightNode->numKeys--;
      return;
    }
  }
  if (leftSibling >= 0) {
    Node *leftNode = parent->pointers[leftSibling];
    leftNode->keys[leftNode->numKeys] = parent->keys[leftSibling];
    for (int i = leftNode->numKeys + 1, j = 0; j < cursor->numKeys; j++) {
      leftNode->keys[i] = cursor->keys[j];
    }
    for (int i = leftNode->numKeys + 1, j = 0; j < cursor->numKeys + 1; j++) {
      leftNode->pointers[i] = cursor->pointers[j];
      cursor->pointers[j] = NULL;
    }
    leftNode->numKeys += cursor->numKeys + 1;
    cursor->numKeys = 0;
    deleteInternal(parent->keys[leftSibling], parent, cursor);
  } else if (rightSibling <= parent->numKeys) {
    Node *rightNode = parent->pointers[rightSibling];
    cursor->keys[cursor->numKeys] = parent->keys[rightSibling - 1];
    for (int i = cursor->numKeys + 1, j = 0; j < rightNode->numKeys; j++) {
      cursor->keys[i] = rightNode->keys[j];
    }
    for (int i = cursor->numKeys + 1, j = 0; j < rightNode->numKeys + 1; j++) {
      cursor->pointers[i] = rightNode->pointers[j];
      rightNode->pointers[j] = NULL;
    }
    cursor->numKeys += rightNode->numKeys + 1;
    rightNode->numKeys = 0;
    deleteInternal(parent->keys[rightSibling - 1], parent, rightNode);
  }
}
