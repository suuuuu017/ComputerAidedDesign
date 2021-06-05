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
    gate(std::string n, bool v = false, bool visit = false){
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

    void addNeighbour(std::string gate){
        this->neighbour.push_back(gate);
    };

    void addDirected(std::string gate){
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
//            std::cout << "it is " << *it << std::endl;
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
//            std::cout << inGateName << output << std::endl;
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
                output = output;
            }
        }
        this->val = output;
//        std::cout << "current gate operation is on   "<< name << "    " << this->val << " this is the value" << std::endl;
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
                //TODO: do i have to consider "input"?
            else if(!line.find("INPUT")){
                std::size_t found1 = 0;
                found1 = line.find('(');
                if(found1!=std::string::npos){
                    std::size_t found2 = line.find(')');
                    std::string inputName = line.substr(found1 + 1, found2 - found1 - 1);
                    //TODO: check if this subtraction is valid
                    gate t = gate(inputName);
                    t.updateType("buf");
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
                std::size_t found2 = line.find('(');
                //TODO: fix this hard code
                std::string gateName = line.substr(0, found1 - 1);
                gate t = gate(gateName);
                //TODO: fix this hard code
                std::string gateType = line.substr(found1 + 2, found2 - found1 - 2);
//                std::cout << gateType << " gate type is " << std::endl;
                t.updateType(gateType);
                //TODO: fix this hard code
                std::string Name = line.substr(found2 + 1);
                std::stringstream ss(Name);
                while(ss.good()){
                    std::string gate;
                    getline( ss, gate, ',' );
                    if(gate.find(')')){
                        gate = gate.substr(0, gate.find(')') );
                        gate = leftTrim(gate);
                    }
                    t.addNeighbour(gate);
                    t.increaseInDegree();
//                    std::cout << " degree is   " << t.readInDegree() << std::endl;
                    gateMap.at(gate).addDirected(gateName);
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

    while(!q.empty()){
        gate current = q.front();
        const char *type = (current.readType()).data();
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
//        std::cout << q.front().getName() << " visitibg front" << q.front().readDirected() << " "
//                  << std::endl;
        q.pop();
//        q.pop();
    }

    std::map<std::string, gate>::iterator it;

    for (it = outputMap.begin(); it != outputMap.end(); it++){
        std::string name = it->first;
        std::cout << name << " ";
        bool val = gateMap.at(name).getVal();
        std::cout << val << std::endl;
    }

//    std::map<std::string, gate, int>::iterator it;

//    for (it = gateMap.begin(); it != gateMap.end(); it++){
//        std::cout << it->first    // string (key)
//                  << " : name is "
//                  << it->second.getName()   // string's value
//                  << " type is "
//                  << it->second.readType()
//                  << " neighbout is "
//                  << it->second.readNeightbour()
//                  << " directed is "
//                  << it->second.readDirected()
//                  << " indegree is"
//                  << it->second.readInDegree()
//                  << std::endl;
//
//    }

};