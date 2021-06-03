//
// Created by ShiHe Wang on 2021/6/3.
//
#include <iostream>
#include <vector>
#include <queue>
#include <string>

class gate{
protected:
    std::string name;
    bool val;
    int inDegree;
    std::vector<gate*> parent;
    std::vector<gate*> child;
    bool visited;

public:
    gate(std::string name, bool val){
        name = name;
        val = val;
    };

    void addNeighbour(){

    };

    void logicOperation(const char* &op, std::vector<gate*> input, bool output){
        output = (*input.begin())->val;
        if(strcmp(op, "AND") == 0 || strcmp(op, "and") == 0){
            for(auto it = ++input.begin(); it != input.end(); ++it) {
                output = output & (*it)->val;
            }
        }
        if(strcmp(op, "OR") == 0 || strcmp(op, "or") == 0){
            for(auto it = ++input.begin(); it != input.end(); ++it) {
                output = output | (*it)->val;
            }
        }
        else if(strcmp(op, "NAND") == 0 || strcmp(op, "nand") == 0){
            for(auto it = ++input.begin(); it != input.end(); ++it) {
                output = output & (*it)->val;
            }
            output = !output;
        }
        else if(strcmp(op, "NOR") == 0 || strcmp(op, "nor") == 0){
            for(auto it = ++input.begin(); it != input.end(); ++it) {
                output = output | (*it)->val;
            }
            output = !output;
        }
        else if(strcmp(op, "XOR") == 0 || strcmp(op, "xor") == 0) {
            for (auto it = ++input.begin(); it != input.end(); ++it) {
                output = output ^ (*it)->val;
            }
        }
        else if(strcmp(op, "XNOR") == 0 || strcmp(op, "xnor") == 0) {
            for (auto it = ++input.begin(); it != input.end(); ++it) {
                output = output ^ (*it)->val;
            }
            output = !output;
        }
        else if(strcmp(op, "NOT") == 0 || strcmp(op, "not") == 0) {
            output = !output;
        }
        else if (strcmp(op, "BUF") == 0 || strcmp(op, "buf") == 0) {
            output = output;
        }
        this->val = output;
    };
};

std::queue<gate*> q;

void readNetlist(){

};

void readInputVal(){

};

int main(int argc, char * argv[]){

};