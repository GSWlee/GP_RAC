//
// Created by 李志恺 on 2021/2/25.
//

#include "data.h"

std::vector<Container> data::createContainers(std::string os,int total, int start) {
    std::vector<Container> coList;
    for(int i=0;i<total;i++){
        //srand((unsigned)time(NULL)+seed++);
        int coCPU=rand()%200+50;
        int coMem=rand()%400+100;
        coList.push_back(Container(i+start,coCPU,coMem,os));
    }
    return coList;
}

PM data::createPM(int id) {
    return PM(id,3300,4000,200,2000);
}