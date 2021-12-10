//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

char opening[4] = {'(','[','<','{'};

std::map<char,char> mappings = {{'[',']'},{'{','}'},{'(',')'},{'<','>'}};

std::map<char,int> corruptScores = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
std::map<char,int> completeScores = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};

bool isOpening(char c){
  for (char i : opening) {
    if(c==i){
      return true;
    }
  }

  return false;
}

void part1(){
  std::string line;
  int res = 0;
  while((std::cin >> line) && !line.empty()){
    std::stack<char> chars;
    for (auto c:line) {
      if(isOpening(c)){
        chars.push(mappings[c]);
      } else {
        if(c!=chars.top()){
          res+=corruptScores[c];
          //cout << "Mismatch. Expected: '"<<chars.top()<<"'. Got '"<<c<<"'"<<endl;
          //cout << scores[c] << endl;
          break;
        } else {
          chars.pop();
        }
      }
    }
  }

  cout << res << endl;
}

void part2(){
  std::string line;
  std::vector<uint64_t> scores;

  while((std::cin >> line) && !line.empty()){
    uint64_t res = 0;
    std::stack<char> chars;
    bool corrupt = false;
    //cout << line << endl;
    for (auto c:line) {
      if(isOpening(c)){
        chars.push(mappings[c]);
      } else {
        if(c!=chars.top()){
          corrupt = true;
          break;
        } else {
          chars.pop();
        }
      }
    }

    if(corrupt){
      //cout << "Corrupt" << endl;
      continue;
    }

    while (!chars.empty()){
      res*=5;
      res+=completeScores[chars.top()];
      chars.pop();
    }
    //cout << line << endl;
    //cout << res << endl;
    scores.push_back(res);
  }

  sort(scores.begin(), scores.end());

  cout << scores[scores.size()/2] << endl;
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

