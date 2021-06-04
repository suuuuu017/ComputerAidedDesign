//
// Created by ShiHe Wang on 2021/6/3.
//
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <map>
#include <sstream>

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
    std::vector<std::string> neighbour;
    bool visited;

public:
    gate(std::string n, bool v = false, bool visit = false){
        this->name = n;
        this->val = v;
        this->visited = visit;
        this->inDegree = 0;
    };

    void updateVal(bool val){
        this->val = val;
    }

    std::string getName(){
        return name;
    }

    void visitGate(){
        this->visited = true;
    }

    void addNeighbour(std::string gate){
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

    int readInDegree(){
        return inDegree;
    }
};

std::queue<gate*> q;

std::map<std::string, gate> gateMap;
std::map<std::string, gate> inputMap;
std::map<std::string, gate> outputMap;

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
            else if(!line.find("INPUT")){
                std::size_t found1 = 0;
                found1 = line.find('(');
                if(found1!=std::string::npos){
                    std::size_t found2 = line.find(')');
                    std::string inputName = line.substr(found1 + 1, found2 - found1 - 1);
                    //TODO: check if this subtraction is valid
                    gate t = gate(inputName);
                    gateMap.insert(std::make_pair(inputName, t));
                }
                continue;
            }
            else if(!line.find("OUTPUT")){
                //TODO: why is !line.find
                std::size_t found1 = 0;
                found1 = line.find('(');
                if(found1!=std::string::npos){
                    std::size_t found2 = line.find(')');
                    std::string outputName = line.substr(found1 + 1, found2 - found1 - 1);
                    //TODO: check if this subtraction is valid
                    gate t = gate(outputName);
                    outputMap.insert(std::make_pair(outputName, t));
                }
                continue;
            }
            else if(line.find("=")){
                //TODO: why is !line.find
                std::size_t found1 = line.find('=');
                std::string gateName = line.substr(0, found1);
                gate t = gate(gateName);
                std::string Name = line.substr(found1);
                std::stringstream ss(Name);
                while(ss.good()){
                    std::string gate;
                    getline( ss, gate, ',' );
                    t.addNeighbour(gate);
                }
                gateMap.insert(std::make_pair(gateName, t));
                continue;
            }
        }
    }
};

void readInputVal(std::ifstream & inputValue){
    std::string line;
    while(inputValue){
        std::getline(inputValue, line);
        if(inputValue){
            std::size_t found = line.find(" ");
            if(found!=std::string::npos){
                std::string gateName = line.substr(0, found);
                std::string gateVal = line.substr(found + 1);
                bool updateVal;
                if(gateVal == "1"){
                    updateVal = true;
                }
                else{
                    updateVal = false;
                }
                gateMap.at(gateName).updateVal(updateVal);
            }
        }
    }

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