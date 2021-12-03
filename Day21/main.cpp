//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>

using namespace std;

void part1(){
  std::string line;
  while((std::cin >> line) && !line.empty()){
    // Read input
  }
}

void part2(){
  std::string line;

  while((std::cin >> line) && !line.empty()) {
      // Read input
  }
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

