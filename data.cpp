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

std::vector<VM> data::createTemplateVM(){
    std::vector<VM> templateVM;
    auto item0=VM(0,719,2005,"",70,200,0);
    templateVM.push_back(item0);
    auto item1=VM(1,917,951,"",90,90,1);
    templateVM.push_back(item1);
    auto item2=VM(2,1032,1009,"",100,100,2);
    templateVM.push_back(item2);
    auto item3=VM(3,1135,3542,"",110,350,3);
    templateVM.push_back(item3);
    auto item4=VM(4,1231,1989,"",120,190,4);
    templateVM.push_back(item4);
    auto item5=VM(5,1311,3238,"",130,320,5);
    templateVM.push_back(item5);
    auto item6=VM(6,1363,2634,"",130,260,6);
    templateVM.push_back(item6);
    auto item7=VM(7,1648,1538,"",160,153,7);
    templateVM.push_back(item7);
    auto item8=VM(8,2047,1181,"",200,118,8);
    templateVM.push_back(item8);
    auto item9=VM(9,2100,3013,"",210,300,9);
    templateVM.push_back(item9);
    return templateVM;
}