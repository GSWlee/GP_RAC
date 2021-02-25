#include <iostream>
#include "PM.h"
#include "VM.h"
#include "Container.h"
#include "Rule.h"
#include "data.h"
#include <algorithm>



int main() {
    int gen=10000;
    srand((unsigned)time(NULL));
    std::vector<Rule> ruleList;
    std::map<std::string,int> value;
    value["lvm"]=1;
    value["lvc"]=2;
    value["coC"]=3;
    value["coM"]=4;
    value["vMO"]=5;
    value["vCO"]=6;
    for(int i = 0;i<100;i++){
        Rule temp(i);
        ruleList.push_back(temp);
    }
    printf("init OK!\n");
    for(int g=0;g<gen;g++){
        if(g!=0){
            std::sort(ruleList.begin(),ruleList.end(),[](Rule a,Rule b){return a.weight>b.weight;});
            auto nums=setRandOne(100,100);
            auto pairs=setRandPair(400,100);
            printf("begin %d mutate\n",g);
            for(int i=0;i<100;i++){
                ruleList[i+100]=mutation(ruleList[nums[i]],i+100,100);
            }
            printf("end %d mutate\n",g);
            for(int i=0;i<400;i++){
                auto temp=crossing(ruleList[pairs[i][0]],ruleList[pairs[i][1]],200+2*i,201+2*i);
            }
            printf("end %d crossing\n",g);
            for(int i=0;i<ruleList.size();i++){
                ruleList[i].caculate(value);
                printf("NO:%d = %lf ; ",i,ruleList[i].weight);
            }
            printf("\n");
        }else{
            auto nums=setRandOne(100,100);
            auto pairs=setRandPair(400,100);
            printf("begin %d mutate\n",g);
            for(int i=0;i<100;i++){
                ruleList.push_back(mutation(ruleList[nums[i]],i+100,100));
            }
            printf("end %d mutate\n",g);
            for(int i=0;i<40;i++){
                auto temp=crossing(ruleList[pairs[i][0]],ruleList[pairs[i][1]],200+2*i,201+2*i);
                ruleList.push_back(temp[0]);
                ruleList.push_back(temp[1]);
            }
            printf("end %d crossing\n",g);
            for(int i=0;i<ruleList.size();i++){
                ruleList[i].caculate(value);
                printf("NO:%d = %lf ; ",i,ruleList[i].weight);
            }
            printf("\n");
        }

    }
    return 0;
}
