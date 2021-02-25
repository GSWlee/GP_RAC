//
// Created by 李志恺 on 2021/2/24.
//

#ifndef GP_RAC_RULE_H
#define GP_RAC_RULE_H

#include <map>
#include <string>
#include <vector>
#include "PM.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

static int seed=0;
static bool flag=true;
const static std::vector<std::string> KEY={"lvm","lvc","coC","coM","vMO","vCO"};
const static std::vector<char> MARKS={'+','-','*','/'};
struct node{
    bool isNum;
    std::string value="";
    char mark='\0';
    int level;
    node* left=nullptr;
    node* right=nullptr;
};

node* build(node* root,int);

node* mbuild(node*root,int);

std::map<std::string,int> getArg(Container,VM);

class Rule {
private:
    node* root;
    std::map<std::string,int> value;
    int sumNodes();
    int sumNodes(node*);
public:
    int id;
    float weight;
    Rule(int);
    Rule(const Rule&,int,int);
    float caculate();
    float caculate(std::map<std::string,int>);
    float caculate(node* root);
    node* select();
    node* select(int);
};

Rule mutation(Rule,int,int);

std::vector<Rule> crossing(Rule,Rule,int,int);

std::vector<int> setRandOne(int,int);

std::vector<std::vector<int>> setRandPair(int,int);

#endif //GP_RAC_RULE_H
