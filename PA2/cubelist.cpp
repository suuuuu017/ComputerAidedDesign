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
    for(unsigned int i= 0; i < cubelist.size(); i++){
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

bool CubeList::isEmptyList() {
    return cubelist.size() == 0;
}

bool CubeList::containDontCare() {
    std::string dc(this->readCubeLength(), '-');
    std::vector<Cube>::iterator it;
    for(it = cubelist.begin(); it!= cubelist.end(); ++it){
        if(it->readCube() == dc){
            return true;
        }
    }
    return false;
}

bool CubeList::containOneCube() {
    return cubelist.size() == 1;
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

int CubeList::chooseBinatevar(CubeList inputCubeList) {
    int varNum = 0;
    int rank[cubeLength][5];
    for(int i = 0; i < cubeLength; i++){
        for(int j = 0; j < 4; j++){
            rank[i][j] = 0;
        }
    }

    //first positive, second negative, third is absolut, fourth is the sum
    for(unsigned int i = 0; i < inputCubeList.cubelist.size(); i++){
        for(unsigned int j = 0; j < inputCubeList.cubelist[i].cube.size(); j++){
            if(inputCubeList.cubelist[i].cube[j] == '1'){
                rank[j][0] = rank[j][0] + 1;
            }
            else if(inputCubeList.cubelist[i].cube[j] == '0'){
                rank[j][1] = rank[j][1] + 1;
            }
        }
    }

    for(int i = 0; i < cubeLength; i++){
        rank[i][2] = abs(rank[i][0] - rank[i][1]);
        rank[i][3] = abs(rank[i][0] + rank[i][1]);
    }

    bool binateE = false;
    for(int i = 0; i < cubeLength; i++){
        if(rank[i][0] > 0 && rank[i][1] > 0){
            rank[i][4] = 1;
            binateE = true;
        }
    }

    if(!binateE){
//        std::cout << "here" << std::endl;
        std::vector<int> tie2Breaker;
        int unateNum = 0;

        for(int i = 0; i < cubeLength; i++) {
            if (rank[i][3] > unateNum) {
                unateNum = rank[i][3];
                varNum = i;
            }
        }
        for(int i = 0; i < cubeLength; i++){
            if(rank[i][3] == unateNum){
                tie2Breaker.push_back(i);
            }
        }

        if(tie2Breaker.size() == 1){
            return varNum;
        }

        int lowestIndex = cubeLength;
        for(unsigned int i = 0; i < tie2Breaker.size(); i++){
            if(tie2Breaker[i] < lowestIndex){
                lowestIndex = tie2Breaker[i];
            }
        }
        return lowestIndex;
    }

    int binateNum = 0;

    std::vector<int> tieBinate;

    for(int i = 0; i < cubeLength; i++) {
        if (rank[i][3] > binateNum && rank[i][4] == 1) {
            binateNum = rank[i][3];
            varNum = i;
        }
    }
    for(int i = 0; i < cubeLength; i++){
        if(rank[i][3] == binateNum && rank[i][4] == 1){
            std::cout << "biNum is " << binateNum << std::endl;
            tieBinate.push_back(i);
        }
    }
    if(tieBinate.size() == 1){
//        std::cout << "here2" << std::endl;
        return varNum;
    }

    std::cout << "ties  " << std::endl;
    for(unsigned int i = 0; i < tieBinate.size(); i++) {
        std::cout << tieBinate[i]  << " "<< rank[tieBinate[i]][2]<< " "<< rank[tieBinate[i]][4]<< std::endl;
    }
//    std::cout << "tiesNum is " << tieBinate.size() << std::endl;

    int breaktie1 = 1000000000;

    std::vector<int> tie1Breaker;

    for(unsigned int i = 0; i < tieBinate.size(); i++){
        if(rank[tieBinate[i]][2] < breaktie1 && rank[tieBinate[i]][4] == 1){
            breaktie1 = rank[tieBinate[i]][2] ;
            varNum = tieBinate[i];
        }
    }
    std::cout << "num is " << breaktie1 << std::endl;
    for(unsigned int i = 0; i < tieBinate.size(); i++){
        if(rank[tieBinate[i]][2] == breaktie1 && rank[tieBinate[i]][4] == 1){
            tie1Breaker.push_back(tieBinate[i]);
        }
    }
    if(tie1Breaker.size() == 1){
        return varNum;
    }

    std::cout << "ties arew " << std::endl;
    for(unsigned int i = 0; i < tie1Breaker.size(); i++) {
        std::cout << tie1Breaker[i] << std::endl;
    }

    int lowestIndex = cubeLength;
    for(unsigned int i = 0; i < tie1Breaker.size(); i++){
        std::cout << "ties arew " << std::endl;
        std::cout << tie1Breaker[i] << std::endl;
        if(tie1Breaker[i] < lowestIndex){
            lowestIndex = tie1Breaker[i] ;
            std::cout << std::endl;
            std::cout << lowestIndex << std::endl;
        }
    }
    return lowestIndex;
}

CubeList CubeList::positiveCo(CubeList inputCubeList, int var) {
    CubeList returnP(cubeLength);

    for(unsigned int i = 0; i < inputCubeList.cubelist.size(); i ++){
        if(inputCubeList.cubelist[i].cube[var] == '1'){
            inputCubeList.cubelist[i].cube[var] = '-';
            returnP.pushbackCube(inputCubeList.cubelist[i]);
        }
        else if(inputCubeList.cubelist[i].cube[var] == '-'){
            returnP.pushbackCube(inputCubeList.cubelist[i]);
        }
        else if(inputCubeList.cubelist[i].cube[var] == '0'){
            continue;
        }
    }
    return returnP;
}

CubeList CubeList::negativeCo(CubeList inputCubeList, int var) {
    CubeList returnN(cubeLength);

    for(unsigned int i = 0; i < inputCubeList.cubelist.size(); i ++){
        if(inputCubeList.cubelist[i].cube[var] == '0'){
            inputCubeList.cubelist[i].cube[var] = '-';
            returnN.pushbackCube(inputCubeList.cubelist[i]);
        }
        else if(inputCubeList.cubelist[i].cube[var] == '-'){
            returnN.pushbackCube(inputCubeList.cubelist[i]);
        }
        else if(inputCubeList.cubelist[i].cube[var] == '1'){
            continue;
        }
    }
    return returnN;
}

CubeList CubeList::positiveAnd(CubeList inputCubeList, int var) {
    std::vector<Cube>::iterator it;

    for(it = inputCubeList.cubelist.begin(); it != inputCubeList.cubelist.end(); it++){
        it->cube[var] = '1';
    }

    return inputCubeList;
}

CubeList CubeList::negativeAnd(CubeList inputCubeList, int var) {
    std::vector<Cube>::iterator it;

    for(it = inputCubeList.cubelist.begin(); it != inputCubeList.cubelist.end(); it++){
        it->cube[var] = '0';
    }

    return inputCubeList;
}


void Cube::loadCube(std::istream &input) {
    char c;
    while(input.get(c)){
        cube.push_back(c);
    }
}

std::string Cube::readCube() {
    std::string output;
    for(unsigned int i = 0; i < cube.size(); i++){
        output.push_back(cube[i]);
    }
    return output;
}

Cube::Cube(int length): cube(length, '-') {
}

Cube::Cube(): cube(0) {
}
