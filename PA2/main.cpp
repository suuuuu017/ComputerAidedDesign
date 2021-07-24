#include <iostream>
#include <fstream>
#include <sstream>

#include "cubelist.h"

class tooFewArgument{};

CubeList complement(CubeList& cubel, CubeList &resultList){
    if(cubel.isEmptyList(resultList)){
        Cube tmpcube(cubel.readCubeLength());
        resultList.pushbackCube(tmpcube);
        return resultList;
    }
    else if(cubel.containDontCare(resultList)){
        return resultList;
    }
    else if(cubel.containOneCube(resultList)){
//        std::cout << "here" << std::endl;
        CubeList cubeR = cubel.deMorgan(cubel);
        resultList.concatList(cubeR);
        return resultList;
    }
    return resultList;
}

int main(int argc, char * argv[]){
    if(argc < 2 || argc > 2){
        throw tooFewArgument();
    }

    std::string filePath = argv[1];

    std::ifstream inputFile;
    inputFile.open(filePath);

    std::string line;

    int cubelength = 0;

    while(inputFile){
        getline(inputFile, line);
        if(inputFile){
//            std::cout << line << std::endl;
            std::stringstream instr(line);
            instr >> cubelength;
        }
        break;
    }

    CubeList cubelist(cubelength);

    std::cout << cubelist.readCubeLength() << std::endl;

    while(inputFile){
        getline(inputFile, line);
        if(inputFile){
//            std::cout << line << std::endl;
            std::stringstream instr(line);
            Cube tmpCube;
            tmpCube.loadCube(instr);
            cubelist.pushbackCube(tmpCube);
            cubelist.incrementCubelistLength();
        }
    }

    cubelist.readCubeList();

    std::cout << cubelist.readcubelistLength() << std::endl;

    CubeList resultCubeList(cubelength);

    complement(cubelist, resultCubeList);

    std::cout << "result cube list is" << std::endl;
    std::cout << resultCubeList.readCubeLength() << std::endl;
    resultCubeList.readCubeList();



    inputFile.close();

}