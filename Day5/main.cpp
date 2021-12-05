//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>

using namespace std;

void printGrid(std::vector<std::vector<uint32_t>> &grid){
  for (auto& line : grid ) {
    for(auto p : line){
      if(p==0){
        cout << ".";
      }else{
        cout << p;
      }
    }
    cout << endl;
  }
}

struct Point{
  int x,y;
};

struct Line{
  Point begin,end;


  [[nodiscard]] bool isOrthogonal() const{
    return (begin.x==end.x)||(begin.y==end.y);
  }

  [[nodiscard]] bool isDiagonal() const{
    return abs(end.x-begin.x)==abs(end.y-begin.y);
  }

  [[nodiscard]] std::vector<Point> getPoints() const{
    if(!(isOrthogonal()||isDiagonal())){
      return {};
    }
    std::vector<Point> res;

    if(isDiagonal()){

      int dist = abs(end.x-begin.x);
      for (int i = 0; i <= dist; ++i) {
        int x,y;
        if(begin.x<=end.x){
          x=begin.x+i;
        }else{
          x=begin.x-i;
        }

        if(begin.y<=end.y){
          y=begin.y+i;
        }else{
          y=begin.y-i;
        }

        res.push_back({x,y});
      }

      return res;
    }

    if(begin.x==end.x){
      int beg = begin.y;
      int en = end.y;
      if(begin.y>end.y){
        beg = end.y;
        en = begin.y;
      }

      for (int y = beg; y <= en; ++y) {
        res.push_back({begin.x,y});
      }
    }else if(begin.y==end.y){
      int beg = begin.x;
      int en = end.x;
      if(begin.x>end.x){
        beg = end.x;
        en = begin.x;
      }

      for (int x = beg; x <= en; ++x) {
        res.push_back({x,begin.y});
      }
    }

    return res;
  }
};

void part1(){
  std::string line;
  int maxX = 0;
  int maxY = 0;

  std::vector<Line> lines;
  while(getline(std::cin, line) && !line.empty()) {
    // Read input
    auto p = line.find("->");
    auto p1 = line.substr(0, p - 1);
    auto p2 = line.substr(p + 3);

    int y1 = stoi(p1.substr(0, p1.find(",")));
    int x1 = stoi(p1.substr(p1.find(",") + 1));

    int y2 = stoi(p2.substr(0, p2.find(",")));
    int x2 = stoi(p2.substr(p2.find(",") + 1));

    maxX = max(maxX,x1);
    maxX = max(maxX,x2);

    maxY = max(maxY,y1);
    maxY = max(maxY,y2);
    lines.push_back({{x1,y1},{x2,y2}});
  }

  std::vector<std::vector<uint32_t>> grid;

  grid.resize(maxX+1,std::vector<uint32_t>(maxY+1,0));

  for (auto& l : lines ) {
    if (l.isOrthogonal()){
      auto points = l.getPoints();
      for (auto p : points) {
        ++grid[p.x][p.y];
      }
    }
  }

  printGrid(grid);

  int cnt = 0;
  for (auto& l : grid ) {
    for (auto pos : l ) {
      if(pos>1){
        ++cnt;
      }
    }
  }

  cout << cnt << endl;
}

void part2(){
  std::string line;
  int maxX = 0;
  int maxY = 0;

  std::vector<Line> lines;
  while(getline(std::cin, line) && !line.empty()) {
    // Read input
    auto p = line.find("->");
    auto p1 = line.substr(0, p - 1);
    auto p2 = line.substr(p + 3);

    int y1 = stoi(p1.substr(0, p1.find(",")));
    int x1 = stoi(p1.substr(p1.find(",") + 1));

    int y2 = stoi(p2.substr(0, p2.find(",")));
    int x2 = stoi(p2.substr(p2.find(",") + 1));

    maxX = max(maxX,x1);
    maxX = max(maxX,x2);

    maxY = max(maxY,y1);
    maxY = max(maxY,y2);
    lines.push_back({{x1,y1},{x2,y2}});
  }

  std::vector<std::vector<uint32_t>> grid;

  grid.resize(maxX+1,std::vector<uint32_t>(maxY+1,0));

  for (auto& l : lines ) {
    if (l.isOrthogonal()||l.isDiagonal()){
      auto points = l.getPoints();
      for (auto p : points) {
        ++grid[p.x][p.y];
      }

      //std::cout << "Grid after line (" <<l.begin.x<<"|"<<l.begin.y<<")->("<<l.end.x<<"|"<<l.end.y<<")"<<endl;
      //printGrid(grid);
      //cout << endl<<endl;
    }
  }

  //printGrid(grid);

  int cnt = 0;
  for (auto& l : grid ) {
    for (auto pos : l ) {
      if(pos>1){
        ++cnt;
      }
    }
  }

  cout << maxX<< "," <<maxY << endl;
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

