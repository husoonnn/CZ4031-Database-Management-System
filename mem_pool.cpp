#include "mem_pool.h"
#include "types.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <cstring>

using namespace std;

MemoryPool::MemoryPool(std::size_t MaxPoolSize, std::size_t BlockSize) {
  
  maxpoolsize = MaxPoolSize;
  poolsizeleft = maxpoolsize - (num_of_blocks*blocksize);
  blocksize = BlockSize;
  blocksizeused = 0;
  blocksizeleft = 0;

  pool = operator new(maxpoolsize);

}

bool MemoryPool::checkblocksize(std::size_t recordsize, std::size_t BlockSizeLeft){

  if (recordsize > BlockSizeLeft){
    std::cout << "Not enough memory to insert record into block" << endl;
    return false;
  }
  else {
    return true;
  }
}

Address MemoryPool::Allocateblock(bool CheckBlockSize){
  if (!CheckBlockSize){
    //allocate new block
    //from pool get new block get new address
  }
  else{
    //add to current block
    //return current block new address
  }
}

Address MemoryPool::Deallocate(){

}