//
// Created by 李志恺 on 2021/2/23.
//

#include "VM.h"
VM::VM(int id, int totalCPU, int totalMem, std::string os, int idleCPU, int idleMem,int type) {
    this->id=id;
    this->totalCPU=totalCPU;
    this->totalMem=totalMem;
    this->os=os;
    this->idleCPU=idleCPU;
    this->idleMem=idleMem;
    this->type=type;
}

int VM::getId() {
    return this->id;
}

int VM::getIdleMem() {
    return this->idleMem;
}

int VM::getIdleCPU() {
    return this->idleCPU;
}

std::string VM::getOs() {
    return this->os;
}

int VM::getTotalCPU() {
    return this->totalCPU;
}

int VM::getTotalMem() {
    return this->totalMem;
}

int VM::getRemainCPU() {
    return this->remainCPU;
}

int VM::getRemainMem() {
    return this->remainMem;
}

VM::VM(int id,const VM &vm) {
    this->id=id;
    this->totalCPU=vm.totalCPU;
    this->totalMem=vm.totalMem;
    this->os=vm.os;
    this->idleCPU=vm.idleCPU;
    this->idleMem=vm.totalMem;
    this->type=vm.type;
}

void VM::setPmId(int Pmid) {
    this->PMid=Pmid;
}

void VM::setRemainCPU() {
    int sum=0;
    for(int i=0;i< this->list.size();i++){
        sum+=list[i].getCoCPU();
    }
    this->remainCPU= this->totalCPU-sum-this->idleCPU;
}

void VM::setRemainMem() {
    int sum=0;
    for(int i=0;i< this->list.size();i++){
        sum+=list[i].getCoMem();
    }
    this->remainMem= this->totalMem-sum-this->idleMem;
}

bool VM::isEnough(Container c) {
    if(c.getCoCPU()<= this->remainCPU&&c.getOs()==this->os&&c.getCoMem()<=this->remainMem){
        return true;
    }
    return false;
}

void VM::addContainer(Container c) {
    c.setVMid(this->id);
    this->list.push_back(c);
    setRemainMem();
    setRemainCPU();
}