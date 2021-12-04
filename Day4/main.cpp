//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

using Board = array<array<std::pair<bool,int>,5>,5>;
using BoardPos = std::tuple<int,int,int>;
using Boards = std::vector<Board>;
using PosMap = std::map<int,std::vector<BoardPos>>;

std::vector<int> getDraw(){
  std::vector<int> res;

  std::string line;
  getline(std::cin,line);

  size_t p;
  while ((p = line.find(",")) != std::string::npos){
    int n = stoi(line.substr(0,p));
    line=line.substr(p+1);
    res.push_back(n);
  }

  return res;
}

bool parseBoard(Boards& boards, PosMap &posMap, int curBoard){
  string line;
  //Skip one empty line
  getline(cin, line);

  Board b = {std::make_pair(false,0)};
  for (int i = 0; i < 5; ++i) {
    getline(cin,line);
    if(line.empty()){
      return false;
    }
    stringstream ss(line);
    int n;
    for (int j = 0; j < 5; ++j) {
      ss >> n;
      b[i][j].second = n;
      posMap[n].push_back(make_tuple(curBoard,i,j));
    }
  }

  boards.push_back(b);

  return true;
}

bool hasRow(const Board& board){
  for(int i=0;i<5;++i){
    bool fullRow = true;
    for (int j = 0; j < 5; ++j) {
      if(!board[i][j].first){
        fullRow = false;
        break;
      }
    }
    if(fullRow){
      return true;
    }
  }

  return false;
}

bool hasColumn(const Board& board){
  for(int i=0;i<5;++i){
    bool fullCol = true;
    for (int j = 0; j < 5; ++j) {
      if(!board[j][i].first){
        fullCol = false;
        break;
      }
    }
    if(fullCol){
      return true;
    }
  }

  return false;
}

bool hasDiag(const Board& board){
  bool main=true;
  bool second=true;

  for (int i = 0; i < 5; ++i) {
    main &= board[i][i].first;
    second &= board[4-i][i].first;
  }

  return main||second;
}

bool hasWon(const Board& board){
  return hasRow(board)|| hasColumn(board);
}

void part1(){
  auto draw = getDraw();

  Boards boards;
  PosMap pMap;

  int numBoards = 0;

  while(parseBoard(boards,pMap,numBoards)){
    ++numBoards;
  }

  for (int num : draw) {
    for (auto boardPos : pMap[num]) {
      int boardNum = get<0>(boardPos);
      boards[boardNum][get<1>(boardPos)][get<2>(boardPos)].first = true;

      if(hasWon(boards[get<0>(boardPos)])){
        cout << "Board " << boardNum << " has won after draw of " << num <<endl;
        int sum = 0;
        for (int i = 0; i < 5; ++i) {
          for (int j = 0; j < 5; ++j) {
            if(!boards[boardNum][i][j].first){
              sum+=boards[boardNum][i][j].second;
            }
          }
        }

        std::cout << "BoardSum: " << sum << std::endl;
        cout << sum*num << endl;
        return;
      }

    }
  }
}

void part2(){
  auto draw = getDraw();

  Boards boards;
  PosMap pMap;

  int numBoards = 0;

  while(parseBoard(boards,pMap,numBoards)){
    ++numBoards;
  }

  std::vector<bool> boardWon(numBoards,false);

  int lastRes = 0;
  for (int num : draw) {
    for (auto boardPos : pMap[num]) {

      int boardNum = get<0>(boardPos);
      if(boardWon[boardNum]){
        continue;
      }
      boards[boardNum][get<1>(boardPos)][get<2>(boardPos)].first = true;

      if(hasWon(boards[get<0>(boardPos)])){
        boardWon[boardNum]=true;
        cout << "Board " << boardNum << " has won after draw of " << num <<endl;
        int sum = 0;
        for (int i = 0; i < 5; ++i) {
          for (int j = 0; j < 5; ++j) {
            if(!boards[boardNum][i][j].first){
              sum+=boards[boardNum][i][j].second;
            }
          }
        }

        std::cout << "BoardSum: " << sum << std::endl;
        cout << sum*num << endl;
        lastRes = sum*num;
      }

    }
  }

  cout << endl << lastRes << endl;
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

