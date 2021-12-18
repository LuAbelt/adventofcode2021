//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <queue>
#include <stack>
#include <cassert>

using namespace std;

class SnailFishNode{
public:
    SnailFishNode(uint64_t value)
    :value(value){}

    SnailFishNode(shared_ptr<SnailFishNode> left
                  , shared_ptr<SnailFishNode> right)
                  :left(std::move(left))
                  ,right(std::move(right)){

    };

    uint64_t magnitue() const{
        if(left&&right){
            return 3*left->magnitue()+2*right->magnitue();
        }
        assert(!left);
        assert(!right);
        return value;
    }

    void print(){
        if(left&&right){
            cout << "[";
            left->print();
            cout << ",";
            right->print();
            cout << "]";
        }else{
            cout << value;
        }
    }

    std::shared_ptr<SnailFishNode> left, right, parent;
    uint64_t value;
};

bool reduce(shared_ptr<SnailFishNode> root){
    // Find either pair with nesting depth 5 or value >10

    //DFS:
    stack<pair<int,shared_ptr<SnailFishNode>>> open;
    open.emplace(make_pair(0,root));

    while(!open.empty()){
        auto cur = open.top();
        open.pop();

        int level = cur.first;
        auto node = cur.second;

        if(node->left && node->right && level>=4){
            //Explode
            //cout << "Explode ";
            assert(!node->left->left);
            assert(!node->left->right);
            assert(!node->right->left);
            assert(!node->right->right);
            auto leftVal = node->left->value;
            auto rightVal = node->right->value;

            auto newNode = make_shared<SnailFishNode>(0);
            newNode->parent = node->parent;
            if(node->parent->left==node){
                node->parent->left = newNode;
            } else {
                node->parent->right = newNode;
            }

            //root->print();
            //cout << endl;

            //Find leftmost value neighbour
            auto current = newNode;
            while (current->parent && current->parent->left == current){
                current = current->parent;
            }

            if(current->parent && (current != current->parent->left)){
                current = current->parent->left;
                while (current->right){
                    current = current->right;
                }

                assert(!current->left);
                assert(!current->right);
                current->value += leftVal;
            }

            //Find rightmost value neighbour
            current = newNode;
            while (current->parent && current->parent->right == current){
                current = current->parent;
            }

            if(current->parent && (current != current->parent->right)){
                current = current->parent->right;
                while (current->left){
                    current = current->left;
                }
                assert(!current->left);
                assert(!current->right);
                current->value += rightVal;
            }
            return true;
        }

        if(node->left && node->right) {
            open.emplace(level + 1, node->right);
            open.emplace(level + 1, node->left);
        }
    }


    open.emplace(make_pair(0,root));
    while(!open.empty()){
        auto cur = open.top();
        open.pop();

        int level = cur.first;
        auto node = cur.second;

        if(!(node->left || node->right) && node->value>9){
            // Split
            //cout << "Split ";
            uint64_t l = node->value/2;
            uint64_t r = (node->value+1)/2;
            auto left = make_shared<SnailFishNode>(l);
            auto right = make_shared<SnailFishNode>(r);
            auto newNode = make_shared<SnailFishNode>(left,right);
            left->parent = newNode;
            right->parent = newNode;
            newNode->parent = node->parent;
            if(node->parent->left == node){
                newNode->parent->left = newNode;
            }else{
                newNode->parent->right = newNode;
            }
            return true;
        }

        if(node->left && node->right) {
            open.emplace(level + 1, node->right);
            open.emplace(level + 1, node->left);
        }
    }
    return false;
}

shared_ptr<SnailFishNode> add(shared_ptr<SnailFishNode> left
                              , shared_ptr<SnailFishNode> right){
    auto newNode = make_shared<SnailFishNode>(left,right);
    left->parent = newNode;
    right->parent = newNode;
    while (reduce(newNode)) {
    }
    return newNode;
}

shared_ptr<SnailFishNode> parse(string input, size_t &pos){
    if(input[pos]=='['){
        pos += 1;
        auto left = parse(input,pos);
        while (input[pos]!=','){
            ++pos;
        }
        pos+=1;
        auto right = parse(input,pos);

        auto resultNode = make_shared<SnailFishNode>(left,right);
        left->parent = resultNode;
        right->parent = resultNode;
        return resultNode;
    }

    if(input[pos]>='0'&&input[pos]<='9'){
        return make_shared<SnailFishNode>(input[pos]-'0');
    }

    assert(false && "We should not reach this case");
    return nullptr;
}

void part1(){
    std::string line;
    vector<shared_ptr<SnailFishNode>> numbers;
    while(getline(std::cin, line) && !line.empty()){
      size_t pos = 0;
      auto num = parse(line,pos);
      //cout << num->magnitue() << endl;
      numbers.push_back(num);
    }

    auto currentResult = numbers[0];
    //currentResult->print();
    //cout << endl;
    for (int i = 1; i < numbers.size(); ++i) {
        //cout << "+ ";
        //numbers[i]->print();
        //cout << endl;
        currentResult = add(currentResult,numbers[i]);

        while (reduce(currentResult)){
            //currentResult->print();
            //cout << endl;
        }
        //cout << "= ";
        //currentResult->print();
        //cout << endl;
    }
    cout << currentResult->magnitue() << endl;
}

void part2(){

    std::string line;
    vector<string> inputs;
    while(getline(std::cin, line) && !line.empty()){

        //cout << num->magnitue() << endl;
        inputs.push_back(line);
    }

    uint64_t maxMagnitude = 0;
    shared_ptr<SnailFishNode> op1,op2;

    for (int i = 0; i < inputs.size(); ++i) {
        for(int j = 0;j<inputs.size();++j) {
            if(j==i){
                continue;
            }
            size_t pos = 0;
            auto num1 = parse(inputs[i],pos);
            pos = 0;
            auto num2 = parse(inputs[j],pos);
            auto sum = add(num1, num2);


            if(sum->magnitue()>maxMagnitude){
                maxMagnitude = sum->magnitue();
                op1 = num1;
                op2 = num2;
            }
        }
    }
    op1->print();
    cout << " + ";
    op2->print();
    cout << " = ";
    auto res = add(op1,op2);
    res->print();
    cout << endl;
    cout << maxMagnitude << endl;
}

int main(int argc, char* argv[]){
  if(std::string(argv[1])=="--one"){
    part1();
  } else if(std::string(argv[1])=="--two"){
    part2();
  } else {
    std::cout << "Wrong usage. Allowed arguments: '--one' or '--two'";
  }
}

