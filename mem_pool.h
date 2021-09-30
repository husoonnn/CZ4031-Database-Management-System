#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include "types.h"

#include <vector>
#include <unordered_map>
#include <tuple>

class MemoryPool {

  private:
    std::size_t maxpoolsize;
    std::size_t blocksizeused;
    std::size_t poolsizeleft;
    std::size_t blocksizeleft;
    std::size_t blocksize;
    int numofblocks;

    void* pool; //pointer to memory pool
    void* block; //pointer to block we are accessing

  public:

    MemoryPool(std::size_t MaxPoolSize, std::size_t BlockSize);

    bool CheckBlockSize(std::size_t recordsize);

    bool CheckMaxPool(); 

    Address AllocateBlock(std::size_t recordsize);

    Address Deallocate();

    void NewBlock();

    void* loadFromDisk(Address address, std::size_t size);

    Address saveToDisk(void *itemAddress, std::size_t size); 

    Address saveToDisk(void *itemAddress, std::size_t size, Address diskAddress); 

    void DeallocateRecord(Address address, std::size_t size);


  //getters 
    std::size_t getMaxPoolSize(){
      return maxpoolsize; 
    }
    std::size_t getBlockSizeUsed(){
      return blocksizeused; 
    }
    std::size_t getPoolSizeLeft(){
      return poolsizeleft; 
    }
    std::size_t getBlockSizeLegt(){
      return blocksizeleft; 
    }
    int getNumOfBlocks(){
      return numofblocks;
    }
    int getBlockSize(){
      return blocksize; 
    }
    std::size_t getSizeOfDatabase(){
      return numofblocks*blocksize; 
    }
};

#endif