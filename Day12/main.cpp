//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <chrono>
#include <iomanip>

using namespace std;

using NextCandidate = pair<string,vector<string>>;

struct PartialPath{
  string next;
  vector<string> path;
  bool oneSmallVisitedTwice;
};

bool isLargeCave(string name){
  return name[0]>='A'&&name[0]<='Z';
}

unordered_map<string,vector<string>> parseGraph(){
  std::string line;
  unordered_map<string,std::vector<string>> edges;
  while(getline(std::cin, line) && !line.empty()){
    auto p = line.find("-");
    string beg = line.substr(0,p);
    string end = line.substr(p+1);

    if(beg!="end" && end!="start") {
      edges[beg].push_back(end);
    }
    if(beg!="start" && end!="end") {
      edges[end].push_back(beg);
    }
  }
  return edges;
}

void part1(){
  auto graph = parseGraph();

  int res = 0;
  std::queue<NextCandidate> open;
  NextCandidate s{"start",{}};
  open.emplace(s);

  while (!open.empty()){
    NextCandidate c = open.front();
    open.pop();


    auto currentPath = c.second;
    currentPath.push_back(c.first);

    if(c.first == "end"){
      res +=1;
      /*for(auto &node : currentPath){
        cout << node << ",";
      }
      cout << endl;*/
      continue;
    }

    for (auto &next : graph[c.first]) {
      if (isLargeCave(next)){
        open.emplace(next,currentPath);
      } else {
        if(std::find(currentPath.begin(), currentPath.end(), next)==currentPath.end()){
          open.emplace(next,currentPath);
        }
      }
    }
  }

  cout << res << endl;
}

void part2(){
  auto graph = parseGraph();

  int res = 0;
  std::queue<PartialPath> open;
  PartialPath s{"start",{},false};
  open.emplace(s);

  while (!open.empty()){
    PartialPath c = open.front();
    open.pop();


    auto currentPath = c.path;
    currentPath.push_back(c.next);

    if(c.next == "end"){
      res +=1;
      /*for(auto &node : currentPath){
        cout << node << ",";
      }
      cout << endl;*/
      continue;
    }

    for (auto &next : graph[c.next]) {
      if (isLargeCave(next)){
        open.emplace(PartialPath{next,currentPath,c.oneSmallVisitedTwice});
      } else {
        if(std::find(currentPath.begin(), currentPath.end(), next)==currentPath.end()){
          open.emplace(PartialPath{next,currentPath,c.oneSmallVisitedTwice});
        }else if(!c.oneSmallVisitedTwice){
          open.emplace(PartialPath{next,currentPath,true});
        }
      }
    }
  }

  cout << res << endl;
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

