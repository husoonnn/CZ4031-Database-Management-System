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

void Experiment1(int blocksize, MemoryPool disk, MemoryPool index){
    
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

            tree.insert(address,int(r.numVotes));

        }
        file.close();
    }
    
    std::cout<<"Parameter n of the tree is: "<<tree.getMaxKeys(blocksize)<<endl;
    std::cout<<"Number of nodes of the B+ tree: "<<endl;
    std::cout<<"Height of B+ tree is: "<<tree.getHeight()<<endl;
    // tree.displayNode();
    std::cout<<"Content of root node and it's first child node: "<<endl;
    // tree.display(tree.getRoot());
}

void Experiment3(){

}

void Experiment4(){

}

void Experiment5(int blocksize, MemoryPool disk, MemoryPool index){
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

            tree.insert(address,int(r.numVotes));

        }
        file.close();
    }
    tree.display(tree.getRoot());
    tree.deleteKey(1807);
    //tree.LLdisplay(tree.getRoot());
    
}

int main(){

    int blocksize = BlockSizeSelect();

    streambuf *coutbuf = std::cout.rdbuf(); //save old buffer

    // save experiment1 logging
    ofstream out1("outputs/experiment1_" + to_string(blocksize) + "B.txt");
    std::cout.rdbuf(out1.rdbuf()); 

    //initialize disk storage for memory pool 
    MemoryPool disk(150000000,blocksize);
    MemoryPool index(300000000,blocksize);

    //construct 
    BPTree tree = BPTree(blocksize,&disk,&index);

    //file creation
    std::fstream file;

    //datasets
    //file.open("data/data.tsv",ios::in);
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

            tree.insert(address,int(r.numVotes));

        }
        file.close();
    }

    //Experiment 1
    std::cout<<"Number of blocks: "<<disk.getNumOfBlocks()<<endl;
    std::cout<<"Size of database: "<<disk.getSizeOfDatabase()<<" MB"<<endl;

    std::cout.rdbuf(coutbuf);

    ofstream out2("outputs/experiment2_" + to_string(blocksize) + "B.txt");
    std::cout.rdbuf(out2.rdbuf()); 
    // Experiment2(blocksize,disk,index);
    std::cout<<"Parameter n of the tree is: "<<tree.getMaxKeys(blocksize)<<endl;
    std::cout<<"Number of nodes of the B+ tree: "<<endl;
    std::cout<<"Height of B+ tree is: "<<tree.getHeight()<<endl;
    // tree.displayNode();
    std::cout<<"Content of root node and it's first child node: "<<endl;

    std::cout.rdbuf(coutbuf);
    //insert function of experiment 3
    
    //insert function of experiment 4
    
    // Experiment5(blocksize,disk,index);

    //repeat experiment(Y/N)
    return 0;
}