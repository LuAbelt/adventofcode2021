//
// Created by lukas on 02/12/2021.
//
# include <iostream>

void part1(){
    int numEntries = 1000;

    int down = 0;
    int forward = 0;

    std::string line;
    while(numEntries>0){
        std::getline(std::cin, line);
        auto p = line.find(" ");
        std::string command = line.substr(0,p);
        std::string num = line.substr(p+1);
        int n = std::stoi(num);

        if(command=="forward"){
            forward+=n;
        }else if(command=="down"){
            down+=n;
        }else if(command=="up"){
            down-=n;
        }

        numEntries--;
    }

    std::cout << "Down: " << down << std::endl;
    std::cout << "Forward: " << forward << std::endl;

    std::cout << down*forward<<std::endl;
}

void part2(){
    int numEntries = 1000;

    int down = 0;
    int forward = 0;
    int aim = 0;

    std::string line;
    while(numEntries>0){
        std::getline(std::cin, line);
        auto p = line.find(" ");
        std::string command = line.substr(0,p);
        std::string num = line.substr(p+1);
        int n = std::stoi(num);

        if(command=="forward"){
            forward+=n;
            down+= n*aim;
        }else if(command=="down"){
            aim+=n;
        }else if(command=="up"){
            aim-=n;
        }

        numEntries--;
    }

    std::cout << "Down: " << down << std::endl;
    std::cout << "Forward: " << forward << std::endl;

    std::cout << down*forward<<std::endl;
}

int main(int argc, char *argv[]){
  if(std::string(argv[0])=="--one"){
    part1();
  }
  if(std::string(argv[0])=="--two"){
    part2();
  }
}


