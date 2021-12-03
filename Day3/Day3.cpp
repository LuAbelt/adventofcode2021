//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>

void part1(){

    std::vector<int> cnts;

    std::string line;

    std::cin >> line;

    cnts.resize(line.size());

    for(int i = 0;i<line.size();++i){
        if(line[i]=='1'){
            ++cnts[i];
        }else{
            --cnts[i];
        }
    }

    while((std::cin >> line) && !line.empty()){
        for(int i = 0;i<line.size();++i){
            if(line[i]=='1'){
                ++cnts[i];
            }else{
                --cnts[i];
            }
        }
    }

    int epsilon = 0;
    int gamma = 0;

    for(int i = 0;i<cnts.size();++i){
        epsilon+=((int)(cnts[i]>0))<<(cnts.size()-i-1);
        gamma+=((int)(cnts[i]<0))<<(cnts.size()-i-1);
    }

    std::cout << "Epsilon:" << epsilon << std::endl;
    std::cout << "Gamma:" << gamma << std::endl;
    std::cout << epsilon*gamma << std::endl;
}

void part2(){
    std::vector<std::string> inputs;

    std::string line;

    while((std::cin >> line) && !line.empty()) {
        inputs.push_back(line);
    }

    auto mostCommon = [](std::vector<std::string>& v, int p, char tie = '1'){
        int cnt = 0;
        for (auto &s : v) {
            if(s[p]=='1'){
                ++cnt;
            }else{
                --cnt;
            }
        }

        if(cnt>0){
            return '1';
        } else if(cnt<0){
            return '0';
        } else{
            return tie;
        }
    };

    int p = 0;
    auto co2 = inputs;
    auto o2 = inputs;
    while(o2.size()>1){
        o2.erase(std::remove_if(o2.begin(),o2.end(),[&o2,p, &mostCommon](auto& s){
            return s[p]!=mostCommon(o2,p);
        }),o2.end());
        ++p;
    }

    p=0;
    while(co2.size()>1){
        char c = mostCommon(co2,p);
        co2.erase(std::remove_if(co2.begin(),co2.end(),[p, &c](auto& s){
            return s[p]==c;
        }),co2.end());
        ++p;
    }

    auto binToInt = [](std::string& s){
        int r = 0;
        for(int i = 0;i<s.size();++i){
            r+=((int)(s[i]=='1'))<<(s.size()-i-1);
        }
        return r;
    };

    std::cout << o2[0] << "("<<binToInt(o2[0])<<")"<<std::endl;
    std::cout << co2[0] << "("<<binToInt(co2[0])<<")"<<std::endl;

    std::cout << binToInt(o2[0])*binToInt(co2[0])<<std::endl;
}

int main(int argc, char* argv[]){
  if(std::string(argv[1])=="--one"){
    part1();
  }else if(std::string(argv[1])=="--two"){
    part2();
  } else{
    std::cout << "Wrong usage!" << std::endl;
  }
}

