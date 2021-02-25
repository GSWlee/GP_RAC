//
// Created by 李志恺 on 2021/2/23.
//

#ifndef GP_RAC_VM_H
#define GP_RAC_VM_H
#include "Container.h"
#include <vector>
#include <string>

class VM {
private:
    int id;
    int type;
    int totalCPU;
    int totalMem;
    std::string os;
    int idleCPU;
    int idleMem;
    int remainCPU;
    int remainMem;
    int PMid;
    void setRemainCPU();
    void setRemainMem();
    std::vector<Container> list;
public:
    VM(int id,int totalCPU,int totalMem,std::string os,int idleCPU,int idleMen,int);
    VM(int id,const VM &vm);
    int getId();
    int getTotalCPU();
    int getTotalMem();
    int getIdleCPU();
    int getIdleMem();
    std::string getOs();
    int getRemainCPU();
    int getRemainMem();
    bool isEnough(Container c);
    void addContainer(Container c);
    void setPmId(int);
};


#endif //GP_RAC_VM_H
