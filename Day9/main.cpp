//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int getBasinSize(int x, int y,vector<vector<int>> &heights){
  auto cmp = [](std::tuple<int,int,int> &left, std::tuple<int,int,int> &right){
    return get<0>(left)<get<0>(right);
  };

  priority_queue<std::tuple<int,int,int>,std::vector<std::tuple<int,int,int>>,decltype(cmp)> open(cmp);

  vector<vector<bool>> marked(heights.size(),std::vector<bool>(heights[0].size(),false));

  open.emplace(make_tuple(heights[x][y],x,y));

  int size = 0;

  while (!open.empty()){
    auto cur = open.top();
    open.pop();
    int val = get<0>(cur);
    int curX = get<1>(cur);
    int curY = get<2>(cur);
    if(marked[curX][curY] || val>=9){
      continue;
    }
    marked[curX][curY] = true;
    ++size;
    open.push(make_tuple(heights[curX-1][curY],curX-1,curY));
    open.push(make_tuple(heights[curX+1][curY],curX+1,curY));
    open.push(make_tuple(heights[curX][curY-1],curX,curY-1));
    open.push(make_tuple(heights[curX][curY+1],curX,curY+1));
  }

  return size;
}

void part1(){
  std::string line;
  cin>>line;
  auto len = line.length()+2;
  vector<vector<int>> heights;
  {
    heights.emplace_back(line.length() + 2, 10);
    vector<int> curLine(len, 10);

    for (int i = 0; i < line.length(); ++i) {
      curLine[i + 1] = line[i] - '0';
    }

    heights.push_back(curLine);
  }
  while((cin >> line) &&!line.empty()){
    vector<int> curLine(len,10);

    for(int i=0;i<line.length();++i){
      curLine[i+1]= line[i]-'0';
    }
    heights.push_back(curLine);
  }

  heights.emplace_back(len,10);

  auto isLow = [&heights](int x, int y){
    return heights[x][y]<heights[x-1][y]
          && heights[x][y]<heights[x+1][y]
          && heights[x][y]<heights[x][y-1]
          && heights[x][y]<heights[x][y+1];
  };

  int res = 0;

  for (int x = 1; x < heights.size()-1; ++x) {
    for (int y = 1; y < len-1; ++y) {
      if(isLow(x,y)){
        //cout << x<<","<<y<<endl;
        res+=heights[x][y]+1;
      }
    }
  }

  cout << res<<endl;
}

void part2(){
  std::string line;
  cin>>line;
  auto len = line.length()+2;
  vector<vector<int>> heights;
  {
    heights.emplace_back(line.length() + 2, 10);
    vector<int> curLine(len, 10);

    for (int i = 0; i < line.length(); ++i) {
      curLine[i + 1] = line[i] - '0';
    }

    heights.push_back(curLine);
  }
  while((cin >> line) &&!line.empty()){
    vector<int> curLine(len,10);

    for(int i=0;i<line.length();++i){
      curLine[i+1]= line[i]-'0';
    }
    heights.push_back(curLine);
  }

  heights.emplace_back(len,10);

  auto isLow = [&heights](int x, int y){
    return heights[x][y]<heights[x-1][y]
           && heights[x][y]<heights[x+1][y]
           && heights[x][y]<heights[x][y-1]
           && heights[x][y]<heights[x][y+1];
  };

  vector<pair<int,int>> lowPoints;

  for (int x = 1; x < heights.size()-1; ++x) {
    for (int y = 1; y < len-1; ++y) {
      if(isLow(x,y)){
        lowPoints.push_back({x,y});
      }
    }
  }


  priority_queue<int> sizes;

  for (auto& lowPoint : lowPoints) {
    int size = getBasinSize(lowPoint.first,lowPoint.second,heights);
    //cout << size << endl;
    sizes.push(size);
  }

  int res = 1;
  for (int i = 0; i < 3; ++i) {
    res *= sizes.top();
    sizes.pop();
  }
  cout << res <<endl;
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

