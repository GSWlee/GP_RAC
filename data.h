//
// Created by 李志恺 on 2021/2/25.
//

#ifndef GP_RAC_DATA_H
#define GP_RAC_DATA_H
#include "PM.h"
#include "Rule.h"
class data {
    std::vector<Container> createContainers(std::string os,int,int start=0);
    PM createPM(int);
    VM createVM(int,int);

};


#endif //GP_RAC_DATA_H
