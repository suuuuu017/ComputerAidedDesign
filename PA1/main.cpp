//
// Created by ShiHe Wang on 2021/6/3.
//
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <map>

const std::string WHITESPACE = " \n\r\t\f\v";

std::string leftTrim(const std::string & line)
{
    size_t start = line.find_first_not_of(WHITESPACE);
    if(start == std::string::npos){
        return "";
    }
    else{
        return line.substr(start);
    }
}

std::string rightTrim(const std::string & line)
{
    size_t end = line.find_last_not_of(WHITESPACE);
    if(end == std::string::npos){
        return "";
    }
    else{
        line.substr(0, end + 1);
    }
}

std::string trim(const std::string & line) {
    return rightTrim(leftTrim(line));
}

class gate{
protected:
    std::string name;
    bool val;
    int inDegree;
    std::vector<gate*> neighbour;
    bool visited;

public:
    gate(std::string n, bool v = false, bool visit = false){
        this->name = n;
        this->val = v;
        this->visited = visit;
        this->inDegree = 0;
    };

    void visitGate(){
        this->visited = true;
    }

    void addNeighbour(gate* gate){
        this->neighbour.push_back(gate);
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

    void assignInDegree(){
        this->inDegree = neighbour.size();
    }
};

std::queue<gate*> q;

std::map<std::string, gate> gateMap;

void readNetlist(std::ifstream & netlist){
    std::string line;
    while(netlist){
        std::getline(netlist, line);
        if(netlist){
            if(line[0] == '#'){
                continue;
            }
            else if(line == ""){
                continue;
            }
            //TODO: do i have to consider "input"?
            else if(line.find("INPUT")){
                std::size_t found = 0;
                found = line.find_first_of("INPUT");
                if(found!=std::string::npos){
                    std::string tmp = line.substr(found);
                    std::string inputName = trim(tmp);
                    gateMap[inputName] = gate(inputName);
                }
            }
            else if(line.find("OUTPUT")){
                std::size_t found = 0;
                found = line.find_first_of("OUTPUT");
                if(found!=std::string::npos){
                    std::string tmp = line.substr(found);
                    std::string outputName = trim(tmp);
                    gateMap[outputName] = gate(outputName);
                }
            }
        }
    }
};

void readInputVal(std::ifstream & inputValue){

};

int main(int argc, char * argv[]){
    std::string netlistName = argv[1];
    std::string inputValueName = argv[2];
    std::ifstream netlist;
    std::ifstream inputValue;
    netlist.open(netlistName);
    inputValue.open(inputValueName);

    readNetlist(netlist);
    readInputVal(inputValue);
};