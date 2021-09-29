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
    int num_of_blocks;

    void *pool;
    void *block;

  public:

    MemoryPool(std::size_t MaxPoolSize, std::size_t BlockSize);

    bool checkblocksize(std::size_t recordsize, std::size_t BlockSizeLeft);

    Address Allocateblock(bool CheckBlockSize);

    Address Deallocate();

};

#endif