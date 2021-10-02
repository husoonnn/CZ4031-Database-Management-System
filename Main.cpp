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
    file.open("data/data.tsv",ios::in);
    // file.open("data/testdata.tsv",ios::in);
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
    std::cout <<"*************************************Experiment 1*************************************"<<endl;
    std::cout<<"Number of blocks: "<<disk.getNumOfBlocks()<<" blocks"<<endl;
    std::cout<<"Size of database: "<<disk.getSizeOfDatabase()<<"B"<<endl;

    //Save output to experiment1.txt
    std::cout.rdbuf(coutbuf);

    //Experiment 2
    ofstream out2("outputs/experiment2_" + to_string(blocksize) + "B.txt");
    std::cout.rdbuf(out2.rdbuf()); 

    std::cout <<"*************************************Experiment 2*************************************"<<endl;
    std::cout<<"Parameter n of the tree is: "<<tree.getMaxKeys(blocksize)<<endl;
    std::cout<<"Number of nodes of the B+ tree: "<< tree.getnumNodes()<<endl;
    std::cout<<"Height of B+ tree is: "<<tree.getHeight()<<endl;
    std::cout<<"Content of root node and it's first child node: "<<endl;
    tree.displayNode(tree.getRoot());

    //Save output to experiment2.txt
    std::cout.rdbuf(coutbuf);

    //Experiment 3
    ofstream out3("outputs/experiment3_" + to_string(blocksize) + "B.txt");
    std::cout.rdbuf(out3.rdbuf()); 

    std::cout <<"*************************************Experiment 3*************************************"<<endl;
    // std::cout <<"Retrieving the attribute tconst of those movies with numVotes equal to 500..."<<endl;     
    // tree.search(500,500);
    // std::cout << endl;
    // std::cout <<"Number of index blocks the process accesses: "<<index.resetBlocksAccessed()<<endl; 
    // std::cout <<"Number of record blocks the process accesses: "<<disk.resetBlocksAccessed()<<endl;
    // std::cout << "\nNo more records found for numVotes equal to 500 "<< endl;
    
    //Save output to experiment3.txt
    std::cout.rdbuf(coutbuf);

    //Experiment 4
    ofstream out4("outputs/experiment4_" + to_string(blocksize) + "B.txt");
    std::cout.rdbuf(out4.rdbuf()); 
    
    std::cout <<"*************************************Experiment 4*************************************"<<endl;
    // std::cout <<"Retrieving the attribute tconst of those movies with numVotes from 30,000 to 40,000 (inclusively)..."<<endl;
    // tree.search(30000, 40000); 
    // std::cout << endl;
    // std::cout <<"Number of index blocks the process accesses: "<<index.resetBlocksAccessed()<<endl; 
    // std::cout <<"Number of data blocks the process accesses: "<<disk.resetBlocksAccessed()<<endl;
  
    
    //Save output to experiment4.txt
    std::cout.rdbuf(coutbuf);
    
    // Experiment5
    ofstream out5("outputs/experiment5_" + to_string(blocksize) + "B.txt");
    std::cout.rdbuf(out5.rdbuf()); 

    std::cout <<"*************************************Experiment 5*************************************"<<endl;

    //Save output to experiment5.txt
    std::cout.rdbuf(coutbuf);

    //repeat experiment(Y/N)
    return 0;
}