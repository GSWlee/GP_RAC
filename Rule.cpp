//
// Created by 李志恺 on 2021/2/24.
//

#include "Rule.h"


node* build(node* root,int level=0){
    if(level<5){
        ////srand((unsigned)time(NULL)+seed++);
        if(level==4){
            int index=rand()%KEY.size();
            root=new (node);
            root->value=KEY[index];
            root->isNum= true;
            root->level=level;
        }else if(level==0) {
            //srand((unsigned)time(NULL)+seed++);
            int index=rand()%MARKS.size();
            root=new (node);
            root->level=level;
            root->mark=MARKS[index];
            root->isNum= false;
            root->left=build(root->left,level+1);
            root->right=build(root->right,level+1);
        }else{
            //srand((unsigned)time(NULL)+seed++);
            int temp=rand()%5;
            if(temp>=level){
                //srand((unsigned)time(NULL)+seed++);
                int index=rand()%MARKS.size();
                root=new (node);
                root->level=level;
                root->mark=MARKS[index];
                root->isNum= false;
                root->left=build(root->left,level+1);
                root->right=build(root->right,level+1);
            }else{
                //srand((unsigned)time(NULL)+seed++);
                int index=rand()%KEY.size();
                root=new (node);
                root->level=level;
                root->value=KEY[index];
                root->isNum= true;
            }
        }
        return root;
    }else{
        return root;
    }
}

node* mbuild(node* root,int p){
    if(root==nullptr){
        return root;
    }
    node* temp=new (node);
    temp->level=root->level;
    //srand((unsigned)time(NULL)+seed++);
    int tem=abs(rand()%100);
    if(tem<=p){
        if(root->isNum){
            temp->mark=root->mark;
            temp->isNum= root->isNum;
            //srand((unsigned)time(NULL)+seed++);
            temp->value=KEY[rand()%KEY.size()];
        } else{
            //srand((unsigned)time(NULL)+seed++);
            temp->mark=MARKS[rand()%MARKS.size()];
            temp->value=root->value;
            temp->isNum= root->isNum;
            temp->left=mbuild(root->left,p);
            temp->right=mbuild(root->right,p);
        }
    }else{
        temp->value=root->value;
        temp->mark=root->mark;
        temp->isNum= root->isNum;
        temp->left=mbuild(root->left,p);
        temp->right=mbuild(root->right,p);
    }
    return temp;
}

std::map<std::string,int> getArg(Container c,VM v){
    std::map<std::string,int> value;
    value["lvm"]=v.getRemainMem();
    value["lvc"]=v.getRemainCPU();
    value["coC"]=c.getCoCPU();
    value["coM"]=c.getCoMem();
    value["vMO"]=v.getOs()==""?v.getIdleMem():0;
    value["vCO"]=v.getOs()==""?v.getIdleCPU():0;
    return value;
}

Rule::Rule(int id) {
    this->id=id;
    this->root=build(this->root,0);
}

Rule::Rule(const Rule& t,int id,int p) {
    this->id=id;
    this->root=mbuild(t.root,p);
}

int Rule::sumNodes() {
    return sumNodes(this->root->left)+sumNodes(this->root->right);
}

int Rule::sumNodes(node *root) {
    if (root== nullptr){
        return 0;
    }else{
        return sumNodes(root->left)+sumNodes(root->right)+1;
    }
}

float Rule::caculate() {
    auto root=this->root;
    if (root== nullptr){
        return 0;
    }
    if (root->isNum){
        return this->value[root->value];
    }else{
        switch (root->mark) {
            case '+':
                return caculate(root->left)+caculate(root->right);
            case '-':
                return caculate(root->left)-caculate(root->right);
            case '*':
                return caculate(root->left)*caculate(root->right);
            case '/': {
                float temp = caculate(root->right);
                if (temp == 0) {
                    return caculate(root->left);
                } else {
                    return caculate(root->left) / temp;
                }
            }
            default:{
                printf("error\n");
                return 0;
            }
        }
    }
}

float Rule::caculate(std::map<std::string, int> value) {
    this->value=value;
    this->weight=this->caculate();
    return this->weight;
}

float Rule::caculate(node *root) {
    if (root== nullptr){
        return 0;
    }
    if (root->isNum){
        return this->value[root->value];
    }else{
        switch (root->mark) {
            case '+':
                return caculate(root->left)+caculate(root->right);
            case '-':
                return caculate(root->left)-caculate(root->right);
            case '*':
                return caculate(root->left)*caculate(root->right);
            case '/': {
                float temp = caculate(root->right);
                if (temp == 0) {
                    return caculate(root->left);
                } else {
                    return caculate(root->left) / temp;
                }
            }
            default:{
                printf("error\n");
                return 0;
            }
        }
    }
}

Rule mutation(Rule target , int id,int p){
    return Rule(target,id,p);
}

node * Rule::select() {
    //srand((unsigned)time(NULL)+seed++);
    int target=rand()%this->sumNodes()+1;
    return this->select(target);
}

node * Rule::select(int target) {
    std::vector<node*> list{this->root};
    int start=0;
    while(true){
        if(list[start]->left!= nullptr){
            target--;
            if (target==0){
                flag=true;
                return list[start];
            }
        }else if(list[start]->right!= nullptr){
            target--;
            if (target==0){
                flag=false;
                return list[start];
            }
        } else{
            start++;
        }
    }
}

std::vector<Rule> crossing(Rule father,Rule mather,int id1,int id2){
    auto father1=mutation(father,id1,0);
    auto new1=father1.select();
    auto f1=flag;
    auto mather1=mutation(mather,id2,0);
    auto new2=mather1.select();
    auto f2=flag;
    if(f1&&f2){
        auto item=new1->left;
        new1->left=new2->left;
        new2->left=item;
    }else if(f1&&!f2){
        auto item=new1->left;
        new1->left=new2->right;
        new2->right=item;
    }else if(!f1&&f2){
        auto item=new1->right;
        new1->right=new2->left;
        new2->left=item;
    }else{
        auto item=new1->right;
        new1->right=new2->right;
        new2->right=item;
    }
    return std::vector<Rule>{father1,mather1};
};

std::vector<int> setRandOne(int target,int total){
    std::vector<int> ans;
    std::unordered_set<int> list;
    for(int i=0;i<target;){
        //srand((unsigned)time(NULL)+seed++);
        int temp=rand()%total;
        if(!list.count(temp)){
            list.insert(temp);
            i++;
        }
    }
    for(auto i : list){
        ans.push_back(i);
    }
    return ans;
}

std::vector<std::vector<int>> setRandPair(int target,int total){
    std::vector<std::vector<int>> ans;
    for(int i=0;i<target;i++){
        //srand((unsigned)time(NULL)+seed++);
        int temp1=rand()%total;
        int temp2=rand()%total;
        std::vector<int> temp{temp1,temp2};
        ans.push_back(temp);
    }
    return ans;
}