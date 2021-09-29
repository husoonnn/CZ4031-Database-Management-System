#include "mem_pool.h"
#include "types.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

//Get user choice for 100B or 500B
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

void Fileprocessor(){

    std::fstream file;

    file.open("data/data.tsv",ios::in);
    if (file.is_open()){
        std::string tp;
        while(getline(file,tp)){
            Record r;
            getline(file,tp,'\t');
            strcpy(r.tconst,tp.c_str());
            getline(file,tp,'\t');
            r.averageRating = std::atof(tp.c_str());
            getline(file,tp,'\t');
            r.numVotes = std::atoi(tp.c_str());
        }
        file.close();
    }
}

void Experiment1(int blocksize){
    
    MemoryPool disk(150000000,blocksize);
    
    std::cout<<"Number of blocks: "<<endl;
    std::cout<<"Size of database: "<<endl;
}

void Experiment2(){

}

void Experiment3(){

}

void Experiment4(){

}

void Experiment5(){

}

int main(){
    
    int blocksize = BlockSizeSelect();

    Fileprocessor();

    //allocate by seperating into multiple nodes per block

    Experiment1(blocksize);
    //insert function of experiment 2
    //insert function of experiment 3
    //insert function of experiment 4
    //insert function of experiment 5

    //repeat experiment(Y/N)
    return 0;
}