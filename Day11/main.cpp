//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <array>
#include <set>

using namespace std;

std::vector<pair<int,int>> dirs = {{-1,-1},{-1,0},{-1,1},
                                   {0,-1},{0,1},
                                   {1,-1},{1,0},{1,1}};

bool inBounds(int x, int y){
  return x>=0 && x<10 && y>=0 && y<10;
}

void printGrid(array<array<int,10>,10> &grid){
  for (auto line:grid) {
    for (auto col : line  ) {
      cout << col<< " ";
    }
    cout << endl;
  }
}

bool synchronized(array<array<int,10>,10> &grid){
  for (int x = 0; x < 10; ++x) {
    for (int y = 0; y < 10; ++y) {
      if (grid[x][y]!=0){
        return false;
      }
    }
  }

  return true;
}

int simulateDay(array<array<int,10>,10> & grid){
  std::set<pair<int,int>> blink;

  array<array<bool,10>,10> marked = {false};

  for (int x = 0; x < 10; ++x) {
    for (int y = 0; y < 10; ++y) {
      ++grid[x][y];
      if(grid[x][y]>9){
        blink.emplace(std::make_pair(x,y));
      }
    }
  }

  int res = 0;
  while (!blink.empty()) {

    auto pos = *blink.begin();
    blink.erase(blink.begin());
    int x = pos.first;
    int y = pos.second;
    //cout << "Processing "<<x<<","<<y<<endl;
    //printGrid(grid);
    //cout << endl;
    if(marked[x][y]){
      continue;
    }
    if(grid[x][y]>9) {
      marked[x][y] = true;
      ++res;
    }else{
      continue;
    }

    for (auto d:dirs) {
      int newX = x+d.first;
      int newY = y+d.second;
      if(inBounds(newX,newY)){
        ++grid[newX][newY];
        blink.emplace(std::make_pair(newX,newY));
      }
    }
    //cout << "after" << endl;
    //printGrid(grid);
    //cout << res << endl;
    //cout << endl << endl;
  }

  for (int x = 0; x < 10; ++x) {
    for (int y = 0; y < 10; ++y) {
      if(grid[x][y]>9){
        grid[x][y]=0;
      }
    }
  }

  return res;
}


void part1(){
  std::string line;
  array<array<int,10>,10> grid;
  int row = 0;
  while(getline(std::cin, line) && !line.empty()){
    for (int col = 0; col < 10; ++col) {
      grid[row][col] = line[col]-'0';
    }
    ++row;
  }

  int res = 0;

  for (int day = 0; day < 100; ++day) {
    res += simulateDay(grid);
    cout << "After day "<<day<<endl;
    printGrid(grid);
    cout << endl<<endl;
  }

  cout << res<<endl;
}

void part2(){
  std::string line;
  array<array<int,10>,10> grid;
  int row = 0;
  while(getline(std::cin, line) && !line.empty()){
    for (int col = 0; col < 10; ++col) {
      grid[row][col] = line[col]-'0';
    }
    ++row;
  }

  int res = 0;

  int day = 0;
  while (!synchronized(grid)){
    simulateDay(grid);
    ++day;
  }
  cout << day << endl;
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

