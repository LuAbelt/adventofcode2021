//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class LanternFish{
  int _state;
public:
 explicit LanternFish(int initialValue = 8):_state(initialValue){}

 void passDay(){
   if(_state==0){
     _state=6;
   }else{
     --_state;
   }
 }

 [[nodiscard]] int getState() const{
   return _state;
 }
};

class School
    :public LanternFish{
  size_t _population;
public:
  School(int initialValue, size_t population): LanternFish(initialValue),_population(population){}

  [[nodiscard]] size_t getPopulation() const{
    return _population;
  }
};

void printFishes(std::vector<LanternFish>& fishes){
  for (auto& f : fishes) {
    cout << f.getState()<<",";
  }
  cout<<endl;
}

void part1(){
  std::string line;
  getline(cin,line);

  std::vector<LanternFish> fishes;

  size_t p;
  while ((p = line.find(",")) != std::string::npos){
    int n = stoi(line.substr(0,p));
    line=line.substr(p+1);
    fishes.emplace_back(n);
  }
  fishes.emplace_back(stoi(line));

  printFishes(fishes);
  for (int i = 1; i <= 80; ++i) {
    int newFishes = 0;

    for (auto& fish : fishes ) {
      if(fish.getState()==0){
        newFishes++;
      }

      fish.passDay();
    }

    /*if(i<20) {
      cout << "After " << i << " days ";
      printFishes(fishes);
    }*/
    fishes.resize(fishes.size()+newFishes,LanternFish());
  }

  cout << fishes.size() << std::endl;
}

void part2(){
  std::string line;
  getline(cin,line);

  std::vector<School> fishes;

  size_t p;
  std::map<int,size_t> initialValues;

  while ((p = line.find(",")) != std::string::npos){
    int n = stoi(line.substr(0,p));
    line=line.substr(p+1);
    initialValues[n]++;
  }
  initialValues[stoi(line)]++;

  for (auto& entry : initialValues) {
    fishes.emplace_back(entry.first,entry.second);
  }

  for (int i = 1; i <= 256; ++i) {
    size_t newFishes = 0;

    for (auto& fish : fishes ) {
      if(fish.getState()==0){
        newFishes+=fish.getPopulation();
      }

      fish.passDay();
    }

    /*if(i<20) {
      cout << "After " << i << " days ";
      printFishes(fishes);
    }*/
    fishes.emplace_back(School(8,newFishes));
  }

  size_t res = 0;
  for (auto &school : fishes) {
    res+=school.getPopulation();
  }
  cout<<res<<endl;
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

