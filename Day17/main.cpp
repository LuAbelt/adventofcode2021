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

    getline(cin, line);

    size_t xBeg = line.find("x=");
    size_t separator = line.find(",");
    size_t xSep = line.substr(0,separator).find("..");
    size_t yBeg = line.substr(separator).find("y=");
    size_t ySep = line.substr(separator).find("..");

    int xBBMin = stoi(line.substr(xBeg+2,(xSep-xBeg-2)));
    int xBBMax = stoi(line.substr(xSep+2,(separator-xSep-2)));

    int yBBMin = stoi(line.substr(separator+yBeg+2,(ySep-yBeg-2)));
    int yBBMax = stoi(line.substr(separator+ySep+2));

    cout << line.substr(xBeg+2,(xSep-xBeg-2))<<endl;
    cout << line.substr(xSep+2,(separator-xSep-2))<<endl;
    cout << line.substr(separator+yBeg+2,(ySep-yBeg-2))<<endl;
    cout << line.substr(separator+ySep+2)<<endl;
    //cout << line.substr(xBeg+2,(xSep-xBeg-2))<<endl;

    int64_t x1,x2;
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

