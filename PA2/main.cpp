#include <iostream>
#include <fstream>
#include <sstream>

#include "cubelist.h"

class tooFewArgument{};

CubeList complement(CubeList cubel){
    std::cout << "input cube is " << std::endl;
    cubel.readCubeList();
    if(cubel.isEmptyList()){
//        std::cout << "here1" << std::endl;
        CubeList resultList(cubel.readCubeLength());
        Cube tmpcube(cubel.readCubeLength());
        resultList.pushbackCube(tmpcube);
        return resultList;
    }
    else if(cubel.containDontCare()){
//        std::cout << "here2" << std::endl;
        CubeList resultList(cubel.readCubeLength());
        return resultList;
    }
    else if(cubel.containOneCube()){
        std::cout << "here one cube" << std::endl;
        CubeList resultList(cubel.readCubeLength());
        CubeList cubeR = cubel.deMorgan(cubel);
        resultList.concatList(cubeR);
        return resultList;
    }
    else{
        int x = cubel.chooseBinatevar(cubel);
        std::cout << "x is " << x << std::endl;


        CubeList pCo = cubel.positiveCo(cubel, x);
        std::cout << "poCo is " << std::endl;
        pCo.readCubeList();
        CubeList nCo = cubel.negativeCo(cubel, x);
        std::cout << "neCo is " << std::endl;
        nCo.readCubeList();

        CubeList P = complement(pCo);
        std::cout << "P is " << std::endl;
        P.readCubeList();
        CubeList N = complement(nCo);
        std::cout << "N is " << std::endl;
        N.readCubeList();

        P = P.positiveAnd(P, x);
        std::cout << "P fillingin is " << std::endl;
        P.readCubeList();
        N = N.negativeAnd(N, x);
        std::cout << "P fillingin is " << std::endl;
        P.readCubeList();

        P.concatList(N);
        return P;
    }
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

    resultCubeList = complement(cubelist);

    std::cout << "result cube list is" << std::endl;
    std::cout << resultCubeList.readCubeLength() << std::endl;
    resultCubeList.readCubeList();



    inputFile.close();

}