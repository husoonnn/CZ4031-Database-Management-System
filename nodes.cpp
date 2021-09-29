#include "nodes.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <cstring>

Nodes::Nodes(char movieID[12],float avgRating,int votes){
    keyValues.tconst[12] = movieID[12];
    keyValues.averageRating = avgRating;
    keyValues.numVotes = votes;
}