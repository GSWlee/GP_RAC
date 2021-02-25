//
// Created by 李志恺 on 2021/2/23.
//

#include "PM.h"

PM::PM(int id, int totalCPU, int totalMem, float idleEnerge, float fullEnerge) {
    this->id=id;
    this->totalCPU=totalCPU;
    this->totalMem=totalMem;
    this->idleEnerge=idleEnerge;
    this->fullEnerge=fullEnerge;
}

int PM::getTotalMem() {
    return this->totalMem;
}

int PM::getId() {
    return this->id;
}

void PM::setRemainCPU() {
    int sum=0;
    for(auto item: this->list){
        sum+=item.getTotalCPU();
    }
    this->remainCPU=this->totalCPU-sum;
}

void PM::setRemainMem() {
    int sum=0;
    for(auto item: this->list){
        sum+=item.getTotalMem();
    }
    this->remainMem=this->totalMem-sum;
}

int PM::getTotalCPU() {
    return this->totalCPU;
}

int PM::getRemainMem() {
    return this->remainMem;
}

int PM::getRemainCPU() {
    return this->remainCPU;
}

bool PM::isEnough(VM vm) {
    if (vm.getTotalMem()<=this->totalMem&&vm.getTotalCPU()<= this->remainCPU){
        return true;
    }
    return false;
}

void PM::addVM(VM vm) {
    vm.setPmId(this->id);
    this->list.push_back(vm);
    setRemainMem();
    setRemainCPU();
}

float PM::getEnerge() {
    int sum=0;
    for (auto item:this->list){
        sum+=item.getTotalCPU()-item.getRemainCPU();
    }
    return (this->fullEnerge-this->idleEnerge)*(sum/this->totalCPU)+this->idleEnerge;
}