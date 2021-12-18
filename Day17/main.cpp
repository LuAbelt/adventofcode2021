//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <valarray>

using namespace std;

void part1(){
  std::string line;
  while((std::cin >> line) && !line.empty()){
    // Read input
  }
}

bool simulateThrow(int64_t xVel, int64_t yVel, int xMin, int xMax, int yMin, int yMax){
    int64_t curX = 0;
    int64_t curY = 0;

    while (true){
        curX+= xVel;
        curY+= yVel;
        if(curX>=xMin && curX<=xMax && curY>=yMin && curY<=yMax){
            return true;
        }

        if(curX>xMax || curY<yMin){
            return false;
        }
        if(xVel>0){
            xVel--;
        }
        yVel--;
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

    int xMin = stoi(line.substr(xBeg+2,(xSep-xBeg-2)));
    int xMax = stoi(line.substr(xSep+2,(separator-xSep-2)));

    int yMin = stoi(line.substr(separator+yBeg+2,(ySep-yBeg-2)));
    int yMax = stoi(line.substr(separator+ySep+2));

    int64_t xLower=sqrt(xMin);
    int64_t xUpper=xMax;

    int64_t yLower = yMin;
    int64_t yUpper =1000;

    int64_t cnt = 0;

    cout << "Simualting " << (yMax-yMin)*(xMax-xMin) << " throws." << endl;
    for (int x = xLower; x <= xUpper; ++x) {
        for (int y = yLower; y <= yUpper; ++y) {
            if(simulateThrow(x,y,xMin,xMax,yMin,yMax)){
                cnt++;
            }
        }
    }

    cout << cnt << endl;
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

