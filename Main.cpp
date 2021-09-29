#include "mem_pool.h"
#include "types.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

int main(){
    int BLOCKSIZE=0;
  std::cout <<"=========================================================================================="<<endl;
  std::cout <<"Select Block size:           "<<endl;

  int choice = 0;
  while (choice != 1 && choice != 2){
    std::cout << "Enter a choice: " <<endl;
    std::cout << "1. 100 B " <<endl;
    std::cout << "2. 500 B" <<endl;
    cin >> choice;
    if (int(choice) == 1)
    {
      BLOCKSIZE = int(100);
    } 
    else if (int(choice) == 2)
    {
      BLOCKSIZE = int(500);
    }
    else 
    {
      cin.clear();
      std::cout << "Invalid input, input either 1 or 2" <<endl;
    }
  }
    std::cout << "creating the disk on the stack for records, index" << endl;
  MemoryPool disk(150000000, BLOCKSIZE);  // 150MB
  MemoryPool index(350000000, BLOCKSIZE); // 350MB
}