#include <iostream>
#include "PM.h"
#include "VM.h"
#include "Container.h"
#include "Rule.h"
#include "data.h"
#include <algorithm>

int main() {
    int gen=100;
    std::vector<float> maps;
    srand((unsigned)time(NULL));
    std::vector<Rule> ruleList;
    data dataF;
    auto coList1=dataF.createContainers("Win",50);
    auto coList2=dataF.createContainers("Ubuntu",30);
    auto coList3=dataF.createContainers("CentOS",20);
    std::vector<Container> coList;
    coList.insert(coList.end(),coList1.begin(),coList1.end());
    coList.insert(coList.end(),coList2.begin(),coList2.end());
    coList.insert(coList.end(),coList3.begin(),coList3.end());
    auto vmTemplateList=dataF.createTemplateVM();
    for(int i = 0;i<20;i++){
        Rule temp(i);
        ruleList.push_back(temp);
        maps.push_back(0);
    }
    printf("init OK!\n");
    for(int g=0;g<gen;g++){
        if(g!=0){
            std::sort(ruleList.begin(),ruleList.end(),[maps](Rule a,Rule b){return maps[a.id]>maps[b.id];});
            printf("No %d gen\n",g);
            for(int i=0;i<10;i++){
                printf("NO %d : %f  ;",i,maps[i]);
            }
            auto nums=setRandOne(20,20);
            auto pairs=setRandPair(80,20);
            for(int i = 0;i<20;i++){
                ruleList[i].id=i;
            }
            printf("\nbegin %d mutate\n",g);
            for(int i=0;i<20;i++){
                ruleList[i+20]=mutation(ruleList[nums[i]],i+20,100);
            }
            printf("end %d mutate\n",g);
            for(int i=0;i<80;i++){
                auto temp=crossing(ruleList[pairs[i][0]],ruleList[pairs[i][1]],40+2*i,41+2*i);
                ruleList[40+2*i]=temp[0];
                ruleList[41+2*i]=temp[1];
            }
            printf("end %d crossing\n",g);

            for(int i=0;i<ruleList.size();i++){
                printf("test rule N0 %d: ",i);
                std::vector<VM> tVMList;
                std::vector<PM> pmList;
                std::vector<VM> vmList;
                tVMList.insert(tVMList.end(),vmTemplateList.begin(),vmTemplateList.end());
                tVMList.insert(tVMList.end(),vmList.begin(),vmList.end());
                for(int c=0;c<coList.size();c++){
                    int best=0;
                    float min=MAXFLOAT;
                    int v=0;
                    for(;v<tVMList.size();v++){
                        if(tVMList[v].isEnough(coList[c])){
                            auto temp=getArg(coList[c],tVMList[v]);
                            auto tweigth=ruleList[i].caculate(temp);
                            if(tweigth<min){
                                best=v;
                            }
                        }
                    }
                    if(best<10){
                        int flag=-1;
                        for(int p=0;p<pmList.size();p++){
                            if(pmList[p].isEnough(tVMList[best])){
                                auto t=VM(tVMList.size(),tVMList[best]);
                                t.addContainer(coList[c]);
                                pmList[p].addVM(t);
                                flag=1;
                                break;
                            }
                        }
                        if(flag==-1){
                            auto tp=dataF.createPM(pmList.size());
                            auto t=VM(tVMList.size(),tVMList[best]);
                            t.addContainer(coList[c]);
                            tp.addVM(t);
                            pmList.push_back(tp);
                        }
                    }else{
                        tVMList[best].addContainer(coList[c]);
                    }
                }
                printf(" finsh. caculating energe...");
                float total=0;
                for(int p=0;p<pmList.size();p++){
                    total+=pmList[p].getEnerge();
                }
                maps[i]=total;
                printf("   finsh\n");
            }
            printf("\n");
        }else{
            auto nums=setRandOne(20,20);
            auto pairs=setRandPair(80,20);
            printf("begin %d mutate\n",g);
            for(int i=0;i<20;i++){
                ruleList.push_back(mutation(ruleList[nums[i]],i+20,100));
                maps.push_back(0);
            }
            printf("end %d mutate\n",g);
            for(int i=0;i<80;i++){
                auto temp=crossing(ruleList[pairs[i][0]],ruleList[pairs[i][1]],40+2*i,41+2*i);
                ruleList.push_back(temp[0]);
                maps.push_back(0);
                ruleList.push_back(temp[1]);
                maps.push_back(0);
            }
            printf("end %d crossing\n",g);
            for(int i=0;i<ruleList.size();i++){
                printf("test rule N0 %d: ",i);
                std::vector<VM> tVMList;
                std::vector<PM> pmList;
                std::vector<VM> vmList;
                tVMList.insert(tVMList.end(),vmTemplateList.begin(),vmTemplateList.end());
                tVMList.insert(tVMList.end(),vmList.begin(),vmList.end());
                for(int c=0;c<coList.size();c++){
                    int best=0;
                    float min=MAXFLOAT;
                    int v=0;
                    for(;v<tVMList.size();v++){
                        if(tVMList[v].isEnough(coList[c])){
                            auto temp=getArg(coList[c],tVMList[v]);
                            auto tweigth=ruleList[i].caculate(temp);
                            if(tweigth<min){
                                best=v;
                            }
                        }
                    }
                    if(best<10){
                        int flag=-1;
                        for(int p=0;p<pmList.size();p++){
                            if(pmList[p].isEnough(tVMList[best])){
                                auto t=VM(tVMList.size(),tVMList[best]);
                                t.addContainer(coList[c]);
                                pmList[p].addVM(t);
                                flag=1;
                                break;
                            }
                        }
                        if(flag==-1){
                            auto tp=dataF.createPM(pmList.size());
                            auto t=VM(tVMList.size(),tVMList[best]);
                            t.addContainer(coList[c]);
                            tp.addVM(t);
                            pmList.push_back(tp);
                        }
                    }else{
                        tVMList[best].addContainer(coList[c]);
                    }
                }
                printf(" finsh. caculating energe...");
                float total=0;
                for(int p=0;p<pmList.size();p++){
                    total+=pmList[p].getEnerge();
                }
                maps[i]=total;
                printf("   finsh\n");
            }
            printf("\n");
        }

    }
    return 0;
}


//int main() {
//    int gen=10000;
//    srand((unsigned)time(NULL));
//    std::vector<Rule> ruleList;
//    std::map<std::string,int> value;
//    value["lvm"]=1;
//    value["lvc"]=2;
//    value["coC"]=3;
//    value["coM"]=4;
//    value["vMO"]=5;
//    value["vCO"]=6;
//    for(int i = 0;i<100;i++){
//        Rule temp(i);
//        ruleList.push_back(temp);
//    }
//    printf("init OK!\n");
//    for(int g=0;g<gen;g++){
//        if(g!=0){
//            std::sort(ruleList.begin(),ruleList.end(),[](Rule a,Rule b){return a.weight>b.weight;});
//            auto nums=setRandOne(100,100);
//            auto pairs=setRandPair(400,100);
//            printf("begin %d mutate\n",g);
//            for(int i=0;i<100;i++){
//                ruleList[i+100]=mutation(ruleList[nums[i]],i+100,100);
//            }
//            printf("end %d mutate\n",g);
//            for(int i=0;i<400;i++){
//                auto temp=crossing(ruleList[pairs[i][0]],ruleList[pairs[i][1]],200+2*i,201+2*i);
//            }
//            printf("end %d crossing\n",g);
//            for(int i=0;i<ruleList.size();i++){
//                ruleList[i].caculate(value);
//                printf("NO:%d = %lf ; ",i,ruleList[i].weight);
//            }
//            printf("\n");
//        }else{
//            auto nums=setRandOne(100,100);
//            auto pairs=setRandPair(400,100);
//            printf("begin %d mutate\n",g);
//            for(int i=0;i<100;i++){
//                ruleList.push_back(mutation(ruleList[nums[i]],i+100,100));
//            }
//            printf("end %d mutate\n",g);
//            for(int i=0;i<40;i++){
//                auto temp=crossing(ruleList[pairs[i][0]],ruleList[pairs[i][1]],200+2*i,201+2*i);
//                ruleList.push_back(temp[0]);
//                ruleList.push_back(temp[1]);
//            }
//            printf("end %d crossing\n",g);
//            for(int i=0;i<ruleList.size();i++){
//                ruleList[i].caculate(value);
//                printf("NO:%d = %lf ; ",i,ruleList[i].weight);
//            }
//            printf("\n");
//        }
//
//    }
//    return 0;
//}
