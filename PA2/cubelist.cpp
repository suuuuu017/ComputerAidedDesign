#include <iostream>
#include "cubelist.h"

CubeList::CubeList(int cubeLength): cubeLength(cubeLength), cubelistLength(0) {
}

int CubeList::readCubeLength() const {
    return cubeLength;
}

void CubeList::pushbackCube(Cube cube) {
    cubelist.push_back(cube);
}

void CubeList::readCubeList() {
    for(int i= 0; i < cubelist.size(); i++){
        std::cout << cubelist[i].readCube() << std::endl;
    }
}

void CubeList::incrementCubelistLength() {
    this->cubelistLength = this->cubelistLength + 1;
}

int CubeList::readcubelistLength() const {
    return cubelistLength;
}


void Cube::loadCube(std::istream &input) {
    char c;
    while(input.get(c)){
        cube.push_back(c);
    }
}

std::string Cube::readCube() {
    std::string output;
    for(int i = 0; i < cube.size(); i++){
        output.push_back(cube[i]);
    }
    return output;
}
