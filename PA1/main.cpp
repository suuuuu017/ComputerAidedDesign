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

class gate;
std::map<std::string, gate> gateMap;

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
        return line.substr(0, end + 1);
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
    std::vector<std::string> directed;
    bool visited;
    std::string gateType;

public:
    gate(std::string& n, bool v = false, bool visit = false){
        this->name = n;
        this->val = v;
        this->visited = visit;
        this->inDegree = 0;
    };

    std::vector<std::string> getNeighbour(){
        return neighbour;
    }

    std::vector<std::string> getDericted(){
        return directed;
    }

    void updateVal(bool& val){
        this->val = val;
    }

    void updateType(std::string type){
        this->gateType = type;
    }

    std::string readType(){
        return gateType;
    }

    std::string getName(){
        return name;
    }

    bool& getVal(){
        return val;
    }

    void visitGate(){
        this->visited = true;
    }

    void addNeighbour(std::string & gate){
        this->neighbour.push_back(gate);
    };

    void addDirected(std::string& gate){
        this->directed.push_back(gate);
    };

    std::string readNeightbour(){
        std::string neighbourName = "";
        std::vector<std::string>::iterator it;
        for(it = neighbour.begin(); it != neighbour.end(); ++it) {
            neighbourName = neighbourName + (*it);
        }
        return neighbourName;
    }

    std::string readDirected(){
        std::string directedName = "";
        std::vector<std::string>::iterator it;
        for(it = directed.begin(); it != directed.end(); ++it) {
            directedName = directedName + (*it);
        }
        return directedName;
    }

    void logicOperation(const char *op, std::vector<std::string> input){
        std::vector<std::string>::iterator it;
        std::string inGateName;
        bool output = val;
        if(input.size()) {
            inGateName = *input.begin();
            output = gateMap.at(inGateName).getVal();
            if (strcmp(op, "AND") == 0 || strcmp(op, "and") == 0) {
                for (it = ++input.begin(); it != input.end(); ++it) {
                    output = output & gateMap.at((*it)).getVal();
                }
            }
            if (strcmp(op, "OR") == 0 || strcmp(op, "or") == 0) {
                for (it = ++input.begin(); it != input.end(); ++it) {
                    output = output | gateMap.at((*it)).getVal();
                }
            } else if (strcmp(op, "NAND") == 0 || strcmp(op, "nand") == 0) {
                for (it = ++input.begin(); it != input.end(); ++it) {
                    output = output & gateMap.at((*it)).getVal();
                }
                output = !output;
            } else if (strcmp(op, "NOR") == 0 || strcmp(op, "nor") == 0) {
                for (it = ++input.begin(); it != input.end(); ++it) {
                    output = output | gateMap.at((*it)).getVal();
                }
                output = !output;
            } else if (strcmp(op, "XOR") == 0 || strcmp(op, "xor") == 0) {
                for (it = ++input.begin(); it != input.end(); ++it) {
                    output = output ^ gateMap.at((*it)).getVal();
                }
            } else if (strcmp(op, "XNOR") == 0 || strcmp(op, "xnor") == 0) {
                for (it = ++input.begin(); it != input.end(); ++it) {
                    output = output ^ gateMap.at((*it)).getVal();
                }
                output = !output;
            } else if (strcmp(op, "NOT") == 0 || strcmp(op, "not") == 0) {
                output = !output;
            } else if (strcmp(op, "BUF") == 0 || strcmp(op, "buf") == 0) {
            }
        }
        this->val = output;
    };

    void increaseInDegree(){
        this->inDegree = this->inDegree + 1;
    }

    void decreaseInDegree(){
        this->inDegree = this->inDegree - 1;
    }

    int readInDegree(){
        return inDegree;
    }
};

std::queue<gate> q;

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
            else if(!line.find("INPUT") || !line.find("input")){
                std::size_t found1 = 0;
                found1 = line.find('(');
                if(found1!=std::string::npos){
                    std::size_t found2 = line.find(')');
                    std::string inputName = line.substr(found1 + 1, found2 - found1 - 1);
                    inputName = trim(inputName);
                    gate t = gate(inputName);
                    t.updateType("buf");
                    gateMap.insert(std::make_pair(inputName, t));
                }
                continue;
            }
            else if(!line.find("OUTPUT")|| !line.find("output")){
                std::size_t found1 = 0;
                found1 = line.find('(');
                if(found1!=std::string::npos){
                    std::size_t found2 = line.find(')');
                    std::string outputName = line.substr(found1 + 1, found2 - found1 - 1);
                    outputName = trim(outputName);
                    gate t = gate(outputName);
                    outputMap.insert(std::make_pair(outputName, t));
                }
                continue;
            }
            else if(line.find("=")){
                std::size_t found1 = line.find('=');
                std::size_t found2 = line.find('(');
                std::string gateName = line.substr(0, found1);
                gateName = trim(gateName);
//                std::cout << "gatename is ???" << gateName << " end"<< std::endl;
                gate t = gate(gateName);
                if(gateMap.find(gateName) == gateMap.end()){
//                    std::cout << "gate is  ,,,,, " << gateName << std::endl;
                    t = gate(gateName);
                    gateMap.insert(std::make_pair(gateName, t));
                }
//                gate t = gate(gateName);
                else{
                    t = gateMap.at(gateName);
                }
                //TODO: fix this hard code
                std::string gateType = line.substr(found1 + 1, found2 - found1 - 1);
                gateType = trim(gateType);
//                std::cout << "gatetype is ......." << gateType << " end"<< std::endl;
//                std::cout << gateType << " gate type is " << std::endl;
                t.updateType(gateType);
                //TODO: fix this hard code
                std::string Name = line.substr(found2 + 1);
                std::stringstream ss(Name);
                while(ss.good()){
                    std::string gaten;
                    getline( ss, gaten, ',' );
                    if(gaten.find(')')){
                        gaten = gaten.substr(0, gaten.find(')'));
                        gaten = trim(gaten);
                    }
                    t.addNeighbour(gaten);
                    t.increaseInDegree();
//                    std::cout << " degree is   " << t.readInDegree() << std::endl;
                    if(gateMap.find(gaten) == gateMap.end()){
//                        std::cout << "gate is   " << gaten << std::endl;
                        gate f = gate(gaten);
                        f.addDirected(gateName);
                        gateMap.insert(std::make_pair(gaten, f));
                    }
                    else{
                        std::map<std::string, gate>::iterator itt = gateMap.find(gaten);
                        gate f = gateMap.at(gaten);
                        f.addDirected(gateName);
                        itt->second = f;
                    }
//                    gateMap.insert(std::make_pair(gaten, fix));
                }
                std::map<std::string, gate>::iterator itt = gateMap.find(gateName);
                itt->second = t;
//                if(flag){
//                    gateMap.insert(std::make_pair(gateName, t));
//                }
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
                q.push(gateMap.at(gateName));
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

    const char *type;
    while(!q.empty()){
        gate current = q.front();
        type = (current.readType()).data();
        current.logicOperation(type, current.getNeighbour());
//        std::cout << " type is " << type << " gate is " << current.getName() << " value is " << current.getVal() << std::endl;
        gateMap.at(current.getName()).updateVal(current.getVal());
        std::vector<std::string> toDecrease = current.getDericted();
        std::vector<std::string>::iterator it;
        if(!toDecrease.empty()) {
            for(it = toDecrease.begin(); it != toDecrease.end(); ++it) {
                gate& decreasing = gateMap.at(*it);
//                std::cout << "to decrease is " << "gate is " << decreasing.getName() << "value is" << decreasing.readInDegree() << std::endl;
                decreasing.decreaseInDegree();
                if (decreasing.readInDegree() == 0) {
                    q.push(decreasing);
                }
            }
        }
        current.visitGate();
        q.pop();
    }

    std::map<std::string, gate>::iterator it;

    for (it = outputMap.begin(); it != outputMap.end(); it++){
        std::string name = it->first;
        std::cout << name << " ";
        bool val = gateMap.at(name).getVal();
        std::cout << val << std::endl;
    }

};