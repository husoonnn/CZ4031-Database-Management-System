#include "mem_pool.h"
#include "types.h"
#include "BPTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

//get user choice for 100B or 500B
int BlockSizeSelect(){

    int choice=0;

    while(choice != 1 || choice != 2){

        std::cout << "Enter choice for Block Size:" << endl;
        std::cout << "(1) 100B" << endl;
        std::cout << "(2) 500B" << endl;
        std::cin >> choice;

        if (choice == 1){
            return 100;
        }
        else if (choice == 2){
            return 500;
        }
        else{
            std::cout << "Please enter a valid choice" << endl;
        }
    }
    return 0;
}

void Experiment1(int blocksize,MemoryPool disk, MemoryPool index){
    
    //read data.tsv file and load into disk storage
    std::fstream file;

    file.open("data/testdata.tsv",ios::in);
    if (file.is_open()){
        std::string line;
        while(getline(file,line)){
            Record r;
            stringstream linestream(line);
            string data;

            //assigning temp.tconst value
            strcpy(r.tconst, line.substr(0, line.find('\t')).c_str());
            std::getline(linestream, data, '\t');

            //assigning temp.averageRating & temp.numVotes values
            linestream >> r.averageRating >> r.numVotes;
            Address address = disk.saveToDisk(&r, sizeof(Record));

        }
        file.close();
    
    std::cout<<"Number of blocks: "<<disk.getNumOfBlocks()<<endl;
    std::cout<<"Size of database: "<<disk.getSizeOfDatabase()<<" MB"<<endl;
    }
}

void Experiment2(int blocksize, MemoryPool disk, MemoryPool index){
    BPTree tree = BPTree(blocksize,&disk,&index);

    //read data.tsv file and load into disk storage
    std::fstream file;

    file.open("data/testdata.tsv",ios::in);
    if (file.is_open()){
        std::string line;
        while(getline(file,line)){
            Record r;
            stringstream linestream(line);
            string data;
            
            //assigning temp.tconst value
            strcpy(r.tconst, line.substr(0, line.find('\t')).c_str());
            std::getline(linestream, data, '\t');

            //assigning temp.averageRating & temp.numVotes values
            linestream >> r.averageRating >> r.numVotes;
            Address address = disk.saveToDisk(&r, sizeof(Record));
            std::cout<<address.blockAddress<<endl; 

            tree.insert(address,int(r.numVotes));

            //tree.display(tree.getRoot());
            //std::cout<<"next"<<"\n";
        }
        file.close();
    }
    tree.display(tree.getRoot());
}

void Experiment3(){

}

void Experiment4(){

}

void Experiment5(){

}

int main(){

    int blocksize = BlockSizeSelect();

    //initialize disk storage for memory pool 
    MemoryPool disk(150000000,blocksize);
    MemoryPool index(300000000,blocksize);

    // Experiment1(blocksize,disk,index);
    Experiment2(blocksize,disk,index);
    //insert function of experiment 3
    //insert function of experiment 4
    //insert function of experiment 5

    //repeat experiment(Y/N)
    return 0;
}