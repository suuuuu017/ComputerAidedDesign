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
//        std::cout << i << std::endl;
        std::cout << cubelist[i].readCube() << std::endl;
    }
}

void CubeList::incrementCubelistLength() {
    this->cubelistLength = this->cubelistLength + 1;
}

int CubeList::readcubelistLength() const {
    return cubelistLength;
}

bool CubeList::isEmptyList(CubeList &resultList) {
    return cubelistLength == 0;
}

bool CubeList::containDontCare(CubeList &resultList) {
    std::string dc(this->readCubeLength(), '-');
    std::vector<Cube>::iterator it;
    for(it = cubelist.begin(); it!= cubelist.end(); ++it){
        if(it->readCube() == dc){
            return true;
        }
    }
    return false;
}

bool CubeList::containOneCube(CubeList &resultList) {
    return cubelistLength == 1;
}

CubeList CubeList::deMorgan(CubeList inputCubeList) {
    Cube cube = inputCubeList.cubelist.back();
    CubeList returnCubeList(cubeLength);

    for(unsigned int it = 0; it < cube.cube.size(); ++it){
        if(cube.cube[it] == '-'){
            continue;
        }
        else if(cube.cube[it] == '1'){
            Cube returnCube(cubeLength);
            returnCube.cube[it] = '0';
//            std::cout << "the complement for 1 " << returnCube.readCube() << std::endl;
            returnCubeList.pushbackCube(returnCube);
        }
        else if(cube.cube[it] == '0'){
            Cube returnCube(cubeLength);
            returnCube.cube[it] = '1';
//            std::cout << "the complement for 0 " << returnCube.readCube() << std::endl;
            returnCubeList.pushbackCube(returnCube);
        }
    }
    return returnCubeList;
}

void CubeList::concatList(CubeList inputCubeList) {
    this->cubelist.insert(cubelist.end(), inputCubeList.cubelist.begin(), inputCubeList.cubelist.end());
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

Cube::Cube(int length): cube(length, '-') {
}

Cube::Cube(): cube(0) {
}
