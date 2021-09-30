#include "mem_pool.h"
#include "types.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <cstring>

using namespace std;

//Constructor 
MemoryPool::MemoryPool(std::size_t MaxPoolSize, std::size_t BlockSize) {
  
  maxpoolsize = MaxPoolSize;
  poolsizeleft = maxpoolsize - (numofblocks*blocksize);
  blocksize = BlockSize;
  blocksizeused = 0;
  blocksizeleft = 0;
  numofblocks = 0; 

  //pointers 
  //allocating pool ptr to maxpoolsize bytes of storage 
  pool = operator new(maxpoolsize);
  //initialize pool all to null
  std::memset(pool, '\0', maxpoolsize);
  //set block ptr to null ptr  
  block = nullptr; 
}

//done. 
//check whether the block can insert the record 
bool MemoryPool::CheckBlockSize(std::size_t recordsize){
  if (recordsize > blocksizeleft){
    std::cout << "Not enough memory to insert record into block" << endl;
    return false;
  }
  else {
    return true;
  }
}

// insert record into block 
Address MemoryPool::AllocateBlock(std:: size_t recordsize){
  //if block size cannot fit new record, create new block
  if (!CheckBlockSize(recordsize)){

    //if new block cannot be created, exception error 
    NewBlock();
    }
    short int offset = blocksizeused;

    //update current block
    blocksizeused += recordsize;
    blocksizeleft = blocksize - blocksizeused;

    //update pointer after insert
    //block = (char *)block + recordsize;
  // Return the new memory space to put in the record.
  Address recordAddress = {block, offset};

  return recordAddress;
}

//done. 
//check whether the maxpoolsize is exceeded; if exceeded cannot create new block 
bool MemoryPool::CheckMaxPool(){
  if (blocksize <= poolsizeleft){
    //std::cout<<"checking1"<<endl;
    return false; 
  }
  else {
    std::cout<<"Max Pool Size exceeded! Unable to add more blocks"<<endl;
    return true; 
  }
}

//done. 
void MemoryPool::NewBlock(){
  //create newblock if we didn't exceed maxpoolsize 
  if (!CheckMaxPool()){
    block = (char *)pool + numofblocks * blocksize; //move pointer to start of new block 
    blocksizeused = 0; //update blocksizeused
    blocksizeleft = blocksize;
    numofblocks += 1; 

    std::cout << "New block successfully created!" <<numofblocks<< endl; 
    std::cout<< block <<endl;
  }
}

//copied from repo. 
// Give a block address, offset and size, returns the data there.
void* MemoryPool::loadFromDisk(Address address, std::size_t size)
{
  void* mainMemoryAddress = operator new(size);
  std::memcpy(mainMemoryAddress, (char *)address.blockAddress + address.offset, size);

  // Update blocks accessed
  //numofblocks++;

  return mainMemoryAddress;
}

// Saves something into the disk. Returns disk address.
Address MemoryPool::saveToDisk(void *itemAddress, std::size_t size)
{
  Address diskAddress = AllocateBlock(size);
  std::memcpy((char *)diskAddress.blockAddress + diskAddress.offset, itemAddress, size);

  // Update blocks accessed
  //numofblocks++;
  std::cout<<(char *)diskAddress.blockAddress+diskAddress.offset<<endl;
  return diskAddress;
}

// Update data in disk if I have already saved it before.
Address MemoryPool::saveToDisk(void *itemAddress, std::size_t size, Address diskAddress)
{
  std::memcpy((char *)diskAddress.blockAddress + diskAddress.offset, itemAddress, size);

  // Update blocks accessed
  //numofblocks++;

  return diskAddress;
}

//kiv maybe don;t do deallocation 
//Address MemoryPool::Deallocate(){

//}