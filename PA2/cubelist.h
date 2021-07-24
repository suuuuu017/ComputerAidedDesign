#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>


class Cube{
private:
    std::vector<char> cube;
    friend class CubeList;
public:
    Cube(int length);

    void loadCube(std::istream &input);

    std::string readCube();
};

//a vector of cube class
class CubeList{
private:
    int cubeLength;
    int cubelistLength;
    std::vector<Cube> cubelist;
public:
    CubeList(int cubeLength);

    int readCubeLength() const;

    void pushbackCube(Cube cube);

    void readCubeList();

    void incrementCubelistLength();

    int readcubelistLength() const;

    bool isEmptyList(CubeList &resultList);

    bool containDontCare(CubeList &resultList);

    bool containOneCube(CubeList &resultList);

    CubeList deMorgan(CubeList inputCubeList);

    void concatList(CubeList inputCubeList);
};