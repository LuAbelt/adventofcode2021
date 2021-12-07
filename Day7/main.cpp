//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

uint64_t fuelConsumptionNonLinear(uint64_t start, uint64_t goal){
  uint64_t d = std::max(start,goal)-std::min(start,goal);

  return (d*d+d)/2;
}

void part1(){
  std::string line;
  getline(cin,line);

  size_t p;
  std::vector<int> positions;

  int min = std::numeric_limits<int>::max();
  int max = 0;

  while ((p = line.find(",")) != std::string::npos){
    int n = stoi(line.substr(0,p));
    min = std::min(min,n);
    max = std::max(max,n);
    line=line.substr(p+1);
    positions.emplace_back(n);
  }
  positions.emplace_back(stoi(line));

  uint64_t minFuel = std::numeric_limits<uint64_t>::max();

  for (int i = min; i <= max; ++i) {
    uint64_t fuelConsumption = std::accumulate(positions.begin(),positions.end(),0,[i](uint64_t cur, auto& pos){
      return cur+abs(pos-i);
    });

    minFuel = std::min(minFuel,fuelConsumption);
  }

  cout << minFuel << endl;
}

void part2(){
  std::string line;
  getline(cin,line);

  size_t p;
  std::vector<int> positions;

  int min = std::numeric_limits<int>::max();
  int max = 0;

  while ((p = line.find(",")) != std::string::npos){
    int n = stoi(line.substr(0,p));
    min = std::min(min,n);
    max = std::max(max,n);
    line=line.substr(p+1);
    positions.emplace_back(n);
  }
  positions.emplace_back(stoi(line));

  uint64_t minFuel = std::numeric_limits<uint64_t>::max();

  for (int i = min; i <= max; ++i) {
    uint64_t fuelConsumption = std::accumulate(positions.begin(),positions.end(),0,[i](uint64_t cur, auto& pos){
      return cur+ fuelConsumptionNonLinear(i,pos);
    });

    minFuel = std::min(minFuel,fuelConsumption);
  }

  cout << minFuel << endl;
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

