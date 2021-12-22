//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class DeterministicDice{
    int _maxValue;
    int _numThrows = 0;
    int _curValue = 0;
public:
    DeterministicDice(uint64_t maxValue)
    :_maxValue(maxValue){}

    int throwDice(){
        ++_numThrows;
        ++_curValue;
        if(_curValue>100){
            _curValue=1;
        }
        return _curValue;
    }

    int throws(){
        return _numThrows;
    }
};

struct Player{
    uint16_t position;
    uint64_t score;
};

struct QuantumGameState{
    Player p1;
    Player p2;
    size_t playerTurn;

    bool operator<(QuantumGameState const & Other) const{
        if(Other.p1.position==p1.position){
            if(Other.p1.score==p1.score){
                if(Other.p2.position==p2.position){
                    if(Other.p2.score==p2.score){
                        return Other.playerTurn<playerTurn;
                    }else{
                        return Other.p2.score<p2.score;
                    }
                }else{
                    return Other.p2.position<p2.position;
                }
            }else{
                return Other.p1.score<p1.score;
            }
        }else{
            return Other.p1.position<p1.position;
        }
    }
};

map<uint64_t,uint64_t> DiracPossibilities{
        {3,1},
        {4,3},
        {5,6},
        {6,7},
        {7,6},
        {8,3},
        {9,1}
};

void part1(){
    std::string line;
    getline(cin,line);

    uint16_t p1Pos = line[line.length()-1]-'0'-1;
    getline(cin,line);

    uint16_t p2Pos = line[line.length()-1]-'0'-1;

    Player p1{p1Pos,0};
    Player p2{p2Pos,0};

    DeterministicDice dice(100);

    while (p1.score<1000 && p2.score<1000){
        int move = dice.throwDice() + dice.throwDice() + dice.throwDice();

        p1.position = (p1.position+move)%10;
        p1.score += p1.position+1;
        if(p1.score>=1000){
            break;
        }
        move = dice.throwDice() + dice.throwDice() + dice.throwDice();

        p2.position = (p2.position+move)%10;
        p2.score += p2.position+1;
    }

    if(p1.score<1000){
        cout << p1.score * dice.throws() << endl;
    }else{
        cout << p2.score * dice.throws() << endl;
    }
}

void part2(){
    std::string line;
    getline(cin,line);

    uint16_t p1Pos = line[line.length()-1]-'0'-1;
    getline(cin,line);

    uint16_t p2Pos = line[line.length()-1]-'0'-1;

    Player p1{p1Pos,0};
    Player p2{p2Pos,0};

    QuantumGameState initialState{p1,p2,0};
    std::map<QuantumGameState,uint64_t> runningGames;

    vector<uint64_t> universesWon(2,0);
    runningGames[initialState]=1;

    while(!runningGames.empty()){
        std::map<QuantumGameState,uint64_t> newStates;
        for (const auto& game:runningGames) {
            for (const auto& outcome: DiracPossibilities) {
                uint64_t numUniverses = game.second*outcome.second;
                size_t playerTurn=0;
                Player p1 = game.first.p1;
                Player p2 = game.first.p2;

                if(game.first.playerTurn==0){
                    playerTurn=1;
                    p1.position = (p1.position+outcome.first)%10;
                    p1.score += p1.position+1;
                    if(p1.score>=21){
                        universesWon[0]+=numUniverses;
                        continue;
                    }
                }else{
                    playerTurn=0;
                    p2.position = (p2.position+outcome.first)%10;
                    p2.score += p2.position+1;
                    if(p2.score>=21){
                        universesWon[1]+=numUniverses;
                        continue;
                    }
                }
                QuantumGameState newState{p1,p2,playerTurn};
                newStates[newState]+=numUniverses;
            }
        }

        runningGames = newStates;
    }



    for (auto& won:universesWon) {
        cout << won << endl;
    }
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

