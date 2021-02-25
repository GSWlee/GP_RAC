//
// Created by 李志恺 on 2021/2/23.
//

#ifndef GP_RAC_CONTAINER_H
#define GP_RAC_CONTAINER_H
#include <string>

class Container {
private:
    int id;
    int coCPU;
    int coMem;
    std::string os;
    int VMid;
public:
    Container(int id,int coCPU,int coMem,std::string os);
    void setVMid(int VMid);
    int getId();
    int getCoCPU() const;
    int getCoMem();
    std::string getOs();
};


#endif //GP_RAC_CONTAINER_H
