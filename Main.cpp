   
#include "mem_pool.h"
#include "types.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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

void Fileprocessor(string filename){

    std::ifstream file(filename);
    std::vector<Record> v;
    std::string line;

    while(std::getline(file,line)){
        std::istringstream is(line);
        Record r;
        std::string s;

        std::getline(is,s,'\t');
        r.tconst = std::stoi(s);
    }

}

void Experiment1(){
    
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
    
    //int blocksize = BlockSizeSelect();

    Fileprocessor("data.tsv");

    //allocate by seperating into multiple nodes per block

    Experiment1();
    //insert function of experiment 2
    //insert function of experiment 3
    //insert function of experiment 4
    //insert function of experiment 5

    //repeat experiment(Y/N)
    return 0;
}