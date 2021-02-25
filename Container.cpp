//
// Created by 李志恺 on 2021/2/23.
//

#include "Container.h"
Container::Container(int id,int coCPU,int coMem,std::string os){
    this->id=id;
    this->coCPU=coCPU;
    this->coMem=coMem;
    this->os=os;
};

int Container::getId() {
    return this->id;
}

int Container::getCoCPU() const {
    return this->coCPU;
}

int Container::getCoMem() {
    return this->coMem;
}

std::string Container::getOs() {
    return this->os;
}

void Container::setVMid(int VMid) {
    this->VMid=VMid;
}
