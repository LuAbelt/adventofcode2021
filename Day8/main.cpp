//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <array>
#include <map>

using namespace std;
auto getInput(){
  std::vector<vector<string>> notes;
  std::vector<vector<string>> outputs;

  string line;
  while(getline(std::cin, line) && !line.empty()){
    // Read input
    string note = line.substr(0,line.find("|"));
    string out = line.substr(line.find("|")+1);
    {
      stringstream ss(note);
      string pattern;
      vector<string> n;
      while (ss>>pattern){
        std::sort(pattern.begin(), pattern.end());
        n.push_back(pattern);
      }
      notes.emplace_back(n);
    }
    {
      stringstream ss(out);
      string pattern;
      vector<string> n;
      while (ss>>pattern){
        std::sort(pattern.begin(), pattern.end());
        n.push_back(pattern);
      }
      outputs.push_back(n);
    }
  }

  return std::make_pair(notes,outputs);
}


void part1(){
  auto input = getInput();

  int cnt = 0;
  for (auto& vec:input.second) {
    for (auto& out : vec) {
      if (out.length() == 2 || out.length() == 3 || out.length() == 4 ||
          out.length() == 7) {
        ++cnt;
      }
    }
  }

  cout << cnt << endl;
}

void part2(){
  auto inputs = getInput();

  int res =0;

  for (int i = 0; i < inputs.first.size(); ++i) {
    auto note = inputs.first[i];
    auto out = inputs.second[i];

    std::array<vector<string>,10> candidates;

    std::map<std::string,int> mappings;
    std::map<int,std::string> rMappings;

    for (auto& entry : note) {
      switch(entry.size()){
        case 2:
          mappings[entry] = 1;
          rMappings[1] = entry;
          break;
        case 3:
          mappings[entry] = 7;
          rMappings[7] = entry;
          break;
        case 4:
          mappings[entry] = 4;
          rMappings[4] = entry;
          break;
        case 5:
          candidates[2].emplace_back(entry);
          candidates[3].emplace_back(entry);
          candidates[5].emplace_back(entry);
          break;
        case 6:
          candidates[6].emplace_back(entry);
          candidates[9].emplace_back(entry);
          candidates[0].emplace_back(entry);
          break;
        case 7:
          mappings[entry] = 8;
          rMappings[8] = entry;
          break;
      }
    }
    //Find 9:
    for (auto& entry : candidates[9]) {
      bool found = true;
      for (auto c : rMappings[4]) {
        if(entry.find(c)==string::npos){
          found = false;
          break;
        }
      }
      if(found){
        mappings[entry]=9;
        rMappings[9]=entry;
        break;
      }
    }

    //Find 0
    for (auto& entry : candidates[0]) {
      if(entry==rMappings[9]){
        continue;
      }
      bool found = true;
      for (auto c : rMappings[1]) {
        if(entry.find(c)==string::npos){
          found = false;
          break;
        }
      }
      if(found){
        mappings[entry]=0;
        rMappings[0]=entry;
        break;
      }
    }

    //Find 6
    for (auto& entry : candidates[6]) {
      if(entry != rMappings[0] && entry != rMappings[9]){
        mappings[entry] = 6;
        rMappings[6] = entry;
      }
    }

    //Find 3
    for (auto& entry : candidates[3]) {
      bool found = true;
      for (auto c : rMappings[1]) {
        if(entry.find(c)==string::npos){
          found = false;
          break;
        }
      }
      if(found){
        mappings[entry]=3;
        rMappings[3]=entry;
        break;
      }
    }

    //Find 5
    std::string s;
    for (auto c:rMappings[4]) {
      if(rMappings[1].find(c)==string::npos){
        s.push_back(c);
      }
    }

    for (auto& entry : candidates[5]) {
      if((entry.find(s[0])!=string::npos) && (entry.find(s[1])!=string::npos)){
        mappings[entry] = 5;
        rMappings[5] = entry;
        break;
      }
    }

    //Find 2
    for (auto& entry:candidates[2]) {
      if(entry == rMappings[3] || entry == rMappings[5]){
        continue;
      }
      mappings[entry] = 2;
      rMappings[2] = entry;
      break;
    }

    int output = 0;
    for (auto entry : out) {
      output *= 10;
      output += mappings[entry];
    }
    cout << output << endl;
    res += output;
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

