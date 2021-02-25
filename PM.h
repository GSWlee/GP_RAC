//
// Created by 李志恺 on 2021/2/23.
//

#ifndef GP_RAC_PM_H
#define GP_RAC_PM_H
#include <vector>
#include "VM.h"

class PM {
private:
    int id;
    int totalCPU;
    int totalMem;
    int remainCPU;
    int remainMem;
    float idleEnerge;
    float fullEnerge;
    void setRemainCPU();
    void setRemainMem();
    std::vector<VM> list;
public:
    PM(int id,int totalCPU,int totalMem,float idleEnerge,float fullEnerge);
    int getTotalCPU();
    int getTotalMem();
    int getId();
    int getRemainCPU();
    int getRemainMem();
    bool isEnough(VM vm);
    void addVM(VM vm);
    float getEnerge();
};


#endif //GP_RAC_PM_H
