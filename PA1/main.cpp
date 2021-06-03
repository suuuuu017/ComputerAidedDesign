//
// Created by ShiHe Wang on 2021/6/3.
//
#include <iostream>
#include <vector>
#include <queue>

class gate{
protected:
    bool val;
    std::string name;
    int inDegree;
    std::vector<gate*> neighbour;
    bool visited;

public:
    gate(std::string name){
        name = name;
    };

    void addNeighbour(){

    };

    void logicOperation(){

    };
};

std::queue<gate*> q;

void readNetlist(){

};

int main(){

};