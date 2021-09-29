#ifndef NODES_H
#define NODES_H

#include "types.h"

#include <list>
#include <string>

class Nodes {

    private:
        Record keyValues; //key values containing all movie data
        Nodes* next; //left pointer
        Nodes* prev; //right pointer
        bool isleaf; //check if node is leaf node

    public:
        Nodes(char movieID[12],float avgRating,int votes);
};

#endif